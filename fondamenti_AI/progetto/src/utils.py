import time
import torch
import torch.nn as nn
import torch.optim as optim
import os
import shutil
import random
import matplotlib.pyplot as plt
import numpy as np

def evaluate(model, loader, device):
    model.eval()
    correct, total = 0, 0
    with torch.no_grad():
        for x, y in loader:
            x, y = x.to(device), y.to(device)
            out = model(x)
            _, preds = torch.max(out, 1)
            correct += (preds == y).sum().item()
            total += y.size(0)
    return 100.0 * correct / total

def train_and_eval(model, train_loader, val_loader, device, epochs=3):
    model.to(device)
    
    optimizer = optim.Adam(model.parameters(), lr=3e-4) #ottimizzatore adam per aggiornare i pesi
    criterion = nn.CrossEntropyLoss() #classificazione multiclasse
    
    start = time.time() #tempo
    
    for _ in range(epochs):
        model.train() #attiva la modalità training

        #itero su tutti i batch di training
        for x, y in train_loader:
            x, y = x.to(device), y.to(device)
            optimizer.zero_grad() #azzera i gradienti
            out = model(x) #calcola l'output
            loss = criterion(out, y) #calcola la loss
            loss.backward() #backpropagation
            optimizer.step() #aggiorno i pesi
            
    elapsed = time.time() - start #fine tempo
    acc = evaluate(model, val_loader, device) #calcola l'accuratezza sul validation test
    return acc, elapsed

def fgsm_attack(model, data_loader, device, epsilon):
    model.eval()

    #calcola le valutazioni corrette
    correct = 0
    total = 0

    #definisce la loss di classificazione
    criterion = nn.CrossEntropyLoss()

    #scorre tutti i batch del validation set
    for images, labels in data_loader:

        #calcolare i gradienti rispetto ai pixel
        images, labels = images.to(device), labels.to(device)
        images.requires_grad = True

        #calcola le predizioni
        outputs = model(images)
        loss = criterion(outputs, labels)

        #calcola i gradienti
        model.zero_grad()
        loss.backward()

        #creo immagini avversarie
        data_grad = images.grad.data
        perturbed_images = images + epsilon * data_grad.sign()
        perturbed_images = torch.clamp(perturbed_images, 0, 1)

        #valuta come si comporta il modello su queste immagini manipolate
        outputs = model(perturbed_images)
        _, predicted = torch.max(outputs.data, 1)

        #conta le predizioni corrette
        correct += (predicted == labels).sum().item()
        total += labels.size(0)

    accuracy = 100. * correct / total
    return accuracy

def crea_subset_imagenet_mini(base_path, subset_sizes):
    """
    Crea subset con numero specificato di classi casuali dal dataset ImageNet-mini.
    """
    for size in subset_sizes:
        train_classes = sorted(os.listdir(os.path.join(base_path, 'train')))
        selected_classes = random.sample(train_classes, size)

        print(f"➡️  Ricreazione subset con {size} classi...")

        for split in ['train', 'val']:
            src_split = os.path.join(base_path, split)
            dst_split = os.path.join(base_path, f"{split}_subset_{size}")

            if os.path.exists(dst_split):
                shutil.rmtree(dst_split)

            os.makedirs(dst_split, exist_ok=True)
            for cls in selected_classes:
                src_class = os.path.join(src_split, cls)
                dst_class = os.path.join(dst_split, cls)
                shutil.copytree(src_class, dst_class, dirs_exist_ok=True)

        print(f"✅ Subset da {size} classi rigenerato in {base_path}/{split}_subset_{size}\n")


def show_fgsm_example(model, data_loader, device, epsilon):
    model.eval()
    criterion = nn.CrossEntropyLoss()

    # prendi un batch di immagini e labels
    images, labels = next(iter(data_loader))
    images, labels = images.to(device), labels.to(device)
    images.requires_grad = True

    # predici e calcola la loss
    outputs = model(images)
    loss = criterion(outputs, labels)
    model.zero_grad()
    loss.backward()

    # calcola perturbazione
    data_grad = images.grad.data
    perturbed_images = images + epsilon * data_grad.sign()
    perturbed_images = torch.clamp(perturbed_images, 0, 1)

    # scegli la prima immagine del batch
    orig_img = images[0].detach().cpu()
    perturbed_img = perturbed_images[0].detach().cpu()

    # de-normalizza (ImageNet)
    mean = torch.tensor([0.485, 0.456, 0.406]).view(3,1,1)
    std = torch.tensor([0.229, 0.224, 0.225]).view(3,1,1)

    orig_img = orig_img * std + mean
    perturbed_img = perturbed_img * std + mean

    orig_img = torch.clamp(orig_img, 0, 1)
    perturbed_img = torch.clamp(perturbed_img, 0, 1)

    # mostra le immagini
    fig, axs = plt.subplots(1, 2, figsize=(8, 4))
    axs[0].imshow(np.transpose(orig_img.numpy(), (1,2,0)))
    axs[0].set_title("Originale")
    axs[0].axis('off')

    axs[1].imshow(np.transpose(perturbed_img.numpy(), (1,2,0)))
    axs[1].set_title(f"FGSM ε={epsilon}")
    axs[1].axis('off')

    plt.tight_layout()
    plt.show()