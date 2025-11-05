# Trama
Questo studio dimostra che GPT-3 può essere utilizzato per prevedere la demenza a partire dal discorso spontaneo. Gli embedding testuali (rappresentazione numerica del significato di un testo, GPT-3 è in grado di trasformare il testo in vettori che descrivono cosa viene detto, come, e con quale tono) generati dal modello permettono di distinguere i soggetti con Alzheimer dai sani e stimare il punteggio cognitivo, superando le prestazioni delle caratteristiche acustiche tradizionali. Questo approccio mostra grande potenziale per la diagnosi precoce della demenza.

# Introduzione
Il morbo di Alzheimer (AD) è una malattia neurodegenerativa che comporta un progressivo declino delle funzioni cognitive, inclusi disturbi del linguaggio e della parola, è la causa più comune di demenza.

Attualmente, la diagnosi dell’AD si basa principalmente su valutazioni cliniche come neuroimmagini o test cognitivi, ad esempio il Mini-Mental State Examination (MMSE), utilizzato per valutare la progressione della malattia. Tuttavia, questi metodi sono spesso costosi e richiedono valutazioni mediche lunghe. 

Le analisi precedenti del parlato si basano principalmente su un approccio a caratteristiche, utilizzando parametri acustici estratti dall’audio e caratteristiche linguistiche ricavate da testi scritti o trascrizioni vocali tramite tecniche NLP.

>**NLP** (**Natural Language Processing**), ovvero **Elaborazione del Linguaggio Naturale**.
>È una **disciplina dell’intelligenza artificiale** che permette ai computer di **capire, interpretare, generare e analizzare il linguaggio umano**, proprio come lo usiamo ogni giorno — in forma scritta o parlata.

Di conseguenza, è difficile da generalizzare ad altri stadi della malattia o a tipologie differenti, che possono comportare variazioni linguistiche diverse. L’analisi del linguaggio abilitata dall’intelligenza artificiale è emersa come un approccio promettente per lo screening precoce dell’Alzheimer.

I grandi modelli linguistici (LLM), che hanno mostrato prestazioni impressionanti in molti compiti di NLP, offrono una comprensione e generazione del linguaggio altamente efficiente.  
GPT-3 (Generative Pre-trained Transformer 3), uno dei più grandi modelli linguistici sviluppati da OpenAI, si è rivelato particolarmente efficace in due ambiti:
1. l’apprendimento zero-shot, la capacità di un modello di svolgere un compito anche se non è stato addestrato direttamente su quel compito specifico.
2. la codifica di una vasta conoscenza semantica del mondo e la produzione di rappresentazioni apprese, cioè GPT-3 riesce a "capire" il significato delle frasi e dei concetti e può trasformare un testo in un insieme di numeri (chiamati embedding) che rappresentano il senso profondo di quel testo.

Gli embedding testuali forniscono rappresentazioni vettoriali significative che possono rivelare pattern e caratteristiche implicite nel significato semantico dell’input, talvolta non evidenti nemmeno per esperti umani.
 Utilizziamo i dati della sfida ADReSSo (Alzheimer’s Dementia Recognition through Spontaneous Speech only), un compito condiviso per il confronto sistematico di approcci alla rilevazione del deterioramento cognitivo basato solo su discorso spontaneo.  
 Con questo dataset, eseguiamo due compiti:  
- un compito di classificazione dell’AD per distinguere soggetti affetti da Alzheimer da controlli sani,  
- un compito di regressione del punteggio MMSE per stimare il risultato di un test cognitivo, entrambi basati esclusivamente su dati vocali demograficamente bilanciati.
## Obiettivo
Mostriamo che l'embedding testuale può essere utilizzato in modo affidabile per rilevare la demenza di Alzheimer e per inferire il punteggio del test cognitivo. Inoltre, dimostriamo che l’embedding testuale supera nettamente l’approccio convenzionale basato su caratteristiche acustiche e si comporta in modo competitivo anche rispetto ai modelli fine-tuned. 

# Risultati
Lo studio presenta due compiti principali:
1. **Classificazione AD vs non-AD**, usando caratteristiche acustiche, embedding di GPT-3 (Ada e Babbage), o entrambi, applicati a modelli di machine learning (SVC, LR, RF), con un confronto anche tramite fine-tuning di GPT-3.
2. **Previsione della gravità dell’AD**, stimando il punteggio MMSE tramite regressione basata su caratteristiche acustiche e embedding GPT-3, usando modelli SVR, Ridge e RFR.

