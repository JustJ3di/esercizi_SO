I/O pova d'esame

Si  realizzi  in  linguaggio  C/C++  un’applicazione multithreadutilizzando  il  costrutto Monitor,  che simuli la gestione di un vettore di buffer di I/O. 
Per gestire l’accesso al vettore, si utilizzi la soluzione del produttore/consumatore con vettore circolare.
   
   typedef struct {
        int indirizzo;
        int dato;} 
   Buffer;
    
    typedef struct {
          Buffervettore[10];
          
          // ... inserire qui variabili aggiuntive per la sincronizzazione ...
          
    } GestioneIO;
     
     void Inizializza(Gestione IO * g);   
     void Produci(GestioneIO* g, Buffer * b);
     intConsuma(GestioneIO* g, Buffer * b);
 
 
Il metodo Inizializzaimposta il valore iniziale delle variabili interne del monitor. 
Il metodo Produciha un parametro di ingresso di tipo puntatore a Buffer, per il passaggio di un buffer da copiare nel vettore. 
Il metodo Producidevesospendere il thread chiamante senon vi èspazio disponibile.
Il  metodo Consumaprelevadal  vettore il  contenuto  di  un  buffer,  che  deve  essere datoal  chiamante attraverso  il  puntatore  a Bufferpassato  come  parametro  di  ingresso.  Nel  caso  non  vi  siano  buffer disponibili,  il  metodo Consumanondeve  sospendere  il  thread  chiamante,bensì  deve indicareal chiamante l'assenza di buffer pieni, ritornando il valore 1 attraverso il parametro di uscita intero della funzione. Nel caso invece che vi sia un buffer disponibile da consumare, la funzione dovrà ritornare 0.
Il  programma  principale  dovrà  creare 4threadProduttori  e  2  thread  Consumatori.  I  thread Produttorieffettuano ciascuno 3 produzioni, attendendo 1 secondo tra una produzione e la successiva (usando la primitiva sleep). I produttori dovranno scegliere a caso (tra 0 e 10) i valori di indirizzoe datoda usare alla prima produzione, e incrementarli di 1 ad ogni produzione. Ad esempio, il produttore può scegliere la coppia (3,7) alla prima produzione, e usarele coppie (4,8) e (5,9) alle produzioni successive.
Ogni  thread  Consumatore  dovrà  effettuare  4  iterazioni. 
Ad  ogni  iterazione,  il  Consumatore  effettua consumazioni  ripetute(chiamando  più  volte  il  metodo Consuma,e  stampando  a  video  i  valori prelevati), fino a quando il vettore di buffer diventa vuoto(il valore di ritorno di Consumaèparia 1).

Il thread Consumatore deve attendere 3 secondi (tramite sleep) tra due iterazioni
