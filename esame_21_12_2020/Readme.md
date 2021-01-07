Testo della prova
Si realizzi in linguaggio C/C++ un’applicazione multithread basata sul costrutto Monitor, per
simulare lo streaming video mediante lo schema produttore-consumatore. Utilizzare un vettore
circolare di buffer condiviso. Ogni buffer è atto a contenere un frame video (una matrice di interi 2x2).
In aggiunta ai metodi tradizionali per la consumazione e la produzione di un singolo elemento, il
monitor dovrà fornire un ulteriore metodo void bufferizza(MonitorStreaming *m, int
N), che può essere chiamato dal thread consumatore. Il metodo sospende il thread chiamante se il
numero di frame video nel vettore è inferiore a N.
Il thread sospeso verrà riattivato quando sarà prodotto un frame e saranno stati accumulati in totale N
frame video. Dopo l'attesa, il metodo bufferizza si limita a uscire dal monitor. Il thread chiamante può
poi consumare i frame chiamando più volte il metodo per la consumazione.
Si simulino un thread produttore e un thread consumatore, con un vettore di 6 buffer. Il produttore
effettuerà in totale 10 produzioni in un ciclo, attendendo 1 secondo tra le iterazioni, e inserendo nei
frame valori casuali tra 0 e 10. Il consumatore chiamerà inizialmente il metodo di bufferizzazione, per
attendere che si accumulino 4 frame. Dopo l'attesa, il consumatore effettuerà 10 consumazioni in un
ciclo, attendendo 1 secondo tra le iterazioni.
File da completare:
