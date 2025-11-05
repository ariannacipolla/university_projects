[Fonte Appunti](https://learning.quantum.ibm.com/course/fundamentals-of-quantum-algorithms/quantum-query-algorithms)
```table-of-contents
```
# Introduzione
Questo corso esamina i vantaggi computazionali offerti dalle informazioni quantistiche. Vale a dire, penseremo a cosa possiamo fare con i computer quantistici e ai vantaggi che possono offrire rispetto ai normali computer classici. Per essere più precisi, ci concentreremo su cosa possiamo fare con un singolo computer quantistico, al contrario di un ambiente distribuito in cui più computer quantistici interagiscono su una rete, ad esempio. (Ci sono, infatti, vantaggi quantistici da trovare in ambienti distribuiti, dove la comunicazione e la crittografia entrano in gioco, ma questo argomento esula dallo scopo di questa unità.)

Inizieremo con una domanda naturale: quali sono i vantaggi che un computer quantistico potrebbe potenzialmente offrire?

Il primo potenziale vantaggio, che è fondamentale tra tutti gli altri, è che i computer quantistici potrebbero fornire soluzioni più rapide ad alcuni problemi computazionali. Il tempo è una risorsa davvero preziosa, ed è questo potenziale, che i computer quantistici potrebbero consentirci di risolvere determinati problemi computazionali che i computer classici sono troppo lenti a risolvere, che ha guidato la ricerca sul calcolo quantistico negli ultimi decenni.

Oltre al tempo, ci sono altre risorse computazionali che possono essere prese in considerazione. La quantità di memoria del computer richiesta per eseguire i calcoli, solitamente definita spazio richiesto per i calcoli, è un'alternativa che viene spesso studiata. Tuttavia, a quanto pare, i computer quantistici hanno un potenziale limitato per offrire vantaggi nell'uso dello spazio rispetto ai computer classici. La memoria del computer è anche relativamente poco costosa e, a differenza del tempo, può essere riutilizzata. Per queste ragioni, il tempo è di maggiore interesse e sarà il nostro obiettivo principale.

Una cosa che i computer quantistici non possono fare è fornire soluzioni computazionali a problemi che i computer classici non possono risolvere, indipendentemente dalle risorse richieste, come il famoso problema dell'arresto formulato da Alan Turing negli anni '30. I computer quantistici possono essere simulati dai computer classici, quindi qualsiasi problema computazionale che può essere risolto da un computer quantistico può essere risolto anche da un computer classico, anche se il computer classico potrebbe impiegare molto, molto più tempo per trovare una soluzione.

Mentre il tempo necessario per risolvere i problemi è la nostra preoccupazione principale. Ciò che faremo è formulare un semplice framework algoritmico, noto come modello di query, ed esplorare i vantaggi offerti dai computer quantistici all'interno di questo framework.

Il modello di query di calcolo è come una capsula di Petri per le idee algoritmiche quantistiche. È rigido e innaturale, nel senso che non rappresenta accuratamente i tipi di problemi computazionali che generalmente ci interessano nella pratica. Tuttavia, si è dimostrato incredibilmente utile come strumento per sviluppare tecniche algoritmiche quantistiche, comprese quelle che alimentano gli algoritmi quantistici più noti (come l'algoritmo di fattorizzazione di Shor). Capita anche che sia un framework molto utile per spiegare queste tecniche.

# Il modello di query di calcolo
Quando modelliamo i calcoli in termini matematici, di solito abbiamo in mente il tipo di processo rappresentato dalla figura seguente, in cui le informazioni vengono fornite come input, viene eseguito un calcolo e viene prodotto un output.
![[processo-calcolo.png]]

È vero che i computer che utilizziamo oggi ricevono continuamente input e producono output, interagendo essenzialmente sia con noi che con altri computer in un modo non rappresentato dalla figura. Qui, tuttavia, l'intenzione non è quella di rappresentare il funzionamento in corso dei computer, ma piuttosto di creare una semplice astrazione del calcolo, concentrandosi su attività computazionali isolate.

Ad esempio, l'input potrebbe codificare un numero, un vettore, una matrice, un grafico, una descrizione di una molecola o qualcosa di più complicato, mentre l'output codifica una soluzione all'attività computazionale che abbiamo in mente. Il punto chiave è che l'input viene fornito al calcolo, solitamente sotto forma di una stringa binaria, senza che nessuna parte di esso sia nascosta.

## Descrizione di alto livello


