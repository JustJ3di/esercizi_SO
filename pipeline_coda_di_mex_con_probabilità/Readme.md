
Pipeline di code, con probabilità di modifiche

Si realizzi un'applicazione multiprocesso di tipo Client-Server, utilizzando code di messaggi UNIX. In aggiunta a 3 processi Client e al processo Server (vedi figura),
il programma dovrà avere un terzo tipo di processo Iniettore, che corromperà i messaggi in transito tra Client e Server.

I messaggi dovranno contenere una coppia di campi (oltre al campo "tipo"): un vettore di caratteri, e un valore intero. 
Ciascun Client dovrà inserire nel vettore di caratteri[1] rispettivamente le stringhe "CLIENT1", "CLIENT2", "CLIENT3" (ripetendo la stessa stringa su tutti i messaggi inviati dallo stesso Client); e dovrà inserire nel campo intero la lunghezza della stringa (in questo caso, il valore "7" poiché vi sono 7 caratteri). Si inviino 3 messaggi per ogni Client.

Il processo Iniettore dovrà consumare i messaggi da una prima coda di messaggi.
L'Iniettore dovrà decidere, in maniera casuale[2], se inoltrare il messaggio nella seconda coda di messaggi in maniera intatta (70% di probabilità) oppure corrotta. 
Nel caso si debba corrompere il messaggio, il processo dovrà aggiungere un valore casuale al campo intero (10% di probabilità) oppure inserire il carattere '\0' in una posizione a piacere della stringa (20% probabilità).

Il processo Server dovrà verificare l'integrità del messaggio, controllando che la lunghezza della stringa[3] coincida con il valore intero incluso nel messaggio. In caso affermativo, il processo Server dovrà stampare il messaggio su terminale. In caso negativo, dovrà stampare un messaggio di errore.
