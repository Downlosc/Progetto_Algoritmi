# Progetto_Algoritmi

Scrivere un programma ANSI C che esegue le seguenti elaborazioni:
1. Acquisisce da file le informazioni relative alla prova. Il formato del file `e del tipo:
<Numero totale degli studenti> <Numero delle domande della prova> <Stringa risposte corrette>
<ID1> <stringaID1>
<ID2> <stringaID2>
...
<IDNs> <stringaIDNs>
Ad esempio:
3
5
dbbac
121 babac 107 baadc 104 baaac
2. Produce in output a monitor un report d’esame contenente la stringa delle risposte corrette, gli ID dei vari studenti seguiti dai punteggi percentuali ottenuti e, infine, le informazioni su
quanti studenti hanno sbagliato un dato quesito.
Ad esempio:
Report d’esame Domanda 1 2 3 4 5 Risposta b a a d c ID Punteggio (%) 121 60
107 100 104 80
Domanda 1 2 3 4 5 Sbagliata da 0 0 1 2 0
3. Produce, su richiesta, una versione del report ordinata in base all’identificativo studente oppure calcola la media e la mediana dei voti ottenuti.
Per quanto riguarda l’analisi teorica si devono studiare le complessità degli algoritmi di calcolo
e output del report, di calcolo del report ordinato e di calcolo di media e mediana.
Si deve anche verificare sperimentalmente la complessità dell’ordinamento e del calcolo di media e mediana, generando casualmente una sequenza di ID studente e stringhe di risposte (la cui lunghezza si può ipotizzare costante al variare di Ns) da fornire come input all’algoritmo per valori
crescenti di Ns.
