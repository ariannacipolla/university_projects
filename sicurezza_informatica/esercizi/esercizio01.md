# Analisi File e Software 
Ho caricato il seguente file: "RK_Keyboard_Software_Setup_V4.5%2020240718.exe" si tratta dell'eseguibile per windows di un software per settare la tastiera.
Il file è stato scaricato dal sito originale della azienda che le produce: "[Keyboards Link](https://rkgamingstore.com/pages/software?srsltid=AfmBOooKxIORdTX8ug3uK3acQmjciNi8oOG3YXKDrw_s4hzsncs0SmWR)"
## VirusTotal
 ![[Screenshot 2024-09-29 alle 22.07.29.png]] 
Vediamo dunque come ci sia una presenza di malware all'interno dell'eseguibile, vedendo nello specifico :

![[Screenshot 2024-09-29 alle 22.15.24.png]]

Documentandomi "Bkav Pro" sarebbe il software antivirus che ha trovato una traccia di malware, precisamente "W32" suggerisce che si tratta di un malware per il sistema operativo Windows, mentre la dicitura "AIDetectMalware" implica che è stato rilevato tramite una tecnologia di intelligenza artificiale o comunque un algoritmo di rilevamento avanzato.
Esaminando la tipologia di malware in rete spesso parlano di un falso positivo. allora per esserne certi ho analizzato l'eseguibile con un ulteriore analizzatore.

## Hybrid Analysis

![[Screenshot 2024-09-29 alle 22.28.31.png]]

Anche in questo caso abbiamo che lo stesso file precedente riporta un malware, andiamo quindi a vedere nello specifico di cosa si tratta.

![[Screenshot 2024-09-29 alle 22.30.32.png]]

Vediamo che il file "InitSetup.dll" riporta al suo interno una minaccia, andando ad analizzare quel file in effetti l'antivirus "MetaDefender" riporta un messaggio di file infetto.

![[Screenshot 2024-09-29 alle 22.33.09.png]]

Di seguito riportata la tipologia di malware.
  ![[Screenshot 2024-09-29 alle 22.33.44.png]]

> Per quanto riguarda il sito "Anyrun", il file era troppo pesante e non sono riuscita ad analizzarlo, richiede un massimo di 16 MB:

![[Screenshot 2024-09-29 alle 22.41.18.png|400]]


-------

Proviamo ora a testare un altro tipo di file, così da poter sfruttare anche l'ultimo sito.

Tramite una macchina virtuale con installato il sistema operativo Windows, ho deciso di provare ad analizzare un malware di tipo ransomware chiamato, appunto, ransomware.exe scaricato da una repository di [github](https://github.com/Da2dalus/The-MALWARE-Repo).

## VirusTotal
![[Screenshot 2024-10-01 alle 18.29.24.png]]![[Screenshot 2024-10-01 alle 18.29.58.png]]

Possiamo vedere dagli screen che il sito VirusTotal rileva molte minacce, che vengono categorizzate in minacce di tipo ransomware e trojan.
## Hybrid Analysis 

![[Screenshot 2024-10-01 alle 18.31.07.png]]

![[Screenshot 2024-10-01 alle 18.32.58.png]]

Ovviamente anche Hybrid Analysis rileva molteplici malware di diverso tipo.
## AnyRUN
Passiamo infine al sito web di analisi che ancora non avevamo affrontato e possiamo vedere come, anch'esso, rileva malware.

![[Screenshot 2024-10-01 alle 18.35.03.png]]

Vediamo negli screen seguenti, l'apparizione di un pop-up poco raccomandabile, trattandosi a tutti gli effetti di un virus.

![[Screenshot 2024-10-01 alle 18.36.03.png]]

Il programma ci suggerisce che potrebbe essere un virus che potrebbe rubare i nostri dati personali.

![[Screenshot 2024-10-01 alle 18.36.40.png]]