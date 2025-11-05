[Canale YouTube](https://www.youtube.com/watch?v=42OiBzfdE2o&list=PLOFEBzvs-VvqKKMXX4vbi4EB1uaErFMSO)
```table-of-contents
```
# Informazioni classiche
Consideriamo un sistema fisico che può contenere informazioni, chiamiamolo X.
Ora assumiamo che X si può trovare in un numero finito di stati classici in qualsiasi momento.
Quando ci riferiamo ad un stato classico, intendiamo una configurazione del sistema che può essere riconosciuto e descritto senza ambiguità, incertezze o errori.
Chiamiamo il set di stati che l'informazione può assumere come: $\Sigma$.
*Esempio:*
- Se X è un bit, gli stati classici che può assumere è $\Sigma = {0, 1}$

In alcuni casi possiamo avere incertezza sullo stato classico di un sistema, dove ogni stato classico ha una certa probabilità associato ad esso.
Per esempio, se X è un bit, allora forse è nello stato classico 0 con probabilità 3/4 e nello stato classico 1 con probabilità 1/4, questo è lo **stato probabilistico** di X.
Un modo per rappresentare questo stato probabilistico è tramite un vettore colonna, che chiameremo vettore probabilità, dove tutti i suoi elementi sono ==numeri reali positivi== e la ==loro somma è sempre uguale a 1==.
## Notazione Dirac
A questo punto diventa utile introdurre la notazione Dirac, essenziale per aiutarci a descrivere l'informazione quantistica.
Come descritto precedentemente, abbiamo $\Sigma$, set di stati classici, assumiamo ora che abbiamo anche un ordinamento di questi stati, ad esempio in ordine alfabetico binario.
### ket
A questo punto denotiamo $\ket{a}$ \[ket di a\] il **vettore colonna** che ha 1 nel punto in cui corrisponde la $a \in \Sigma$ e 0 per tutti gli altri elementi di $\Sigma$.
*Vediamo esempi per chiarire:*
Se $\Sigma = \{0,1\}$ allora:
$$
\ket{0} = 
\begin{pmatrix}
	1 \\
	0
\end{pmatrix} 
\quad and \quad
\ket{1} =
\begin{pmatrix}
	0 \\
	1
\end{pmatrix} 
$$

Se $\Sigma = \{\clubsuit,\diamondsuit, \heartsuit, \spadesuit \}$ allora: 

$$
\ket{\clubsuit} = 
\begin{pmatrix}
	1 \\
	0 \\
	0 \\
	0
\end{pmatrix} 
\quad
\ket{\diamondsuit} = 
\begin{pmatrix}
	0 \\
	1 \\
	0 \\
	0
\end{pmatrix}
\quad
\ket{\heartsuit} = 
\begin{pmatrix}
	0 \\
	0 \\
	1 \\
	0
\end{pmatrix}
\quad
\ket{\spadesuit} = 
\begin{pmatrix}
	0 \\
	0 \\
	0 \\
	1
\end{pmatrix}
$$
Vettori di quella forma vengono chiamati **vettori standard base**, ogni vettore può essere espresso in modo univoco come una combinazione lineare di vettori standard base.
*Ad esempio tornando a quello iniziale:*
$$
\begin{pmatrix}
	3 \over 4 \\
	1 \over 4 
\end{pmatrix} = {3 \over 4}\, \ket{0} + {1 \over 4}\, \ket{1} 
$$
### bra
A questo punto definiamo $\bra{a}$ \[bra di a\] come il **vettore riga** che ha 1 in corrispondenza di ogni $a \in \Sigma$ e 0 nel resto.
*Vediamo un veloce esempio:*
$$
\ket{0} = 
\begin{pmatrix}
	1 & 0
\end{pmatrix} 
\quad and \quad
\ket{1} =
\begin{pmatrix}
	0 & 1
\end{pmatrix} 
$$
Ora, se dovessimo moltiplicare un vettore riga per un vettore colonna otterremmo uno scalare, in particolare se moltiplichiamo il vettore $\bra{a}$ per il vettore $\ket{b}$ due cose interessanti accadono: 
$$
\braket{a|b} = 
\begin{cases}
	 1 \quad a = b \\
	 0 \quad a \neq b
 \end{cases}
$$
>Questa operazione può essere rappresentata tramite la seguente dicitura: $\braket{a | b}$ \[braket\].

Nel caso in cui moltiplichiamo un vettore colonna con un vettore riga otteniamo una matrice $dim(a \times b)$.
$$
\begin{pmatrix}
	* \\
	* \\
	\vdots \\
	*
\end{pmatrix} 
\begin{pmatrix}
	* & * & \dots & *
\end{pmatrix} =
\begin{pmatrix}
	* & * & \dots & * \\
	* & * & \dots & * \\
	\vdots & \vdots & \ddots & \vdots\\
	* & * & \dots & *
\end{pmatrix} 
$$
Otteniamo dunque un matrice: $\ket{b}\bra{a}$ che ha 1 in tutti gli elementi $(a, b) \in \Sigma$ e 0 nel resto.
## Operazioni Deterministiche
Parliamo ora delle operazioni classiche che possono essere applicate su di un sistema classico, partendo dalle operazioni deterministiche.
Le operazioni deterministiche vengono descritte tramite funzioni, della forma $f: \Sigma \rightarrow \Sigma$, questo significa trasformare $a$ in $f(a)$ per ogni $a \in \Sigma$.
### ket
Data una qualsiasi funzione $f: \Sigma \rightarrow \Sigma$, esiste un matrice $M$ che soddisfa la seguente uguaglianza:
$$M \, \ket{a} = \ket{f(a)} \quad \forall a\in \Sigma$$
Questa $M$ è una matrice in cui si ha solamente un 1 per ogni colonna e 0 nel resto della matrice, abbiamo dunque:
$$
M(b, a) = 
 \begin{cases}
	 1 \quad b = f(a) \\
	 0 \quad b \neq f(a)
 \end{cases}
 $$
 
 dove $b$ corrisponde alle righe e $a$ corrisponde alle colonne.
 
 Quindi l'azione che stiamo spiegando è semplicemente descrivibile da una moltiplicazione matrice per vettore: 
$$v \rightarrow Mv$$
 *Vediamo ora un esempio:*
 Per $\Sigma = \{0, 1\}$, abbiamo quattro funzioni del tipo $f: \Sigma \rightarrow \Sigma$:	

$$ 
\begin{array}{cc} 
	\begin{array}{c|c} 
		a & f_1(a)\\ \hline 
		0 & 0 \\
		1 & 0 
	\end{array} 
	&&&
	\begin{array}{c|c} 
		a & f_2(a)\\ \hline 
		0 & 0 \\
		1 & 1 
	\end{array} 
	&&&
	\begin{array}{c|c} 
		a & f_3(a)\\ \hline 
		0 & 1 \\
		1 & 0 
	\end{array} 
	&&&
	\begin{array}{c|c} 
		a & f_4(a)\\ \hline 
		0 & 1 \\
		1 & 1 
	\end{array} 
\end{array} 
$$
Usando la formula descritta precedentemente nella creazione di $M(b, a)$, troviamo le seguenti matrici corrispondenti:
$$
\begin{matrix}
M_1 = \begin{pmatrix}
		1 & 1 \\
		0 & 0
	  \end{pmatrix}
&
M_2 = \begin{pmatrix}
		1 & 0 \\
		0 & 1
	  \end{pmatrix}
&
M_3 = \begin{pmatrix}
		0 & 1 \\
		1 & 0
	  \end{pmatrix}
&
M_4 = \begin{pmatrix}
		0 & 0 \\
		1 & 1
	  \end{pmatrix}
\end{matrix}
$$
Di conseguenza possiamo stabilire che anche l'uguaglianza: $M \, \ket{a} = \ket{f(a)} \; \forall a\in \Sigma$ sia veritiera.

>Dimostriamo:
> ![[dimostrazione.jpeg]]

### bra
La matrice $M$, includendo la notazione bra, può essere espressa come: 
$$M = \sum_{b \, \in \, \Sigma} \, \ket{f(b)}\bra{b}$$
Quindi arriviamo a dire che:
$$M \ket{a} = \Biggl( \; \sum_{b \, \in \, \Sigma} \, \ket{f(b)}\bra{b} 
\Biggr) \ket{a} = \sum_{b \, \in \, \Sigma} \, \ket{f(b)}\braket{b | a} = \ket{f(a)}$$
## Misurazione di uno stato probabilistico
Ora consideriamo brevemente cosa succede se misuriamo un sistema quando è in uno stato probabilistico. Misurando un sistema, intendiamo che guardiamo il sistema e riconosciamo in modo inequivocabile qualunque sia lo stato classico in cui si trova. Intuitivamente, non possiamo mai "vedere" un sistema in uno stato probabilistico; una misurazione produrrà esattamente uno degli stati classici consentiti.
La misurazione cambia la nostra conoscenza del sistema, e quindi cambia lo stato probabilistico che associamo a quel sistema: se riconosciamo che X si trova nello stato classico $a \in \Sigma$, il nuovo vettore di probabilità che rappresenta la nostra conoscenza di X diventa un vettore che ha un 1 in corrispondenza di $a$ e 0 nel resto. Questo vettore indica che X si trova nello stato classico $a$ con certezza, lo stato probabilistico viene rappresentato dal vettore $\ket{a}$.
### Operazioni probabilistiche
Le operazioni probabilistiche sono classiche operazioni, ma che introducono randomicità o incertezza.
Questo tipo di operazioni è descritto da matrici stocastiche, in cui gli elementi in input sono numeri reali positivi e la somma degli elementi di ogni colonna è uguale a 1, possiamo dire che ogni colonna della matrice forma il vettore probabilità.
*Esempio:*
Operazione probabilistica su un bit:
- se lo stato classico è 0, non fare nulla
- se lo stato classico è 1, cambia il bit con probabilità $1 \over 2$.
Vediamo la matrice stocastica come viene formata:
$$
{1 \over 2} 
\begin{pmatrix}
	1 & 1  \\
	0 & 0 
\end{pmatrix}
+{1 \over 2} 
\begin{pmatrix}
	1 & 0 \\
	0 & 1
\end{pmatrix}
=
\begin{pmatrix}
	1 & 1 \over 2 \\
	0 & 1 \over 2
\end{pmatrix}
$$
Nella prima colonna abbiamo la rappresentazione in cui lo stato classico si trova in 0, mentre nella seconda colonna abbiamo il caso in cui il bit corrisponde allo stato 1 dove la probabilità di ogni stato è pari a $1  \over 2$.

# Informazioni Quantiche
Uno stato quantistico di un sistema è rappresentato da un vettore colonna, simile agli stati probabilistici. Come prima, gli indici del vettore etichettano gli stati classici del sistema. I vettori che rappresentano gli stati quantistici sono caratterizzati da queste due proprietà:
1. **Le voci di un vettore di stato quantistico sono numeri complessi.**
2. **La somma dei valori assoluti al quadrato delle voci di un vettore di stato quantistico è 1.**

Solitamente gli stati quantistici vengono rappresentati tramite $\ket{0}$ o $\ket{1}$, vettori in cui gli indici corrispondono ai classici stati 0 e 1.
Per riferirci in modo generico a questo tipo di vettori viene utilizzata la notazione: $\ket{\psi}$, per un qualunque vettore $\ket{\psi}$, il suo corrispettivo vettore $\bra{\psi}$ è il vettore colonna trasposto:
$$
\bra{\psi} = \ket{\psi}^\dagger
$$
## Misurazione di uno stato quantistico
L'obiettivo è quello di estrarre informazioni classiche da vettori di stato quantistici.
Misurazioni basiche standard:
- I possibili output sono stati classici.
- **La probabilità che ogni stato classico esca è pari al valore assoluto al quadrato del corrispondente vettore di stati quantistici in input.**

*Esempio:*
Misuriamo lo stato quantico del seguente sistema:
$$\ket{+} = {1 \over \sqrt{2}} \ket{0} +{1 \over \sqrt{2}} \ket{1}$$
Calcoliamo la probabilità che escano 0 o 1:
$$
\Pr(0) = \Biggl| {1 \over \sqrt{2}}\Biggr|^2 = {1 \over 2}\qquad
\Pr(1) = \Biggl| {1 \over \sqrt{2}}\Biggr|^2 = {1 \over 2}
$$
Quando misuriamo un sistema che si trova in uno stato quantico, lo stato cambierà, in particolare se misurando un sistema otteniamo un classico stato $a$, il nuovo stato quantistico diventerà $\ket{a}$.

*Esempio:* 
Avendo un sistema formato nel seguente modo:
$$
{1 + 2i \over 3}\ket{0} - {2 \over 3}\ket{1}
$$
Se misuriamo questo sistema con probabilità pari a $5 \over 9$ otterremo l'output 0 che cambierà lo stato quantistico in $\ket{0}$, se misurassimo il sistema con probabilità $4 \over 9$ l'output sarebbe 1 e quindi lo stato quantistico cambierebbe in $\ket{1}$.

## Operazioni unitarie
Finora, potrebbe non essere evidente perché l'informazione quantistica sia fondamentalmente diversa dall'informazione classica. Cioè, quando viene misurato uno stato quantistico, la probabilità di ottenere ogni stato classico è data dal valore assoluto al quadrato della voce vettoriale corrispondente, quindi perché non registrare semplicemente queste probabilità in un vettore di probabilità?
La risposta, almeno in parte, è che l'insieme di operazioni consentite che possono essere eseguite su uno stato quantistico è diverso da quello che è per l'informazione classica. Simile all'impostazione probabilistica, le operazioni sugli stati quantistici sono mappature lineari, ma piuttosto che essere rappresentate da matrici stocastiche come nel caso classico, le operazioni sui vettori di stato quantistico sono rappresentate da matrici unitarie.

>Una matrice quadrata $U$ che ha numeri complessi in input è unitaria se soddisfa la seguente uguaglianza:
>$$U^\dagger U = I = UU^\dagger$$
>dove $I$ = matrice identità.

Esiste anche un modo simile per definire le matrici unitarie:

>Una matrice $U$ $n \times n$ è unitaria se:
>$$||Uv|| = ||v||$$
>per ogni ogni vettore $v$ colonna di dimensione $n$ con numeri complessi in input.
>Se $v$ è un vettore di stati quantistici allora anche $Uv$ è un vettore di stati quantistici.

### Qubits
1. **Operazioni Pauli**
$$
I = 
\begin{pmatrix}
	1 & 0 \\
	0 & 1
\end{pmatrix}
\qquad
\sigma_x = 
\begin{pmatrix}
	0 & 1 \\
	1 & 0
\end{pmatrix}
\qquad
\sigma_y = 
\begin{pmatrix}
	0 & -i \\
	i & 0
\end{pmatrix}
\qquad
\sigma_z = 
\begin{pmatrix}
	1 & 0 \\
	0 & -1
\end{pmatrix}
$$
L'operazione $\sigma_x$ è anche chiamata **flip bit** e l'operazione $\sigma_z$ è anche chiamata **phase flip**:
$$
\begin{matrix}
\sigma_x \ket{0} = \ket{1} && \sigma_z \ket{0} = \ket{0}\\
\sigma_x \ket{1} = \ket{0} && \sigma_z \ket{1} = -\ket{1}
\end{matrix}
$$
Possiamo notare come in $\sigma_x$ il bit assume lo stato 1 quando si trova in zero e viceversa.

2.  **Operazione Hadamard**
$$
H = 
\begin{pmatrix}
	{1 \over \sqrt{2}} & {1 \over \sqrt{2}} \\
	{1 \over \sqrt{2}} & -{1 \over \sqrt{2}}
\end{pmatrix}
$$
3. **Operazioni Phase**
$$
P_\theta = 
\begin{pmatrix}
	1 & 0 \\
	0 & e^{i\theta}
\end{pmatrix}
$$
Per un qualsiasi numero reale $\theta$.
*Esempio:*
$$
S = P_{\pi \over 2} = 
\begin{pmatrix}
	1 & 0 \\
	0 & i
\end{pmatrix} 
\qquad
T = P_{\pi \over 4} = 
\begin{pmatrix}
	1 & 0 \\
	0 & {1+i \over \sqrt2}
\end{pmatrix} 
$$
# Qiskit
## Stati, misurazioni e operazioni
La classe di Qiskit `Statevector` fornisce le funzionalità per definire e manipolare i vettori di stato quantistico.

``` python
from qiskit.quantum_info import Statevector
from numpy import sqrt

u = Statevector([1 / sqrt(2), 1 / sqrt(2)])
v = Statevector([(1 + 2.0j) / 3, -2 / 3])
w = Statevector([1 / 3, 2 / 3])

print("State vectors u, v, and w have been defined.")
```

La classe `Statevector` fornisce il metodo `draw` per visualizzare i vettori, includendo le opzioni `latex` e `text` per visualizzarli in modo differente.

```python
display(u.draw("latex"))
display(v.draw("text"))
```

output:
${\sqrt{2} \over 2}\ket{0} + {\sqrt{2} \over 2}\ket{1}$

$[\quad0.33333333+0.66666667j,-0.66666667+0.j \qquad]$

Inoltre la classe `Statevector` include il metodo `is_valid` che controlla se un dato vettore è un vettore di stato quantistico valido.
```python
display(u.is_valid()) #true
display(w.is_valid()) #false
```

w non è un vettore di stato quantistico valido perché i coefficienti non rispettano la condizione di normalizzazione richiesta, ovvero un vettore di stato quantistico $\ket{\psi} = [a, b]$ è valido se la somma dei moduli quadrati dei suoi coefficienti è pari a 1: $|a|^2 + |b|^2 = 1$.

Simuliamo ora una **misurazione** utilizzano `Statevector`:
``` python
v = Statevector([(1 + 2.0j)/3, -2/3])
v.draw("latex")
```
$\bigl({1 \over 3} + {2i \over 3}\bigr) \ket{0} - {2 \over 3}\ket{1}$ 

``` python
v.measure()
```

```output
('1',
 Statevector([ 0.+0.j, -1.+0.j],
             dims=(2,)))
```
Spiegazione risultato:
Il primo elemento `1`, indica che il risultato della misurazione è collassato nello stato $\ket{1}$, dunque ora il nuovo vettore  di stato quantistico si trova in $(0, -1)$, la fase globale non è rilevante (-).

La classe `Statevector` in oltre tramite il metodo `sample_counts` consente la simulazione di qualsiasi numero di misurazioni sul sistema. Per esempio, il codice seguente mostra il risultato della misurazione del vettore v 1000 volte, che (con alta probabilità) si traduce in 0 circa 5 su 9 volte (o circa 568 delle 1000 prove) e 1 circa 4 su 9 volte  (o circa 432 delle 1000 prove).
```python
from qiskit.visualization import plot_histogram

statistics = v.sample_counts(1000)
display(statistics)
plot_histogram(statistics)
```
![[plot_simulation.png]]

Le **operazioni unitarie** possono essere definite ed eseguite su vettori di stato in Qiskit utilizzando la classe `Operator`:

```python
from qiskit.quantum_info import Operator

X = Operator([[0, 1], [1, 0]])
Y = Operator([[0, -1.0j], [1.0j, 0]])
Z = Operator([[1, 0], [0, -1]])
H = Operator([[1 / sqrt(2), 1 / sqrt(2)], [1 / sqrt(2), -1 / sqrt(2)]])
S = Operator([[1, 0], [0, 1.0j]])
T = Operator([[1, 0], [0, (1 + 1.0j) / sqrt(2)]])

v = Statevector([1, 0])

v = v.evolve(X)

v.draw("latex")
```

Output:
![[qiskit_ex.jpeg]]

I circuiti quantistici non saranno introdotti fino alla Lezione 3, ma possiamo comunque sperimentare la composizione di operazioni unitarie di qubit usando la classe `QuantumCircuit`. In particolare, possiamo definire un circuito quantistico (che in questo caso sarà semplicemente una sequenza di operazioni unitarie eseguite su un singolo qubit) come segue:

```python
from qiskit import QuantumCircuit

circuit = QuantumCircuit(1)

circuit.h(0)
circuit.t(0)
circuit.h(0)
circuit.t(0)
circuit.z(0)

circuit.draw("mpl")
```

![[qiskit_circuit01.png]]
Le operazioni vengono applicate in sequenza, iniziando a sinistra e finendo a destra nella figura. Inizializziamo prima un vettore di stato quantistico iniziale e poi evolviamo quello stato in base alla sequenza di operazioni.

```python
ket0 = Statevector([1, 0])

v = ket0.evolve(circuit)

v.draw("text")
```

Infine, simuliamo il risultato dell'esecuzione di questo esperimento (cioè, preparando lo stato $\ket{0},$ applicando la sequenza di operazioni rappresentata dal circuito e misurando) 4000 volte.

```python
statistics = v.sample_counts(4000)
plot_histogram(statistics)
```

![[plot_circuit01.png]]

>I diversi gate del circuito rappresentano diverse operazioni da eseguire sullo `statevector` 'ket0'.
>- h rappresenta l'operazione Hadamard
>- t rappresenta una rotazione di $\pi \over 4$ (45 gradi) attorno all'asse Z della sfera di Bloch
>- z rappresenta una rotazione di $\pi$ (180 gradi) attorno all'asse Z della sfera di Bloch
