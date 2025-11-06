```table-of-contents
```
# Analisi statica
Un esempio meno comune di programmi per computer che manipolano altri programmi. Un analizzatore statico è un programma che accetta come input un programma e fornisce in output informazioni sui suoi possibili comportamenti, senza effettivamente eseguirlo. In realtà l'analisi statica copre anche l'analisi sintattica ce ricerca pattern predefiniti, ma in questo caso ci concentriamo più sull'analisi semantica.

>Interpretazione astratta (Cousot): è una teoria generale dell'approssimazione della semantica formale dei programmi. Si tratta di uno strumento prezioso per dimostrare la correttezza di un'analisi statica, poiché consente di esprimere matematicamente il collegamento tra l'output di un'analisi pratica e approssimativa e la semantica originale e non calcolabile del programma. Inoltre, l'interpretazione astratta consente di derivare, dalla semantica del programma originale e da una scelta di astrazione, un'analisi statica corretta per costruzione. Infine, la nozione di astrazione è un cittadino di prima classe in Abstract Interpretation: le astrazioni possono essere manipolate e combinate, portando a progetti modulari per analisi statiche. In questo tutorial, progetteremo analisi statiche tramite Abstract Interpretation. Il resto di questo capitolo presenta informalmente analisi statiche tramite Abstract Interpretation per derivare semplici proprietà numeriche sulle variabili di un programma.
## Presentazione Informale
Vediamo un semplice esempio di una funzione che calcola il modulo di due interi ($A\%B$):
```C
  int mod(int A, int B) { 
1:    int Q = 0;
2:    int R = A;
3:    while (R >= B) {
4:        R = R - B;
5:        Q = Q + 1;
6:    } 
7:    return R; 
  }
```

Possiamo riassumere i passaggi della funzione, passando come parametri A = 10 e B = 3, nel seguente modo: 
$$
\begin{matrix*}[l]
\braket{1: 10, 3} \rightarrow \braket{2: 10, 3, 0} \rightarrow \braket{3: 10, 3, 0, 10} \\
\rightarrow \braket{4: 10, 3, 0, 10} \rightarrow \braket{5: 10, 3, 0, 7} \rightarrow \braket{6: 10, 3, 1, 7} \\
\rightarrow \braket{4: 10, 3, 1, 7} \rightarrow \braket{5: 10, 3, 1, 4} \rightarrow \braket{6: 10, 3, 2, 4} \\
\rightarrow \braket{4: 10, 3, 2, 4} \rightarrow \braket{5: 10, 3, 2, 1} \rightarrow \braket{6: 10, 3, 3, 1} \rightarrow \braket{7: 10, 3, 3, 1}
\end{matrix*}
$$
dove $\braket{l: a, b, q, r}$  rappresentano rispettivamente $l$ il numero della linea di codice a cui stiamo facendo riferimento, $a$ il parametro A della funzione mod, $b$ il parametro B della funzione mod, $q$ il quoziente Q e $r$ il resto R della funzione.

### Analisi del segno
La prima analisi tenta di stabilire il segno delle variabili, un metodo nativo, che assicura tutti i possibili comportamenti del programma vengano considerati, è quello di simulare tutte le possibili esecuzioni "runnando" il programma e quindi raccogliere i segni dei valori delle variabili durante queste esecuzioni, ovviamente questo non è efficiente.
Riprendiamo l'esempio recedente:
```C
  //@requires A >= 0 && B >= 0
  int mod(int A, int B) { 
1:    //[A = (>=0), B = (>=0)]
	  int Q = 0;
2:    //[A = (>=0), B = (>=0), Q = 0]
	  int R = A;
3:    //[A = (>=0), B = (>=0), Q = 0, R >= 0]
	  while (R >= B) {
4:        //[A = (>=0), B = (>=0), Q = (>=0), R = (>=0)]
		  R = R - B;
5:        //[A = (>=0), B = (>=0), Q = (>=0), R = TOP]
		  Q = Q + 1;
6:        //[A = (>=0), B = (>=0), Q = (>=0), R = TOP]
	  } 
7:    //[A = (>=0), B = (>=0), Q = (>=0), R = TOP]
	  return R; 
  }
```

Un principio chiave dell'interpretazione astratta è la sostituzione di queste esecuzioni effettive, cosiddette concrete, con quelle astratte. Per un'analisi dei segni, sostituiamo gli stati concreti che mappano ogni variabile a un valore intero con uno stato astratto che mappa ogni variabile a un segno.
Quindi partendo da valori positivi di A e B vediamo una possibile esecuzione:
$$
\begin{matrix*}[l]
\braket{1: (\geq0), (\geq0)} \rightarrow \braket{2: (\geq0), (\geq0), 0} \rightarrow \braket{3: (\geq0), (\geq0), 0, (\geq0)} \\
\rightarrow \braket{4: (\geq0), (\geq0), 0, (\geq0)} \rightarrow \braket{5: (\geq0), (\geq0), 0, \top} \\ \rightarrow \braket{6: (\geq0), (\geq0), (\geq0), \top}
\rightarrow \braket{4: (\geq0), (\geq0), (\geq0), \top} \\ \rightarrow \braket{5: (\geq0), (\geq0), (\geq0), \top} \rightarrow \braket{6: (\geq0), (\geq0), (\geq0), \top} \\ \rightarrow \braket{7: (\geq0), (\geq0), (\geq0), \top}
\end{matrix*}
$$
dove $\top$ indica che il segno non è conosciuto, quindi la variabile può essere positiva o negativa, notiamo che alla fine della funzione non abbiamo informazioni sulla variabile R, quando in effetti R è sempre positiva, questo perché nella funzione abbiamo R = R - B, quindi ($\geq0$) - ($\geq0$) = $\top$, in quanto potremmo provare che R sia positiva se e solo se R $\geq$ B, ma questa non è un'informazione di segno è come se non fossimo a conoscenza di essa.
> Abbiamo utilizzato un tipo di astrazione NON-relazionale

Se volessimo utilizzare un dominio dei segni relazionale, sarebbe sì molto più preciso ma perderei in **efficienza**, vediamo il solito esempio: 

```C
  //@requires A >= 0 && B >= 0
  int mod(int A, int B) { 
1:    //[A = (>=0), B = (>=0)]
	  int Q = 0;
2:    //[A = (>=0), B = (>=0), Q = 0]
	  int R = A;
3:    //[A = (>=0), B = (>=0), Q = 0, R = A]
	  while (R >= B) {
4:        //[A = (>=0), B = (>=0), Q = (>=0), R >= B]
		  R = R - B;
5:        //[A = (>=0), B = (>=0), Q = (>=0), R >= 0]
		  Q = Q + 1;
6:        //[A = (>=0), B = (>=0), Q = (>=0), R >= 0]
	  } 
7:    //[A = (>=0), B = (>=0), Q = (>=0), 0 <= R < B]
	  return R; 
  }
```
Notiamo che R alla fine della funzione è un valore più preciso di $\top$ in quanto è un valore che si posiziona tra 0 e B.

### Analisi con intervalli
Un ulteriore esempio, il seguente, è annotato con invarianti calcolati in un'altra astrazione, gli intervalli, che deduce limiti variabili: un limite inferiore e un limite superiore.

```C
   A = 0; B = 0;
1: //[A \in [0, 0], B \in [0, 0]]
   while 
2:     //[A \in [0, 100], B \in [0, +inf.]]
   (A < 100){
3:    //[A \in [0, 99], B \in [0, +inf]]
	  A = A + 1;
4:    //[A \in [1, 100], B \in [0, +inf.]]
	  B = B + 1;
	  //[A \in [1, 100], B \in [1, +inf.]]
   }
   //[A \in [100, 100], B \in [0, +inf.]]
```

Possiamo notare come A si ferma a 100 in quanto il while mette un vincolo ad A arrivando ad un valore massimo di 100, nel caso di B non abbiamo un vincolo su di essa che la limiti e quindi verrà incrementata all'infinito avendo un range da \[0; +inf].

### Precisione
Vedendo i due esempi (con segno non relazionale e con segno relazionale) abbiamo due risultati di analisi statica differenti, questo dipende dal dominio astratto di interpretazione, ma rappresenterà sempre una sovra-approssimazione dell'insieme dei possibili stati del programma.
La Figura sottostante lo illustra mostrando un insieme di punti planari (che rappresentano, ad esempio, un insieme di stati concreti del programma su due variabili) e il suo migliore contenimento in un poliedro (nel dominio della disuguaglianza affine), una scatola (nel dominio dell'intervallo) e un quarto di piano (nel dominio del segno).

![[planar_points.png]]

### Soundness (solidità)
La **solidità** è un concetto fondamentale nei metodi formali e nell'analisi statica, che garantisce che i risultati prodotti dall'analisi siano sempre affidabili per quanto riguarda il comportamento effettivo del programma.
In un'analisi statica si calcolano delle proprietà astratte che descrivono il comportamento possibile di un programma, la solidità implica che queste proprietà sono **sempre corrette** rispetto a ciò che può accadere realmente durante l'esecuzione del programma.
In poche parole, tutti gli stati possibili durante l'esecuzione reale del programma sono contenuti negli stati descritti dall'analisi ed essa può includere anche stati "in più" rispetto a quelli realmente raggiungibili (questo accade perché usiamo delle over-approssimazioni, ossia rappresentazioni che semplificano e ampliano l'insieme degli stati possibili per renderli più facili da calcolare).

Se l'analisi rileva che un qualche stato raggiungibile (lo stato che il programma può attraversare durante la sua esecuzione) non appartiene all'insieme degli stati sicuri, abbiamo identificato un possibile errore (ad esempio, un bug o una violazione di sicurezza).
$$\text{Stati raggiungibili} \subseteq \text{Stati sicuri}$$
Vedendo l'immagine, se l'insieme degli stati astratti A (determinati dall'analisi) è interamente contenuto nell'insieme degli stati sicuri S (specificati esplicitamente o implicitamente), possiamo concludere che il programma è corretto rispetto alla specifica, se l'analisi determina che lo stato astratto A non rientra nella specifica S, l'analisi non può garantire la correttezza del programma. In questo caso, dobbiamo distinguere due possibilità:
- Falso allarme: l'analisi non è in grado di dimostrare la correttezza perché la sovra-approssimazione è troppo grossolana. In altre parole, ci sono stati inclusi nell'insieme astratto che non corrispondono a stati effettivamente raggiungibili dal programma (false alarm).
- Il programma è effettivamente difettoso: esiste un'esecuzione reale che viola la specifica (unsound analysis).

![[soundness.png]]

## Connessioni di Galois
Una connessione di Galois è una relazione tra due domini (uno concreto e uno astratto) definita da due funzioni:
- $\gamma_b$ (mappa di concretizzazione): traduce un elemento del dominio astratto nel corrispondente insieme concreto.
- $\alpha_b$ (mappa di astrazione): traduce un insieme concreto nel corrispondente elemento astratto.
Queste due mappe devono rispettare una relazione fondamentale:
$$\gamma_b(X^{\sharp}) \subseteq C \Longleftrightarrow X^{\sharp}_b \sqsubseteq_b^{\sharp}\alpha_b(C)$$
dove:
- $X_b^{\sharp}$ è un elemento del dominio astratto,
- $C$ è un sottoinsieme del dominio concreto,
- $\sqsubseteq_b^{\sharp}$ è una relazione (qui un pre-ordine) sul dominio astratto.
Questa relazione garantisce che $\alpha_b$​ e $\gamma_b$​ siano "coordinate" tra loro, mantenendo la consistenza tra le due rappresentazioni.
## Il dominio delle congruenze
ll **Congruence Domain** è un dominio astratto utilizzato nell'analisi statica dei programmi, progettato specificamente per lavorare con valori interi. L'idea principale di questo dominio è rappresentare insiemi di valori interi come congruenze modulari. Questo significa che possiamo descrivere il valore di una variabile X usando una relazione del tipo:
$$X \in a\mathbb{Z}+b$$dove:
- a è un numero intero maggiore o uguale a zero (detto modulo, cioè $\in \mathbb{N}$).
- $\mathbb{Z}$ rappresenta l'insieme di tutti i numeri interi.
- b è un numero intero che rappresenta il resto (o offset).
L'espressione $a\mathbb{Z}+b$ descrive l'insieme di tutti i numeri X tali che $X= a \cdot k + b$, dove k è un intero arbitrario.
In termini semplici, $X \in a\mathbb{Z}+b$ significa che X è un numero intero che soddisfa la congruenza $X\equiv b (\text{mod} \; a)$, ad esempio:
**Se a = 4 e b = 1, allora $X \in 4\mathbb{Z}+1$ descrive l'insieme {1, 5, 9, 13, …}, cioè tutti i numeri interi che danno resto 1 quando divisi per 4.**
L'insieme dei valori astratti viene definito come: 
$$\mathcal{B}^{\sharp} = \{(a\mathbb{Z}+b) \; | \; a \in \mathbb{N}, \; b \in \mathbb{Z}\} \; \cup \; \{\bot_b^{\sharp}\}$$
L'insieme più grande che posso rappresentare è $1\mathbb{Z}+0$, cioè tutti i numeri interi, rappresentando così il caso più generale, nel caso in cui voglio rappresentare un singolo elemento {c} può essere rappresentato tramite la notazione $0\mathbb{Z}+c$, questo perché il valore $\mathbb{Z}$ viene annullato dallo 0 e quindi mi resta solamente il valore c.
Viene poi aggiunto il valore di insieme vuoto rappresentato dall'insieme $\{\bot_b^{\sharp}\}$ che viene introdotto esplicitamente in quanto la notazione $a\mathbb{Z}+b$ da sola non può rappresentare l'insieme vuoto, poiché qualsiasi valore di a e b descrive sempre almeno un valore (o più valori).

### Reticolo
![[lattice.png|300]]
Tale reticolo si basa su alcuni risultati aritmetici di base riguardanti i divisori e i cosiddetti coset. Gli interi diversi da zero formano un reticolo (non completo) per la divisibilità: ($\mathbb{N}^*$, |, mcm, mcd), dove |  , mcm e mcd sono il minimo comune multiplo e il massimo comune divisore.
La non completezza del reticolo non dipende dall'assenza di infimi, ma dalla possibile assenza di supremi (mcm) per **sottoinsiemi infiniti**. Ad esempio, l'insieme di tutti i numeri primi {2,3,5,7,… } non ha un mcm finito in $\mathbb{N}^*$, perché nessun numero finito è divisibile per tutti i numeri primi. Questo è ciò che rende il reticolo non completo.
Dobbiamo prima estendere questo reticolo al caso 0, che è utile nel dominio per rappresentare i singleton:
- Relazione di divisibilità:
	$y|y'$ $\Longleftrightarrow$ y divide y' ($y \leq y'$) abbiamo $\exists k \in \mathbb{N}:y' = k \cdot y$
	```Esempio 
	y = 2
	y' = 6 
	6 = k * 2 -> k = 3
	-------------------------
	y = 10
	y' = 4
	4 = k * 10 -> k non appartiene ad N
	```
	con questo metodo possiamo includere $\forall y:y|0$, al contrario non possiamo includere $\forall y: 0|y$, dove y > 0 in quanto non esiste $k$ per cui $y = k \cdot 0$.
	
- Operazione JOIN ($\vee$):
	Il mcm tra $y$ e $y'$ è il più piccolo numero $z$ divisibile sia da $y$ che da $y′$, dunque abbiamo che il join ($\vee$) nel concreto esegue il mcm tra due numeri interi:
	```Esempio
	4 V 6 = 12
	2 V 4 = 4
	5 V 15 = 15
	```
	Questo tipo di relazione possiamo farla valere anche con lo 0, in quanto per qualsiasi numero $y$ vale: $y \vee 0 = 0 \vee y = 0$, perché 0 è divisibile da qualsiasi numero.
	
- Operazione MEET ($\wedge$):
	Il mcd tra $y$ e $y'$ è il più grande numero che divide sia $y$ che $y'$, dunque abbiamo che il meet ($\wedge$) nel concreto esegue il mcd tra due numeri interi:
	```Esempio
	4 ∧ 6 = 2
	9 ∧ 15 = 3
	```
	Questo tipo di relazione possiamo farla valere anche con lo 0, in quanto per qualsiasi numero $y$ vale: $y \wedge 0 = 0 \wedge y = 0$, perché 0 non divide nessun numero diverso da sé stesso.
	
- Congruenza modulo $y$:
	La relazione $x \equiv x' [y]$ significa che la differenza $|x - x'|$ è divisibile per $y$.
	```Esempio
	7 ≡ 1 [3] -> |7 - 1| = 6, 6 è divisibile per 3
	6 ≡ 2 [2] -> |6 - 2| = 4, 4 è divisibile per 2
	```
	Se $y = 0$ allora $x \equiv x' [0]$ deve avere $x = x'$ poiché non esiste divisibilità per 0.
	```Esempio
	7 ≡ 1 [0] -> |7 - 1| = 6, 6 è divisibile per 0? NO
	5 ≡ 5 [0] -> |5 - 5| = 0, 0 è divisibile per 0? SI	
	```

>**Abbiamo quindi incluso lo 0 estendendo il reticolo anche in quel caso e rendendolo completo, quando viene applicata la congruenza del modulo con 0 i numeri devono essere uguali.**

Quindi, ($\mathbb{N}$, |, $\vee$, $\wedge$, 1, 0) è un reticolo distributivo completo. Possiamo definire in cima a questo reticolo aritmetico una struttura reticolare completa su ($\mathcal{B}^{\sharp}, \sqsubseteq_b^{\sharp}, \sqcup_b^{\sharp}, \sqcap_b^{\sharp}, \{\bot_b^{\sharp}\}, (1\mathbb{Z}+0)$), dove:
- Gli elementi di $\mathcal{B}^{\sharp}$ sono della forma $a\mathbb{Z}+b$ che rappresentano le soluzioni di congruenze modulari;
- La **relazione d'ordine** tra due classi di congruenza è definita come segue: $(a\mathbb{Z} + b) \sqsubseteq_b^{\sharp} (a'\mathbb{Z}+b') \Longleftrightarrow a'|a \; \text{e} \; b\equiv b'[a']$ dove $a'$ deve **dividere** $a$ (la seconda classe è più "larga" rispetto alla prima) e il resto $b$ deve essere congruente a $b'$ modulo $a'$;
	```Esempio
	6Z+4 ⊆ 2Z+0
	- 2|6: vero;
	- 4 ≡ 0[2]: vero (poiché 4 mod 2 = 0)
	quindi possiamo dire che la prima classe è contenuta nella seconda.
	```

- **Operazione di unione (join)** trova la classe di congruenza più piccola (rispetto all'ordine) che contiene entrambe le classi: $(a\mathbb{Z} + b) \sqcup_b^{\sharp} (a'\mathbb{Z}+b') = (a \wedge a' \wedge |b - b'|)\mathbb{Z}+b$ dove il primo passo è calcolare il mcd tra le due classi ($d = mcd(a, a', |b-b'|)$) trovando quindi la classe risultante: $d\mathbb{Z}+b$.
	```Esempio
	6Z+4 ∪ 4Z+2
	
	a = 6; a' = 4;
	b = 4; b' = 2;
	
	- d = mcd(6, 4, |4-2|) = mcd(6, 4, 2) = 2
	- classe risultante 2Z+4
	```
	
- **Operazione di intersezione (meet)** trova la **classe di congruenza più grande** (rispetto all'ordine) che è contenuta in entrambe le classi: $$(a\mathbb{Z} + b) \sqcap_b^{\sharp} (a'\mathbb{Z}+b') = \begin{cases} (a \vee a')\mathbb{Z} + b'' & \text{if} \; b \equiv b' [a \vee a'] \\ \bot_b^{\sharp} & \text{altrimenti}\end{cases}$$
	dove come prima cosa dobbiamo calcolare quindi il mcm di $a$ e $a'$ (chiamato $m$), successivamente controlliamo se i resti $b$ e $b'$ sono congruenti modulo $m$:
	- Se si la classe risultante sarà del tipo $m\mathbb{Z}+b''$, dove $b''$ è un valore congruente sia a $b$ che a $b'$ modulo $m$.
	- Se no, il risultato è il simbolo $\bot_b^{\sharp}$
	```Esempio
	6Z+4 ∩ 4Z+2
	
	a = 6; a' = 4;
	b = 4; b' = 2;
	
	m = mcm(6, 4) = 12
	Controllo congruenza resti: b ≡ b'[m]
	4 ≡ 2[12] NO poichè 4 - 2 = 2 che non è divisibile per 12 in quanto non         restituisce un numero intero.
	Poiché i resti non sono congruenti, l'intersezione è BOTTOM
	```

### Connessioni di Galois
Possiamo costruire una connessione di Galois come segue:
$$
\gamma_b(X_b^{\sharp}) = \begin{cases}
\{ak + b \; | \; k \in \mathbb{Z} \} & \text{se} \; X_b^{\sharp} = (a\mathbb{Z}+b) \\
\emptyset & \text{se} \; X_b^{\sharp} = \bot_b^{\sharp}
\end{cases}
$$
$$
\alpha_b(C) = \sqcup_{c \in C}^{\sharp}(0\mathbb{Z}+c)
$$
> La funzione $\alpha_b$ mappa un insieme concreto di numeri interi $C$ a un elemento astratto $X_b^{\sharp}$​ che rappresenta tutti i numeri di $C$.
> Il simbolo $\sqcup_{c \in C}^{\sharp}$ indica il "join" (cioè l'unione nel dominio astratto), questo permette di costruire l'elemento astratto che rappresenta tutti gli interi di $C$.

Notiamo che $\gamma_b$ non è iniettivo poiché diversi elementi astratti possono rappresentare lo stesso insieme concreto, ad esempio, $2\mathbb{Z}+0$ e $2\mathbb{Z}+2$ (entrambi gli insiemi rappresentano multipli di 2, ma partendo da punti di vista diversi (offset $b$), questa non iniettività non compromette la correttezza dell'astrazione, perché il dominio astratto si basa su un **pre-ordine** e non su un ordine parziale. 

Tuttavia, $\sqsubseteq_b^{\sharp}$ corrisponde esattamente all'inclusione: $\gamma_b(X^{\sharp}) \subseteq \gamma_b(Y^{\sharp}) \Longleftrightarrow X^{\sharp} \sqsubseteq_b^{\sharp} Y^{\sharp}$. Possiamo verificare $\gamma_b(X^{\sharp}) = \gamma_b(Y^{\sharp})$ verificando $X^{\sharp} \sqsubseteq_b^{\sharp} Y^{\sharp}$ e $Y^{\sharp} \sqsubseteq_b^{\sharp} X^{\sharp}$ - tecnicamente, $\sqsubseteq_b^{\sharp}$ non è un ordine parziale ma un pre-ordine, per mancanza di anti-simmetria, ma questo non ha conseguenze pratiche nella progettazione delle nostre astrazioni. In alternativa, possiamo garantire una rappresentazione unica richiedendo che, in $a\mathbb{Z}+b$, o $a = 0$ (singleton), oppure $0 \leq b < a$ (insieme infinito di interi), in questo modo possiamo rappresentare sia il singolo elemento che insiemi infiniti garantendo che ogni insieme concreto abbia **una sola rappresentazione astratta**.

### Operazioni astratte
Come nel dominio precedente, abbiamo $\cup_b^{\sharp} = \sqcup_b^{\sharp}$ e $\cap_b^{\sharp} = \sqcap_b^{\sharp}$ e l'intersezione (meet) $\cap_b^{\sharp}$ è esatta, cioè esiste sempre un elemento astratto che rappresenta esattamente l'intersezione, mentre l'unione $\cup_b^{\sharp}$ (join) è ottimale, ma non esatta - per esempio, $\gamma_b(3\mathbb{Z}) \cup \gamma_b(3\mathbb{Z}+1)$ non può essere rappresentato esattamente ed è astratto come $\mathbb{Z}$ (perde di informazione) -> quindi, l'unione astratta è ottimale (cioè la migliore possibile), ma non sempre precisa. Ad esempio $\gamma_b(6\mathbb{Z}) \cup \gamma_b(4\mathbb{Z}) = \gamma_b(12\mathbb{Z})$ l’intersezione astratta è esatta perché possiamo rappresentarla come $12\mathbb{Z}$ nel dominio astratto.

#### Operazioni aritmetiche astratte
Le operazioni aritmetiche (+,−,×,÷) sono definite per propagare l’effetto delle operazioni sui numeri concreti all’interno del dominio astratto.
Tutte le operazioni ad eccezione della divisone sono ottimali, ma in generale non esatte. Per la divisione, gestiamo casi semplici, come divisioni per 0 ($\bot_b^{\sharp}$) o per un valore singleton ($a\mathbb{Z}+b$ con $a = 0$) che divide esattamente il primo argomento, e torniamo a una rappresentazione meno precisa $(1\mathbb{Z} + 0)$ negli altri casi.

Nota, tuttavia, la formula $\overleftarrow{\leq 0_b^{\sharp}}(X^{\sharp}) = X^{\sharp}\cap_b^{\sharp} [-\infty, 0]_b^{\sharp}$  identifica la parte negativa o nulla dell'insieme rappresentato da $X^{\sharp}$ che fornisce l'identità come $[-\infty, 0]_b^{\sharp} = 1\mathbb{Z}+0$; pertanto, vale la pena utilizzare una versione specifica del dominio di $\overleftarrow{\leq 0_b^{\sharp}}(X^{\sharp})$ che ritorna $\bot_b^{\sharp}$ quando $X^{\sharp} = 0\mathbb{Z}+c$ con $c > 0$ (nessun numero positivo).

Sebbene il dominio abbia un'altezza infinita, non esiste una catena strettamente crescente infinita.
Infatti, la componente $a$ in $a\mathbb{Z} + b$ in qualsiasi catena strettamente crescente deve decrescere strettamente ed è limitata da 1.
Possiamo quindi usare, come ampliamento (widening): $\bigtriangledown_b = \sqcup_b^{\sharp}$ . Il dominio ha tuttavia infinite catene strettamente decrescenti, come $2\mathbb{Z}, 4\mathbb{Z}, \dots, 2^n\mathbb{Z}, \dots$. Pertanto, è utile definire un operatore di restringimento $\bigtriangleup_b$ per stabilizzare sequenze decrescenti in un tempo finito. Presentiamo una semplice scelta:
$$
(a\mathbb{Z}+b) \; \bigtriangleup_b \; (a'\mathbb{Z} + b') = \begin{cases}
a'\mathbb{Z}+b' & \text{se} \; a = 1 \\
a\mathbb{Z}+b & \text{altrimenti}
\end{cases}
$$
per esempio, perfezioniamo l'argomento di sinistra solo quando è il valore più grande, $1\mathbb{Z} + 0$.
Combinando questi operatori, possiamo controllare il comportamento del dominio durante l’analisi, garantendo che rimanga gestibile anche in presenza di catene infinite.

**Esempio**
Consideriamo il programma:
```C
X <- 0; Y <- 2;
while X < 40 do
	X <- X + 2;
	if X < 5 then Y <- Y + 18 endif;
	if X > 8 then Y <- Y - 30 endif;
done
```
Notiamo che, ad eccezione di quando un valore astratto rappresenta una costante, qualsiasi test della forma $X < 40$ o $X > 8$ è astratto come l'identità (cioè non forniscono informazioni aggiuntive nel dominio astratto). La nostra analisi statica infierirà come invariante del ciclo, $X \in 2\mathbb{Z}+0$ , ad esempio $X$ è pari, e $Y \in 6\mathbb{Z}+2$, dove 6 è mcd di 18 e 30 poiché, a qualsiasi iterazione del ciclo, Y può essere incrementato di 18 o decrementato di 30.

**Spiegazione**
All'inizio del programma abbiamo: $X \in 0\mathbb{Z}+0$ e $Y \in 0\mathbb{Z} + 2$.
Il ciclo modifica le variabili $X$ e $Y$ con due tipi di operazioni:
- Aggiornamento di $X$:
	A ogni iterazione, $X$ aumenta di 2, nel dominio astratto diventa pari: $X \in 2\mathbb{Z}+0$
- Aggiornamento di $Y$:
	Condizione 1 ($X < 5$) --> Se $X < 5$ allora aggiunge un multiplo di 18 a $Y$;
	Condizione 2 ($X > 8$) --> Se $X > 8$ allora sottrae un multiplo di 30 da $Y$;
	Poiché ogni modifica incrementa o decrementa $Y$ rispettivamente di 18 o 30, il valore di $Y$ sarà un multiplo del massimo comune divisore (mcd) di 18 e 30, che è 6 (JOIN).

Invariante di ciclo --> durante l’esecuzione del ciclo, analizziamo le proprietà che rimangono **invarianti** per $X$ e $Y$:
- Per $X$:
	Ad ogni iterazione $X$ è un multiplo di 2: $X \in 2\mathbb{Z}+0$
- Per $Y$:
	Ad ogni iterazione $Y$ è congruente a 2(mod 6) poiché, inizialmente, $Y=2$ che soddisfa questa proprietà; ogni aggiornamento di $Y$ aggiunge o sottrae un multiplo di 6 (ossia 18 o 30). Quindi, $Y$ è rappresentabile come: $Y \in 6\mathbb{Z}+2$.

```Esempio
Iterazioni: 
1: X = 0; Y = 2;
2: X = 2; Y = 20;
3: X = 4; Y = 38;
4: X = 6; Y = 8;
5: X = 8; Y = -22;
6: X = 10; Y = -52;

X in 2Z+0;
Y in 6Z+2 -> Y = {..., -28, -22, -10, -4, 2, 8, 14, 20, 26, 32, 38, ...};
```
### Congruenze razionali
Il dominio di congruenza può essere esteso ai razionali, invece che agli interi, per questo dominio, $\mathbb{I} = \mathbb{Q}$, e abbiamo i seguenti valori astratti:
$$\mathcal{B^{\sharp}} = \{(a\mathbb{Z}+b) \; | \; a \in \mathbb{Q}^+, b \in \mathbb{Q}\} \cup \{\bot_b^{\sharp}, \top_b^{\sharp}\}$$
ad esempio, rappresentiamo l'insieme nella forma $\{ak+b \; | \; k\in \mathbb{Z}\}$ dove $a$ e $b$ possono essere ora razionali, invece che solo interi. Tali insiemi includono singoletti come $0\mathbb{Z} + b$. Aggiungiamo una rappresentazione $\bot_b^{\sharp}$ per $\emptyset$ e $\top_b^{\sharp}$ per $\mathbb{Q}$. Molte nozioni aritmetiche, come la relazione di divisione |, il mcd e il mcm, si estendono naturalmente ai numeri razionali. Ad esempio, $mcd(\frac{a}{b}, \frac{c}{d}) = \frac{mcd(ad, bc)}{db}$. Allo stesso modo, gli operatori aritmetici astratti sono simili al caso intero. Tuttavia, ora che il dominio ha catene infinite sia crescenti che decrescenti, abbiamo bisogno sia di un ampliamento che di un restringimento. Questo dominio ha meno applicazioni delle classiche congruenze intere, quindi non approfondiremo ulteriormente i suoi operatori e rimanderemo invece il lettore a Granger.

### Utilizzo
Quando un programma accede alla memoria durante l'esecuzione, i dati vengono salvati in posizioni chiamate **indirizzi di memoria**. Questi indirizzi possono avere **schemi regolari**: ad esempio, possono essere equidistanti o seguire una certa periodicità.
Una **congruenza** significa che tutti gli indirizzi acceduti da una determinata istruzione seguono una regola del tipo: $\text{Indirizzo} \equiv b(mod \; a)$, cioè, ogni indirizzo acceduto può essere scritto nella forma: $\text{Indirizzo} = a \cdot k+b$, (dove $k$ è un numero intero, $a$ è il modulo, cioè quanto sono distanti tra di loro e $b$ è lo shift, cioè dove inizia la sequenza di indirizzi).

Ad esempio, un indirizzo con un valore di $32k + 4$ accede sempre al quarto byte in una riga di cache da 32 byte, gli indirizzi di memoria dinamici sono considerati **congruenti** se tutti questi indirizzi soddisfano la relazione descritta precedentemente.