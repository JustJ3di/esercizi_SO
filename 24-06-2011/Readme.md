Si  realizzi  in  linguaggio  C/C++  un’applicazione multiprocessoper  la  simulazione  di un  algoritmo  di schedulazione  dei  dischi.  
L’applicazione deve  esserecostituita  da un  processo Schedulatoree  da  un gruppo  di  5 processi Utente. 
Ogni processo Utente  genera 5 richieste  di  scrittura  verso  il  disco,  che devono essere collocate in una coda circolare di 10 elementi allocata in una memoria condivisa, per poi terminare la sua esecuzione.Se la coda è piena, il processo Utente deve mettersi in attesa che vi sia una  posizione  disponibile. Una  richiesta  deve  contenere  un  valore  da  scrivere  sul  disco  (si  utilizzi  il PID del processo) e la posizione in cui scrivere il valore (un valore intero casuale tra 0 e 19):
      typedef struct {
          unsigned int posizione;
          pid_tprocesso;
      }richiesta;
Il processo  Schedulatore  preleva  le  richieste  dalla  testa  della  coda  circolare  (ossia  applicando  una politica  FIFO).
Per  simulare  la  scrittura  su  disco,  lo  Schedulatore  attende per un intervallo  di tempo (tramite  la  primitiva sleep()) di  duratati=|  pi-pi-1|secondi,dove pirappresenta  la  posizione sul disco della i-esima scrittura, assumendo p0=0. Dopo aver atteso tisecondi, lo Schedulatore sovrascrive il valore della richiesta alla posizione pidi un arrayrappresentanteil disco(daallocare come variabile automatica).
Lo Schedulatore termina dopo aver servito 25 richieste provenienti dai processi Utente.
L’accesso  da  parte  dei  processi alla  coda  circolare  e  ai  relativi  puntatori  "testa"  e  "coda" deve  essere disciplinato attraverso il costrutto Monitordi Hoare.I  processi Utentee Schedulatoresono  generati  daun  unicoprogramma  principale  attraverso  la primitiva fork(). 
Una volta generati i processi, il programma principale ne attende la terminazione e termina a sua volta
