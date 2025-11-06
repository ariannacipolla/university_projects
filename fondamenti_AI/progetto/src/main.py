import torch
from torch.utils.data import DataLoader
from torchvision import datasets, transforms
from models.vit import get_vit_model
from models.cnn import get_resnet_model
from utils import train_and_eval
import torch.nn as nn
import torch.optim as optim
import pandas as pd
from utils import fgsm_attack
from utils import show_fgsm_example
from create_subset import download_dataset, crea_subset_imagenet_mini

# ID predefinito per il dataset Kaggle; impostalo con l'ID corretto se disponibile
KAGGLE_IMAGENET_MINI_ID = "ifigotin/imagenetmini-1000"

def run_experiment():
    
    subset_sizes = [10, 50, 100, 150, 200]
    source_dir = "./data/imagenet-mini"

    try:
        download_dataset(source_dir, KAGGLE_IMAGENET_MINI_ID)
    except Exception as e:
        print("Impossibile procedere senza il dataset. Interruzione.")
        return
    
    device = torch.device("mps" if torch.backends.mps.is_available() else "cuda" if torch.cuda.is_available() else "cpu")
    transform = transforms.Compose([
        transforms.Resize((224, 224)), #ridimensione ogni immagine 224x224
        transforms.ToTensor(), #converto l'immagine in un tensore di solo 0 e 1
        transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225]) #normalizzare i pixel
    ])

    crea_subset_imagenet_mini(source_dir, subset_sizes)

    results = {"Classi": [], "ViT Accuracy (%)": [], "ViT Tempo (s)": [], "ResNet Accuracy (%)": [], "ResNet Tempo (s)": []}

    for n in subset_sizes:
        #carica il dataset di train e validation
        train_ds = datasets.ImageFolder(f"{source_dir}/train_subset_{n}", transform=transform)
        val_ds = datasets.ImageFolder(f"{source_dir}/val_subset_{n}", transform=transform)

        #creo batch di immagini da 32
        train_loader = DataLoader(train_ds, batch_size=32, shuffle=True)
        val_loader = DataLoader(val_ds, batch_size=32)

        print(f"\n>> Addestramento con {n} classi")

        vit = get_vit_model(n) #carica ViT pre-addestrato
        for param in vit.parameters():
            param.requires_grad = False #congela tutti i parametri
        vit.head.requires_grad_(True) #sblocca solo la testa (parte finale)
        
        vit_acc, vit_time = train_and_eval(vit, train_loader, val_loader, device) #allena la testa sul dataset e abbiamo accuratezza e tempo
        print(f"ViT  → Acc: {vit_acc:.2f}%, Tempo: {vit_time:.1f}s")

        #carica ResNet pre-addestrata
        resnet = get_resnet_model(n)
        for param in resnet.parameters():
            param.requires_grad = False #congelo i parametri
        resnet.fc.requires_grad_(True) #sblocco solo la testa

        resnet_acc, resnet_time = train_and_eval(resnet, train_loader, val_loader, device) #allena la testa sul dataset
        print(f"ResNet → Acc: {resnet_acc:.2f}%, Tempo: {resnet_time:.1f}s")

        #valuto la robustezza dei modelli ad ogni epsilon differente
        for eps in [0.01, 0.05, 0.5]:
            vit_fgsm_acc = fgsm_attack(vit, val_loader, device, epsilon=eps)
            print(f"ViT (FGSM ε={eps}) → Accuracy: {vit_fgsm_acc:.2f}%")

            resnet_fgsm_acc = fgsm_attack(resnet, val_loader, device, epsilon=eps)
            print(f"ResNet (FGSM ε={eps}) → Accuracy: {resnet_fgsm_acc:.2f}%")

        show_fgsm_example(vit, val_loader, device, epsilon=0.01)
        show_fgsm_example(vit, val_loader, device, epsilon=0.5)
        
        results["Classi"].append(n)
        results["ViT Accuracy (%)"].append(vit_acc)
        results["ViT Tempo (s)"].append(vit_time)
        results["ResNet Accuracy (%)"].append(resnet_acc)
        results["ResNet Tempo (s)"].append(resnet_time)

    df = pd.DataFrame(results)
    print("\n=== Risultati finali ===")
    print(df)
    df.to_csv("risultati_scaling_vit_vs_resnet.csv", index=False)
    
if __name__ == "__main__":
    run_experiment()