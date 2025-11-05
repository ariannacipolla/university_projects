# Notazione

Uno **spazio di Hilbert** $\mathcal{H}$ è uno spazio vettoriale lineare su $\mathbb{C}$ dotato di **prodotto interno** e che induce una **norma**. Usiamo la **notazione di Dirac** per rappresentare i vettori di tale spazio.

- $\ket{v} \in \mathcal{H}$, detto _ket_;
- $\bra{v} \in \mathcal{H}$, detto _bra_; Generalmente un ket rappresenta lo 
    stato quantistico di uno spazio vettoriale di Hilbert ed è associato ad un
    vettore colonna:    $$
    \ket{v} = \begin{bmatrix}
     v_1 \\
     \vdots \\
     v_n
    \end{bmatrix}
    $$
    Un bra invece rappresenta il _dagato_ (trasposto coniugato) di un ket:    $$
    \bra{v} = \ket{v}^\dagger = \begin{bmatrix}
     v_1^* & \ldots & v_n^*
    \end{bmatrix}
    $$

## Prodotto interno

Definiamo il **prodotto interno** come l'applicazione di un bra ad un ket (_bra-ket_):

$$
\braket{x|y} := \begin{bmatrix}
 x_1^* & \ldots & x_n^*
\end{bmatrix} \cdot \begin{bmatrix}
 y_1 \\
 \vdots \\
 y_n
\end{bmatrix} =
\sum_{i}{x_i^* \cdot y_i}
$$

### Proprietà

Al prodotto interno si associano le seguenti proprietà:
1. linearità:     $$
	    \braket{x|\alpha\ket{y} + \beta\ket{z}} = \alpha\braket{x|y} + \beta\braket{x|z}
	    $$
1. $\braket{x|y} = \braket{y|x}^*$
    > $\braket{y|x}^* = (\sum_{i} y_i^* x_i)^* = \sum_{i} y_i x_i^* =: \braket{x|y}$
3. $\braket{x|x} \geq 0$
4. $\braket{x|x}=0 \Leftrightarrow \ket{x}=0$ Da queste definiamo la **norma**
   come $$
    ||{x}|| := \sqrt{\braket{x|x}}
    $$