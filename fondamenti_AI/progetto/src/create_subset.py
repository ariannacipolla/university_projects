import os
import shutil
import kagglehub
import traceback


# ID del dataset ImageNet-mini su Kaggle Hub
KAGGLE_IMAGENET_MINI_ID = "ifigotin/imagenetmini-1000" 

# --- Funzione per il download del dataset tramite Kaggle Hub ---
def download_dataset(source_dir, kaggle_model_id):
    """
    Scarica il dataset ImageNet-mini da Kaggle Hub se la directory non esiste.
    Verifica l'esistenza delle cartelle 'train' e 'val' nella source_dir.
    :param source_dir: Percorso in cui il dataset estratto dovrebbe risiedere (es. './data/imagenet-mini')
    :param kaggle_model_id: ID del dataset/modello su Kaggle (es. 'ifigotin/imagenetmini-1000')
    :return: Il percorso effettivo locale al dataset.
    """
    print("--- Inizio download_dataset (Debug) ---")
    
    # 1. Verifica esistenza delle cartelle principali del dataset nella source_dir
    train_path = os.path.join(source_dir, 'train')
    val_path = os.path.join(source_dir, 'val')
    
    print(f"DEBUG: Controllo esistenza dei percorsi: {train_path} e {val_path}")
    
    if os.path.exists(train_path) and os.path.isdir(train_path) and \
       os.path.exists(val_path) and os.path.isdir(val_path):
        print(f"✅ La directory dei dati '{source_dir}' esiste già e sembra completa. Salto il download.")
        print("--- Fine download_dataset ---")
        return source_dir

    print(f"⚠️ Dataset non trovato o incompleto in '{source_dir}'. Inizio il download tramite Kaggle Hub...")
    # Crea la directory padre (es. './data/')
    parent_dir = os.path.dirname(source_dir)
    os.makedirs(parent_dir, exist_ok=True) 
    print(f"DEBUG: Directory padre '{parent_dir}' assicurata.")

    try:
        # 2. Download da Kaggle Hub (gestisce cache e download)
        print(f"DEBUG: Avvio kagglehub.dataset_download per ID: {kaggle_model_id}")
        cache_path = kagglehub.dataset_download(kaggle_model_id)
        
        print(f"✅ Download completato. Dati scaricati nella cache Kaggle in: {cache_path}")
        
        # 3. Identifica e copia le cartelle 'train' e 'val' dalla cache alla directory di progetto
        print(f"⚙️ Copia dei dati dalla cache Kaggle a '{source_dir}'...")
        
        content_dir = cache_path 
        print(f"DEBUG: Percorso iniziale cache: {content_dir}")

        # Log per la ricerca di sottocartelle
        if not os.path.exists(os.path.join(content_dir, 'train')):
            print(f"DEBUG: 'train' non trovato direttamente in {content_dir}. Cerco sottodirectory.")
            subdirs = [d for d in os.listdir(cache_path) if os.path.isdir(os.path.join(cache_path, d))]
            print(f"DEBUG: Trovate sottodirectory: {subdirs}")
            for subdir in subdirs:
                temp_path = os.path.join(cache_path, subdir)
                if os.path.exists(os.path.join(temp_path, 'train')):
                    content_dir = temp_path
                    print(f"DEBUG: Trovata sottodirectory contenente 'train': {content_dir}")
                    break
        
        # Verifica se 'train' e 'val' sono stati trovati
        if not os.path.exists(os.path.join(content_dir, 'train')) or \
           not os.path.exists(os.path.join(content_dir, 'val')):
           
            raise FileNotFoundError(f"Impossibile trovare le cartelle 'train' e 'val' all'interno di {content_dir}. Verifica la struttura del dataset scaricato.")

        src_train = os.path.join(content_dir, 'train')
        src_val = os.path.join(content_dir, 'val')
        
        print(f"DEBUG: Sorgente train: {src_train}")
        print(f"DEBUG: Sorgente val: {src_val}")
        print(f"DEBUG: Destinazione train: {train_path}")
        print(f"DEBUG: Destinazione val: {val_path}")

        # Esegue la copia
        shutil.copytree(src_train, train_path, dirs_exist_ok=True)
        shutil.copytree(src_val, val_path, dirs_exist_ok=True)
        
        print(f"✅ Dati copiati e disponibili in '{source_dir}'")
        print("--- Fine download_dataset ---")
        return source_dir

    except Exception as e:
        # In caso di errore, stampa l'errore specifico e lo stack trace
        print("\n" + "="*50)
        print("❌ ERRORE CRITICO DURANTE IL DOWNLOAD O LA COPIA DEI DATI!")
        print(f"Errore: {e}")
        print("--- Stack Trace Completo ---")
        traceback.print_exc() # Stampa lo stack trace completo
        print("==================================================")
        print("\nSuggerimenti per il debug:")
        print("1. **Autenticazione Kaggle:** Assicurati di aver configurato le credenziali Kaggle. Questo è l'errore più comune.")
        print("   - Esegui `kagglehub.login()` separatamente se non l'hai fatto.")
        print("   - Controlla che il file `~/.kaggle/kaggle.json` sia presente e corretto.")
        print(f"2. **Struttura del Dataset:** Se il download riesce (punto 2), controlla il percorso: {cache_path} per assicurarti che contenga 'train' e 'val'.")
        print(f"3. **Permessi:** Verifica di avere i permessi di scrittura nella directory: {parent_dir}")
        
        # Pulizia in caso di fallimento
        if os.path.exists(source_dir):
             shutil.rmtree(source_dir)
             print(f"DEBUG: Pulizia completata per {source_dir}")
        
        # Solleva nuovamente l'eccezione per interrompere il programma in modo controllato
        raise
    
def crea_subset_imagenet_mini(base_path, subset_sizes):
    """
    Crea subset con numero specificato di classi dal dataset ImageNet-mini.
    :param base_path: percorso base, es. './data/imagenet-mini'
    :param subset_sizes: lista con numeri di classi, es. [10, 50, 100]
    """
    for size in subset_sizes:
        # Selezione classi
        train_classes = sorted(os.listdir(os.path.join(base_path, 'train')))
        selected_classes = train_classes[:size]  # o random.sample(...) per randomico

        print(f"➡️  Creazione subset con {size} classi...")

        for split in ['train', 'val']:
            src_split = os.path.join(base_path, split)
            dst_split = os.path.join(base_path, f"{split}_subset_{size}")
            os.makedirs(dst_split, exist_ok=True)

            for cls in selected_classes:
                src_class = os.path.join(src_split, cls)
                dst_class = os.path.join(dst_split, cls)
                shutil.copytree(src_class, dst_class, dirs_exist_ok=True)

        print(f"✅ Subset da {size} classi creato in {base_path}/{split}_subset_{size}\n")

# ESEMPIO USO
if __name__ == "__main__":
    base_path = "./data/imagenet-mini"
    subset_sizes = [10, 50, 100]
    crea_subset_imagenet_mini(base_path, subset_sizes)
