[Canale YouTube](https://www.youtube.com/watch?v=42OiBzfdE2o&list=PLOFEBzvs-VvqKKMXX4vbi4EB1uaErFMSO)

```table-of-contents
```

In questa lezione si parlerà delle basi dell'informazione quantistica quando sono presi in considerazione più di un sistema.
Un'idea semplice, ma di fondamentale importanza, da tenere a mente in questa lezione è che possiamo sempre scegliere di vedere più sistemi come se formassero un unico sistema composto.
Per esempio, possiamo avere più sistemi quantici che sono collettivamente in un particolare stato quantico, e poi scegliere di misurare solo uno (o un sottoinsieme appropriato) dei singoli sistemi, questo influenzerà lo stato dei sistemi rimanenti.
La comprensione dei tipi di correlazioni tra sistemi multipli (e in particolare un tipo di correlazione nota come **entanglement**) è importante anche nell'informazione e nel calcolo quantistico.
Come nella lezione precedente iniziamo dalle informazioni classiche:

# Stati classici attraverso il prodotto cartesiano
Per semplicità, inizieremo discutendo di due soli sistemi e poi generalizzeremo a più di due sistemi.
Supponiamo che $X$ è un sistema di stati classici contenuti in $\Sigma$ e $Y$ è il secondo sistema che ha gli stati classici di $\Gamma$, questi set $\Sigma$ e $\Gamma$ sono entrambi finiti e non vuoti, potrebbero essere $\Sigma = \Gamma$, ma non è necessario.
Immaginiamo di porre questi due sistemi uno affianco all'altro, con $X$ a sinistra e $Y$ a destra, possiamo quindi scegliere di vederli come un singolo sistema che è denotato nel seguente modo $(X, Y)$ oppure $XY$.
Una domanda lecita vedendo questa composizione di sistema sarebbe: "Quali sono i suoi stati classici?"
La risposta è che il set di stati classici è il prodotto cartesiano di $\Sigma$ e $\Gamma$, definito come segue:
$$\Sigma \times \Gamma = \{(a, b) \; : \; a \in \Sigma \; and \; b \in \Gamma\}$$
## Rappresentare gli stati come stringhe
In effetti, la nozione di stringa, che è un concetto fondamentale importante nel l'informatica, è formalizzata in termini matematici attraverso prodotti cartesiani. Il termine alfabeto è comunemente usato per riferirsi a insiemi di simboli usati per formare stringhe, ma la definizione matematica di un alfabeto è esattamente la stessa di quella di un insieme di stati classici: è un insieme finito e non vuoto.
Per esempio, supponiamo che $X_1, \dots, X_{10}$ sono bits, quindi il set di stati classici saranno i seguenti:
$$\Sigma_1 = \Sigma_2 = \dots = \Sigma_{10} = \{0, 1\}^{10}$$
Quindi saranno presenti $2^{10} = 1024$ stati classici del sistema collettivo $(X_1, \dots, X_{10})$ che sono gli elementi del prodotto cartesiano tra tutti i set di stati classici $\Sigma_1, \dots, \Sigma_{10}$.
Se li dovessimo scrivere come stringhe, gli stati classici si presenteranno nel seguente modo:
$$\begin{matrix}
	0000000000 \\
	0000000001 \\
	0000000010 \\
	0000000011 \\
	0000000100 \\
	\vdots \\
	1111111111
\end{matrix}$$
Possiamo notare dunque che per lo stato classico $0001010000$ i sistemi $X_4$ e $X_6$ si trovano nello stato $1$, mentre tutti gli altri sistemi si trovano nello stato $0$.

# Stati probabilistici
Ricordiamo dalla lezione precedente che uno stato probabilistico associa una probabilità ad ogni stato classico di un sistema. Così, uno stato probabilistico di sistemi multipli (visti collettivamente come se formassero un unico sistema) associa una probabilità a ciascun elemento del prodotto cartesiano degli insiemi classici di stati dei singoli sistemi.
Per esempio, supponiamo che $X$ e $Y$ sono entrambi bits, quindi corrispondono allo stato classico $\Sigma = \{0, 1\}$ e $\Gamma = \{0, 1\}$ , di seguito abbiamo un stato probabilistico della coppia $(X, Y)$:
$$\begin{matrix}
	\Pr((X, Y) = (0, 0)) = {1 \over 2} \\
	\Pr((X, Y) = (0, 1)) = 0 \\
	\Pr((X, Y) = (1, 0)) = 0 \\
	\Pr((X, Y) = (1, 1)) = {1 \over 2} \\
\end{matrix}$$
Questo è lo stato probabilistico in cui entrambi, $X$ e $Y$, hanno probabilità $1 \over 2$ se entrambi si trovano nello stato 0 o 1, questo è un esempio di correlazione tra questi sistemi.

## Ordinamento di set di stati dei prodotti cartesiani
Gli stati probabilistici dei sistemi sono rappresentati da vettori di probabilità, che sono vettori a colonna con indici che sono stati posti in corrispondenza del sottostante set di stati classici del sistema considerato.
La stessa situazione si presenta per sistemi multipli. Per rappresentare uno stato probabilistico di sistemi multipli come prodotto cartesiano, si deve decidere su un ordine degli elementi del prodotto.
Assumiamo che ogni singolo stato classico dei set $\Sigma, \Gamma$ dei sistemi $X, Y$ sono già ordinati, esiste una semplice convenzione per farlo: *ordinamento alfabetico*. Più precisamente, le voci in ogni n-tupla (o, equivalentemente, i simboli in ogni stringa) sono visti come ordinati per significatività che diminuisce da sinistra a destra. 
Per esempio, tramite questa convenzione, il prodotto cartesiano $\{1, 2, 3\} \times \{0, 1\}$ è ordinato nel seguente modo:
$$(1, 0), \;(1, 1), \;(2, 0), \;(2, 1), \;(3, 0), \;(3, 1).$$
Ora, ritornando all'esempio dei due bits, lo stato probabilistico è rappresentato dal seguente vettore probabilistico:

$$
\begin{pmatrix}
	{1 \over 2} \\
	0 \\
	0 \\
	{1 \over 2}
\end{pmatrix}
\quad
\begin{matrix}
	\leftarrow \text{ probabilità associata allo stato } 00 \\
	\leftarrow \text{ probabilità associata allo stato } 01 \\
	\leftarrow \text{ probabilità associata allo stato } 10 \\
	\leftarrow \text{ probabilità associata allo stato } 11 \\
\end{matrix} \tag{1}
$$
### Indipendenza di due sistemi
Uno stato probabilistico speciale di due sistemi è quello in cui i sistemi sono indipendenti. Intuitivamente parlando, due sistemi sono indipendenti se l'apprendimento dello stato classico di uno dei due sistemi non ha alcun effetto sulle probabilità associate con l'altro. Cioè, conoscere lo stato classico di uno dei sistemi non fornisce alcuna informazione sullo stato classico dell'altro.
Per definire precisamente questa nozione, supponiamo ancora di avere gli stessi sistemi nominati fino ad ora, rispetto a un dato stato probabilistico di questi sistemi, si dice che siano indipendenti se è il caso che: $$\text{Pr}((X, Y) = (a, b)) = \text{Pr}(X = a)\text{Pr}(Y = b)\tag{2}$$per qualunque scelta di $a \in \Sigma$ e $b \in \Gamma$.
Per esprimerla in termini di vettori probabilistici, assumiamo che gli stati probabilistici dati di $(X, Y)$ sono descritti dal vettore probabilità in notazione di Dirac:
$$\sum_{(a, b) \in \Sigma \times \Gamma} p_{ab}\ket{ab}$$
La condizione (2) per l'indipendenza è quindi equivalente all'esistenza di due vettori di probabilità:
$$
\ket{\phi} = \sum_{a \in \Sigma} q_a\ket{a} \qquad \text{e} \qquad \ket{\psi} = \sum_{b \in \Gamma} r_b\ket{b} \tag{3}
$$
rappresenta le probabilità associate agli stati classici di $X$ e $Y$, rispettivamente come: $$p_{ab} = q_ar_b \tag{4}$$ per ogni $a \in \Sigma$ e $b \in \Gamma$.

*Esempio*
Gli stati probabilistici della coppia di bits (X, Y) sono rappresentati dal vettore:
$${1 \over 6}\ket{00} + {1 \over 12}\ket{01} + {1 \over 2}\ket{10} + {1 \over 4}\ket{11}$$
dove X e Y sono indipendenti. In particolare, la condizione richiesta per l'indipendenza è vera per i vettori probabilistici:
$$\ket{\phi} = {1 \over 4}\ket{0} + {3 \over 4}\ket{1} \qquad \text{e} \qquad \ket{\psi} = {2 \over 3}\ket{0} + {1 \over 3}\ket{1}$$
**Spiegazione**: per esempio, per fare match con l'input 00, abbiamo bisogno della probabilità ${1 \over 6} = {1 \over 4} \times {2 \over 3}$ e così via.

Per lo stato probabilistico descritto nell'espressione (1), possiamo riscriverlo come segue: $${1 \over 2}\ket{00} + {1 \over 2}\ket{11} \tag{5}$$questo non rappresenta l'indipendenza tra i due sistemi X e Y, un modo per dimostrarlo è il seguente.
Supponiamo che esistano i vettori probabilistici $\ket{\phi} \; \text{e} \; \ket{\psi}$ come nell'equazione (3), per la quale la condizione (4) è soddisfatta per ogni scelta di $a$ e di $b$, sarebbe quindi necessario che:
$$q_0r_1 = \text{Pr}((X, Y) = (0, 1)) = 0$$
Ciò implica che $q_0 = 0$ o $r_1 = 0$ perché se entrambi fossero diversi da zero, il prodotto $q_0r_1$ non sarebbe zero. Ciò porta alla conclusione che $q_0r_0 = 0$ (in caso in cui $q_0 = 0$) oppure $q_1r_1 = 0$ (in caso in cui $r_1 = 0$).
Vediamo, tuttavia, che nessuna di queste uguaglianze può essere vera perché dobbiamo avere $q_0r_0 = {1 \over 2}$ e $q_1r_1 = {1 \over 2}$, quindi, non esistono vettori $\ket{\phi}$ e $\ket{\psi}$ che soddisfano la proprietà richiesta per l'indipendenza.

Avendo definito l'indipendenza tra due sistemi, ora possiamo definire la correlazione proprio come una mancanza di indipendenza. Ad esempio, perché i due bit nello stato probabilistico rappresentati dal vettore (5) non sono indipendenti, sono, per definizione, correlati

## Prodotti tensoriali di vettori
La condizione di indipendenza appena descritta può essere espressa in modo più succinto attraverso la nozione di un **prodotto tensoriale**. Sebbene questa sia una nozione molto generale che può essere definita in modo abbastanza astratto e applicata a una varietà di strutture matematiche, nel caso in oggetto può essere definita in termini semplici e concreti. Dati due vettori:
$$
\ket{\phi} = \sum_{a \in \Sigma} \alpha_a\ket{a} \qquad \text{e} \qquad \ket{\psi} = \sum_{b \in \Gamma} \beta_b\ket{b}
$$
il prodotto tensoriale $\ket{\phi} \otimes \ket{\psi}$ è un nuovo vettore sull'insieme di stati congiunti $\Sigma \times \Gamma$, definito come: 
$$
\ket{\phi} \otimes \ket{\psi} = \sum_{(a,b) \in \Sigma \times\Gamma} \alpha_a\beta_b\ket{ab}
$$
Equivalentemente, il vettore $\ket{\pi} = \ket{\phi} \otimes \ket{\psi}$ è definito dall'equazione:
$$
\braket{ab|\pi} = \braket{a|\phi}\braket{b|\psi}
$$
vera per ogni $a \in \Sigma$ e $b \in \Gamma$.
Ora possiamo **riformulare la condizione per l'indipendenza** come richiedente il vettore di probabilità $\ket{\pi}$ del sistema congiunto $(X, Y)$ rappresentabile come prodotto tensoriale:
$$\ket{\pi} = \ket{\phi} \otimes \ket{\psi}$$
dei vettori probabilità $\ket{\phi}$ e $\ket{\psi}$ su ciascuno dei sottoinsiemi X e Y.
In questa situazione possiamo dire che $\ket{\pi}$ è uno stato del prodotto o un vettore del prodotto.

>Possiamo anche omettere il simbolo $\otimes$ quando parliamo di prodotto tensoriale di kets, possiamo scriverlo come $\ket{\phi}\ket{\psi}$. Questa convenzione cattura l'idea che il prodotto tensoriale sia, in questo contesto, il modo più naturale o predefinito per prendere il prodotto di due vettori.

Quando usiamo la convenzione alfabetica per ordinare gli elementi dei prodotti cartesiani, otteniamo la seguente specifica per il prodotto tensoriale di due vettori di colonna.
$$
\begin{pmatrix}
	\alpha_1 \\
	\vdots \\
	\alpha_m
\end{pmatrix}
\; \otimes \;
\begin{pmatrix}
	\beta_1 \\
	\vdots \\
	\beta_k
\end{pmatrix}
\; = \;
\begin{pmatrix}
	\alpha_1 \beta_1 \\
	\vdots           \\
	\alpha_1 \beta_k \\
	\alpha_2 \beta_1 \\
	\vdots           \\
	\alpha_2 \beta_k \\
	\vdots           \\
	\alpha_m \beta_1 \\
	\vdots           \\
	\alpha_m \beta_k \\
\end{pmatrix}
$$
Come importante margine, osserviamo la seguente espressione per i prodotti tensori dei vettori di base standard:
$$\ket{a} \; \otimes \; \ket{b} = \ket{ab}$$
Il prodotto tensoriale di due vettori ha l'importante proprietà di essere bi-lineare, il che significa che è lineare in ciascuno dei due argomenti separatamente, supponendo che l'altro argomento sia fisso. Questa proprietà può essere espressa attraverso queste equazioni:
1. Linearità nel primo argomento:
$$
(\ket{\phi_1} + \ket{\phi_2}) \, \otimes \, \ket{\psi} = \ket{\phi_1} \, \otimes \, \ket{\psi} \, + \, \ket{\phi_2} \, \otimes \, \ket{\psi}
$$
$$
(\alpha\ket{\phi}) \, \otimes \, \ket{\psi} = \alpha(\ket{\phi} \, \otimes \, \ket{\psi})
$$
2. Linearità secondo argomento:
$$
\ket{\phi} \, \otimes \, (\ket{\psi_1} \, + \, \ket{\psi_2}) = \ket{\phi} \, \otimes \, \ket{\psi_1} \, + \, \ket{\phi} \, \otimes \, \ket{\psi_2}
$$
$$
\ket{\phi} \, \otimes \, (\alpha\ket{\psi}) = \alpha(\ket{\phi} \, \otimes \, \ket{\psi})
$$
Considerando la seconda equazione in ciascuna di queste coppie di equazioni, vediamo che gli scalari "fluttuano liberamente" all'interno dei prodotti tensori:
$$
(\alpha\ket{\phi}) \, \otimes \, \ket{\psi} = \ket{\phi} \, \otimes \, (\alpha\ket{\psi}) = \alpha(\ket{\phi} \, \otimes \, \ket{\psi})
$$
Non c'è quindi ambiguità nel semplice scrittura $\alpha(\ket{\phi} \, \otimes \, \ket{\psi})$, o alternativamente $\alpha\ket{\phi}\ket{\psi}$ oppure $\alpha\ket{\phi \, \otimes \, \psi}$ per riferirsi a questo vettore.

### Indipendenza e prodotti tensori per tre o più sistemi
Le nozioni di indipendenza e prodotti tensori si generalizzano direttamente a tre o più sistemi. Se $X_1, \dots, X_n$ sono sistemi con set di stati classici $\Sigma_1, \dots, \Sigma_n$, rispettivamente, poi uno stato probabilistico del sistema combinato $(X_1, \dots, X_n)$ è uno stato del prodotto se il vettore di probabilità associato assume la forma: 
$$
\ket{\psi} = \ket{\phi_1} \, \otimes \, \dots \, \otimes \, \ket{\phi_n} \tag{6}
$$
per i vettori probabilità $\ket{\phi_1}, \dots, \ket{\phi_n}$ descritti dagli stati probabilistici di $X_1, \dots, X_n$.
Qui, la definizione del prodotto tensoriale si generalizza in modo naturale: il vettore (6) viene definito dall'equazione:
$$
\braket{a_1 \dots a_n |\psi} = \braket{a_1|\phi_1} \dots \braket{a_ n|\phi_n}
$$
vera per ogni $a_1 \in \Sigma_1, \dots, a_n \in \Sigma_n$ .
Un modo diverso, ma equivalente, per definire il prodotto tensoriale di tre o più vettori è ricorsivamente in termini di prodotti tensoriali di due vettori:
$$
\ket{\phi_1} \, \otimes \, \dots \, \otimes \, \ket{\phi_n} = (\ket{\phi_1} \, \otimes \, \dots \, \otimes \, \ket{\phi_{n-1}}) \, \otimes \, \ket{\phi_n}
$$
assumendo $n \geq 3$.
Simile al prodotto tensoriale di soli due vettori, il prodotto tensoriale di tre o più vettori è lineare in ciascuno degli argomenti individualmente, supponendo che tutti gli altri argomenti siano fissi. In questo caso, diciamo che il prodotto tensoriale di tre o più vettori è multi-lineare.

## Operazioni su stati probabilistici
Vediamo dunque come applicare operazioni classiche sul sistema composto (X, Y), in cui ogni operazione è rappresentata tramite la matrice stocastica dove le righe e colonne sono indicizzate dal prodotto cartesiano $\Sigma \times \Gamma$.

Per esempio, supponiamo che X e Y siano bits e consideriamo l'operazione seguente: se X = 1, allora applica l'operazione NOT su Y, altrimenti non fare nulla.
Questa è un'operazione deterministica nota come **operazione controllata-NOT**, dove X è il bit "controllore" che determina se un'operazione NOT dev'essere applicata o meno al bit di "bersaglio" Y.
Vediamo come si svolge:
![[esercizio_NOT.jpeg]]

Altro esempio:
![[esercizio_prob.jpeg]]

### Operazioni indipendenti
Ora supponiamo che abbiamo più sistemi e eseguiamo in modo indipendente operazioni separate sui sistemi.
Restiamo alla solita definizione di X e Y, ora supponiamo che dobbiamo applicare un'operazione a X e, completamente indipendente, un'altra operazione su Y.
Sappiamo che le operazioni vengono descritte dalle matrici stocastiche, in questo caso ne adotteremo due, la matrice stocastica M per l'operazione su X e la matrice N per l'operazione su Y.
In questo modo, le righe e le colonne di M gli indici saranno posti in corrispondenza degli elementi di $\Sigma$ e nello stesso modo, le righe e colonne di N saranno in corrispondenza degli elementi di $\Gamma$.
Ora la domanda è: Se vedessimo X e Y come un sistema composto unico (X, Y), come sarà la matrice che combina le due operazione su questo sistema composto unico? A questo punto per rispondere dobbiamo introdurre il prodotto tensoriale tra matrici che non si discosta da quello vettoriale visto in precedenza.

#### Prodotto tensoriale tra matrici
Il prodotto tensoriale delle matrici:
$$M = \sum_{a,b \in \Sigma}\alpha_{ab}\ket{a}\bra{b}$$
e
$$N = \sum_{c,d \in \Gamma}\beta_{cd}\ket{c}\bra{d}$$
è la matrice:
$$ M \otimes N = \sum_{a,b \in \Sigma}\sum_{c,d \in \Gamma}\alpha_{ab}\beta_{cd}\ket{ac}\bra{bd}$$
Equivalentemente, M e N sono definite con la seguente equazione:
$$\braket{ac|M \otimes N | bd} = \braket{a|M|b}\braket{c|N|d}$$
vera per ogni scelta di $a,b \in \Sigma$ e $c,d \in \Gamma$.
Seguendo la convenzione descritta in precedenza per ordinare gli elementi dei prodotti cartesiani, possiamo anche scrivere il prodotto tensoriale di due matrici esplicitamente come segue:
$$
\begin{pmatrix}
	\alpha_{11} & \dots & \alpha_{1m} \\
	\vdots & \ddots & \vdots\\
	\alpha_{m1} & \dots & \alpha_{mm}
\end{pmatrix}
\otimes
\begin{pmatrix}
	\beta_{11} & \dots & \beta_{1k} \\
	\vdots & \ddots & \vdots\\
	\beta_{k1} & \dots & \beta_{kk}
\end{pmatrix}
= 
\begin{pmatrix}
	\alpha_{11}\beta_{11} & \dots & \alpha_{11} \beta_{1k} & & \alpha_{1m} \beta_{11} & \dots & \alpha_{1m}\beta_{1k} \\
	\vdots & \ddots & \vdots & \dots & \vdots & \ddots & \vdots\\
	\alpha_{11}\beta_{k1} & \dots & \alpha_{11}\beta_{kk} & & \alpha_{1m}\beta_{k1} & \dots & \alpha_{1m}\beta_{kk} \\
	& \vdots & & \ddots & & \vdots \\
	\alpha_{m1}\beta_{11} & \dots & \alpha_{m1} \beta_{1k} & & \alpha_{mm} \beta_{11} & \dots & \alpha_{mm}\beta_{1k} \\
	\vdots & \ddots & \vdots & \dots & \vdots & \ddots & \vdots\\
	\alpha_{m1}\beta_{k1} & \dots & \alpha_{m1}\beta_{kk} & & \alpha_{mm}\beta_{k1} & \dots & \alpha_{mm}\beta_{kk} \\
\end{pmatrix}
$$
Vediamo, prendendo le matrici stocastiche dell'esempio precedente, come fare il prodotto tensoriale:
La prima matrice si tratta dell'operazione se X = 1 allora NOT Y, mentre la seconda matrice si tratta dell'operazione se Y = 1 allora NOT X.
![[prodotto_tensoriale_mat.jpeg]]
>il risultato è una matrice stocastica $m \times m \times k \times k$.

# Stati quantistici
Gli stati quantistici di più sistemi sono rappresentati da vettori di colonna con numeri complessi in input e norma euclidea uguale a 1, gli indici di questi vettori sono posti in corrispondenza con il prodotto cartesiano degli insiemi di stati classici associati a ciascuno dei singoli sistemi (perché questo è l'insieme di stati classici del sistema composto).
Se X e Y sono qubits, l'insieme degli stati classici di una coppia di qubits (X, Y) vista collettivamente come un unico sistema, è il prodotto cartesiano $\{0, 1\} \times \{0, 1\}$.
Rappresentando coppie di valori binari come stringhe binarie di lunghezza due, associamo questo set di prodotti cartesiani all'insieme $\{00, 01, 10, 11\}$.
Possiamo rappresentare un esempio:
$$
{1 \over \sqrt{2}}\ket{00} - {1 \over \sqrt{6}}\ket{01} + {i \over \sqrt{6}}\ket{10} + {1 \over \sqrt{6}}\ket{11}
$$
![[quantum_state_mulsys.jpeg]]

## Prodotto tensore di vettori di stato quantistici
Simile a quello che abbiamo per i vettori di probabilità, i prodotti tensoriali dei vettori di stato quantistico sono anche vettori di stato quantistico - e ancora una volta rappresentano l'indipendenza tra i sistemi.
Supponiamo che $\ket{\phi}$ è un vettore di stato quantistico del sistema X e $\ket{\psi}$ è il vettore di stato quantistico Y. Il prodotto tensoriale $\ket{\phi} \otimes \ket{\psi}$ che può anche essere riscritto come $\ket{\phi}\ket{\psi}$ è quindi il vettore di stato quantistico del sistema congiunto (X, Y).
Più intuitivamente, quando la coppia di sistema (X, Y) è in uno stato prodotto $\ket{\phi} \otimes \ket{\psi}$, questo significa che X è nello stato quantistico $\ket{\phi}$ e Y è nello stato quantistico $\ket{\psi}$ e gli stati dei due sistemi non hanno nulla a che fare l'uno con l'altro.

## Stati entangled
Non tutti i vettori di stato quantistico di più sistemi sono stati di prodotto. Ad esempio, il vettore di stato quantistico
$$
{1 \over 2}\ket{00} + {1 \over 2}\ket{11}
$$
di due qubit non è uno stato del prodotto. Per ragionare su questo, possiamo seguire esattamente lo stesso argomento che abbiamo usato per dimostrare che lo stato probabilistico rappresentato dal vettore non è uno stato del prodotto.
Se fosse un stato prodotto, esisterebbero i vettori di stato quantistici $\ket{\phi}$ e $\ket{\psi}$ perché valga
$$\ket{\phi} \otimes \ket{\psi} = {1 \over 2}\ket{00} + {1 \over 2}\ket{11}$$
Ma questo causa la necessità di avere
$$
\braket{0|\phi}\braket{1|\psi} = \braket{01|\phi\otimes\psi} = 0
$$
imponendo che $\braket{0|\phi} = 0$ o $\braket{1|\psi} = 0$ (o entrambi). Questo contraddice il fatto che 
$$
\braket{0|\phi}\braket{0|\psi} = \braket{00|\phi\otimes\psi} = {1 \over \sqrt2}
$$
e
$$
\braket{1|\phi}\braket{1|\psi} = \braket{11|\phi\otimes\psi} = {1 \over \sqrt2}
$$
sono entrambi non zero.
Qualsiasi vettore di stato quantistico che non sia un vettore di prodotto rappresenta uno **stato entangled**.

## Operazioni unitarie
Nelle sezioni precedenti di questa lezione, abbiamo usato il prodotto cartesiano per trattare i singoli sistemi come un sistema più grande e singolo. Seguendo la stessa linea di pensiero, possiamo rappresentare le operazioni su più sistemi come matrici unitarie che agiscono sul vettore di stato di questo sistema più grande.

In linea di principio, qualsiasi matrice unitaria le cui righe e colonne corrispondono agli stati classici di qualsiasi sistema a cui stiamo pensando rappresenta un'operazione quantistica valida - e questo vale per i sistemi composti i cui insiemi di stati classici sono prodotti cartesiani degli insiemi di stati classici dei singoli sistemi.
Per esempio, supponiamo che $\Sigma = \{1, 2, 3\}$ e $\Gamma = \{0, 1\}$ il loro prodotto cartesiano si presenta come $\{1, 2, 3\} \times \{0, 1\} = \{(1,0), (1,1), (2,0), (2, 1), (3, 0), (3, 1))\}$, di seguito abbiamo un esempio di matrice unitaria che rappresenta un'operazione su (X, Y):
$$
\begin{matrix}
U\ket{10} = {1 \over 2}\ket{10} + {1 \over 2}\ket{11} + {1 \over 2}\ket{20} + {1 \over 2}\ket{31} 
\\
\\
U\ket{11} = {1 \over 2}\ket{10} + {i \over 2}\ket{11} - {1 \over 2}\ket{20} - {i \over 2}\ket{31}
\\
\\
U = 
\begin{pmatrix}
	{1 \over 2} & {1 \over 2} & {1 \over 2} & 0 & 0 & {1 \over 2} \\
	{1 \over 2} & {i \over 2} & -{1 \over 2} & 0 & 0 & -{i \over 2} \\
	\vdots & \vdots & \vdots & \vdots & \vdots & \vdots
\end{pmatrix}
\end{matrix}
$$
### Operazioni unitarie eseguite in modo indipendente su singoli sistemi
Quando le operazioni unitarie vengono eseguite in modo indipendente su una raccolta di singoli sistemi, l'azione combinata di queste operazioni indipendenti è descritta dal prodotto tensoriale delle matrici unitarie che le rappresentano.
Quindi, se $X_1, \dots, X_n$ sono sistemi quantici, $U_1, \dots, U_n$ sono matrici unitarie che rappresentano le operazione indipendenti sui singoli sistemi, l'azione combinata su $(X_1, \dots, X_n)$ è rappresentata dalla matrice $U_1 \otimes \dots \otimes U_n$ (analogo alle impostazioni probabilistiche).

#### Operazione di SWAP
Supponiamo che X e Y sono sistemi che condividono lo stesso stato classico $\Sigma$.
L'operazione di **SWAP** sulla coppia (X, Y) è l'operazione che scambia il contenuto dei due sistemi, ma lascia i sistemi da soli (quindi X rimane alla sinistra e Y rimane a destra).
Funziona in questo modo per ogni scelta di stati classici $a, b \in \Sigma$:
$$
\text{SWAP}\ket{a}\ket{b} = \ket{b}\ket{a}
$$
Un modo per scrivere la matrice associata a questa operazione utilizzando la notazione Dirac è il seguente:
$$
\text{SWAP} = \sum_{c, d \in \Sigma}\ket{c}\bra{d} \otimes \ket{d}\bra{c}
$$
Vediamo un esempio, per chiarire, quando X e Y sono qubits troviamo:
![[swap.jpeg]]

# Qiskit
## Prodotto tensoriale
La classe `Statevector` ha il metodo `tensor` che ritorna il prodotto tensoriale di se stesso ed un altro `Statevector`.
Ad esempio, di seguito creiamo due vettori di stato che rappresentano $\ket{0}$ e $\ket{1}$ e usano il metodo `tensor` per creare un nuovo vettore $\ket{0} \otimes \ket{1}$
```python
zero, one = Statevector.from_label("0"), Statevector.from_label("1")
zero.tensor(one).draw("latex")
```
>- `zero  = Statevector.from_label("0")` rappresenta lo stato quantistico $\ket{0}$
>- `one = Statevector.from_label("1")`  rappresenta lo stato quantistico $\ket{1}$
>- `zero.tensor(one).draw("latex")` restituisce il prodotto tensoriale tra zero e one, $\ket{0} \otimes \ket{1} = \ket{01}$ in latex, oppure scritto in forma vettoriale (text): $$\ket{0} \otimes \ket{1} = \begin{pmatrix} 0 \\ 1 \\ 0 \\ 0\end{pmatrix}$$


Anche la classe `Operator` ha il metodo `tensor`, vediamo un esempio:
```python
X = Operator([[0, 1], [1, 0]])
I = Operator([[1, 0], [0, 1]])

X.tensor(I)
```

Output $X \otimes I$:
![[qiskit_tensor02.png | center]]
## Misure parziali
Precedentemente abbiamo usato il metodo `measure` per simulare una misurazione del vettore di stato quantistico. Questo metodo restituisce due elementi: il risultato della misurazione simulata e il nuovo `Statevector`.
Di default `measure` misura tutti i qubit nel vettore di stato, ma possiamo fornire un elenco di numeri interi per misurare solo i qubit in quegli indici. Per dimostrare, la cella sottostante crea lo stato
$$W = {1 \over \sqrt3}(\ket{001} + \ket{010} + \ket{100})$$
Il codice seguente simula una misurazione sul qubit più a destra (che ha indice 0). Gli altri due qubit non sono misurati

```python
W = Statevector([0, 1, 1, 0, 1, 0, 0, 0] / sqrt(3))
W.draw("latex")

result, new_sv = W.measure([0]) # measure qubit 0
print(f"Measured: {result}\nState after measurement:")
new_sv.draw("latex")
```

**SPIEGHIAMO**
Ho un vettore di stati quantistici
$$
W =\begin{pmatrix} 
	0 \\ 
	1 \over \sqrt 3 \\ 
	1 \over \sqrt 3 \\ 
	0 \\ 
	1 \over \sqrt 3 \\ 
	0 \\ 
	0 \\ 
	0
\end{pmatrix}
\begin{matrix} 
	\\ 
	\rightarrow 001 \\ 
	\rightarrow 010 \\ 
	\\ 
	\rightarrow 100 \\ 
	\\ 
	\\ 
\end{matrix}$$
Possiamo dunque riscriverlo come $W = {1 \over \sqrt3}(\ket{001} + \ket{010} + \ket{100})$
Viene effettuata una misura del primo qubit a destra nello stato W, cosa accade? Possiamo ottenere come risultato della misura 0 o 1. Nel caso in cui il risultato sia 0 ci troviamo nello stato che ha come primo qubit a destra 0 e questi sono due $\ket{100}$ e $\ket{010}$, mentre nel caso in cui il risultato sia 1 ci troviamo nello stato in cui il primo bit a destra sia 1 ciò solo nel caso $\ket{001}$.
La domanda ora è: Qual è la probabilità di finire nello stato 0 o nello stato 1? Calcoliamo:
$$P(0) = \left|{1 \over \sqrt 3}\right|^2 + \left|{1 \over \sqrt 3}\right|^2 = {2 \over 3}$$
$$P(1) = \left|{1 \over \sqrt 3}\right|^2 = {1 \over 3}$$

Possiamo vedere gli output del codice:
![[qiskit_measure02.1.png]]
![[qiskit_measure02.2.png]]
Nel caso della misura zero abbiamo che le ampiezze ottenute sono ${\sqrt2}\over 2$ questo perché nel momento in cui misuriamo un qubit, il sistema collassa in una sovrapposizione di stati compatibili con la misurazione 0 in questo caso gli stati $\ket{100}$ e $\ket{010}$, pertanto, dopo la misura, il sistema non potrà più includere lo stato $\ket{001}$ poiché non soddisfa la condizione 0.
A questo punto quindi bisogna normalizzare il sistema nuovo collassato, come? Bisogna fare in modo che, come detto nella teoria, la somma delle probabilità sia pari ad 1.
Dato che la somma delle probabilità, calcolata precedentemente è $2 \over 3$ dobbiamo normalizzare il sistema affinché la probabilità totale sia 1.
Per farlo divido ogni coefficiente degli stati per la radice quadrata della probabilità:
$${{1 \over \sqrt 3} \over \sqrt {2 \over 3}}\ket{010} + {{1 \over \sqrt 3} \over \sqrt {2 \over 3}}\ket{100}$$Ottenendo
$${1 \over \sqrt2}\ket{010} + {1 \over \sqrt2}\ket{100}$$
