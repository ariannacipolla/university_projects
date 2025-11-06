# Guida: Configurazione di Kaggle API e kagglehub

Questo documento descrive i passaggi necessari per installare e configurare le librerie kaggle e kagglehub sul tuo computer locale. Questa configurazione è fondamentale per poter scaricare dataset e modelli da Kaggle direttamente tramite script Python.

## Prerequisiti

- Python e pip (il gestore di pacchetti Python) installati.

- Un account Kaggle valido.

### 1. Installazione dei Pacchetti

Per interagire con l'API di Kaggle e il nuovo `kagglehub`, devi installare i pacchetti Python ufficiali.

Apri il tuo terminale o prompt dei comandi ed esegui:

```
pip install kaggle
pip install kagglehub
```

### 2. Generazione del Token API (kaggle.json)

Per permettere al tuo codice di autenticarsi con il tuo account Kaggle, hai bisogno di un token API.

- Accedi a Kaggle: Vai su https://www.kaggle.com/ ed effettua l'accesso.

- Vai al tuo Profilo: Clicca sulla tua immagine del profilo in alto a destra e seleziona "Your Profile".

- Impostazioni Account: Naviga fino alla scheda "Account".

- Genera Token: Scorri verso il basso fino alla sezione "API" e clicca sul pulsante "Create New Token".

- Il tuo browser scaricherà immediatamente un file chiamato `kaggle.json`.

**Importante**: Tratta questo file come una password. Contiene le tue credenziali segrete e non dovrebbe mai essere condiviso pubblicamente.

### 3. Configurazione delle Credenziali API

Affinché la libreria `kaggle` trovi automaticamente le tue credenziali, devi posizionare il file `kaggle.json` in una directory specifica del tuo sistema.

#### Per Linux e macOS

Apri un terminale.

Crea la cartella `.kaggle` nella tua directory home (se non esiste già):

```
mkdir -p ~/.kaggle
```

Sposta il file `kaggle.json` scaricato (di solito si trova nella cartella `Downloads`) nella nuova directory:

```
# Assicurati di cambiare '~/Downloads' se il file è altrove
mv ~/Downloads/kaggle.json ~/.kaggle/
```

Imposta i permessi corretti per il file. Questo è un passaggio cruciale per la sicurezza, per assicurarti che solo tu possa leggere il file:

```
chmod 600 ~/.kaggle/kaggle.json
```

#### Per Windows

Apri Esplora File.

Naviga nella tua cartella utente principale. Il percorso è solitamente `C:\Users\<IlTuoNomeUtente>`.

Crea una nuova cartella e rinominala `.kaggle` (assicurati che il nome inizi con un punto).

Sposta il file `kaggle.json` (che probabilmente si trova nella cartella `Download`) dentro la cartella `.kaggle` appena creata.

Il percorso finale del file sarà: `C:\Users\<IlTuoNomeUtente>\.kaggle\kaggle.json`

### 4. Utilizzo

Dopo aver scaricato i dati necessari, puoi lanciare il tuo script di addestramento principale eseguendo a terminale:

```
python main.py
```

**Attenzione alle Risorse!!!**
L'addestramento di modelli su dataset di grandi dimensioni può richiedere molte risorse (CPU/GPU, RAM e tempo).

Per un test rapido o se le tue risorse sono limitate, valuta di modificare lo script `main.py` per usare un sottoinsieme di dati più piccolo. Ad esempio, prova a impostare le dimensioni dei sottoinsiemi (variabile `subset_size`) a valori ridotti come `[10, 50, 100]` per ottenere un risultato veloce prima di lanciare un addestramento completo.