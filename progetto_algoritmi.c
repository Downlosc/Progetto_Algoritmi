#include <stdio.h>
#include <stdlib.h>

typedef struct domanda {
    char domanda;
    struct domanda *pross;
    } domanda_t;

typedef struct studente {
    int id;
    struct domanda *domande;
    int risultato;
    } studente_t;

void inserisci_in_lista(domanda_t **, 
                        char);
void stampa_report(studente_t *, 
                   char *, 
                   int, 
                   int);
void quicksort(studente_t *,
               int,
               int,
               int *);
               
void quicksort_per_risultati(studente_t *,
             int,
             int,
             int *);

               
int main(void)
{
    /*Dichiarazione variabili locali*/
    int studenti, 
        domande,
        i,
        j,
        totale,
        si_no,
        passi = 0;

    double media;

    char nuova_domanda,
         *risposte;
    
    FILE *dati;
    
    studente_t *esami;
    
    domanda_t *corrente; 
    
    /*Apertura file di dati*/
    dati = fopen("datiesame.txt", 
                 "r");
    
    /*Acquisizione del numero di studenti*/
    fscanf(dati, 
           "%d", 
           &studenti);
    
    /*Allocazione di un array di studenti*/
    esami = (studente_t *)calloc(studenti, 
                                  sizeof(studente_t));
    
    /*Acquisizione del numero di domande*/
    fscanf(dati, 
           "%d\n", 
           &domande);
    
    /*Allocazione di un array di risposte corrette*/
    risposte = (char *)calloc(domande, 
                              sizeof(char));
    
    /*Memorizzazione delle risposte corrette*/
    for(i=0; 
        (i<domande); 
        i++)
        fscanf(dati,
               "%c",
               &risposte[i]);
    /*Memorizzazione degli esami*/
    for(i=0; 
        (i<studenti); 
        i++)
    {
        /*Acquisizione dell'id dello studente*/
        fscanf(dati, 
               "%d ", 
               &esami[i].id);
        /*Inizializzazione degli altri parametri*/
        esami[i].risultato = 0;
        esami[i].domande = NULL;

        /*Acquisizione delle risposte*/
        for(j=0; 
            (j<domande); 
            j++)
        {
            fscanf(dati,
                   "%c",
                   &nuova_domanda);
            
            inserisci_in_lista(&(esami[i].domande), 
                               nuova_domanda); 
        }
    }
    
    for(corrente = esami[0].domande; corrente != NULL; corrente = corrente->pross)    
        printf("%c", corrente->domanda);
        
    /*Stampa del report*/
    stampa_report(esami, 
                  risposte, 
                  studenti, 
                  domande);
    
    /*Report ordinato*/
    printf("\n\nDesideri il report ordinato in base all'id dello studente?");
    printf("\n0. NO, \n1. SI'\n");
    scanf("%d", 
          &si_no);
    if(si_no != 0)
    {
        quicksort(esami, 
                  0, 
                  studenti-1,
                  &passi);
                  
        stampa_report(esami, 
                      risposte, 
                      studenti, 
                      domande);
    }
    
    
    /*Media e mediana*/
    printf("\n\nDesideri il calcolo di media e mediana dei voti?");
    printf("\n0. NO, \n1. SI'\n");
    scanf("%d", 
          &si_no);
    if(si_no != 0)
    {
        for(totale=0, i=0;
            (i<studenti);
            i++)
        {
            totale+=esami[i].risultato;
            passi++;
        }
        
        totale = totale*100/domande;
        media = (double)totale/studenti;
        printf("\nMedia = %.1f", 
               media);
        
        quicksort_per_risultati(esami, 
                                0, 
                                studenti-1, 
                                &passi); 
                  
        printf("\nMediana = %.1f",
               (double)esami[(studenti+1)/2].risultato*100/domande);
    }
    
    printf("\nComplessita': %d", 
            passi);
    
    printf("\n\nProgramma terminato\n\n");
    
    return(0);
}    


void inserisci_in_lista(domanda_t **testa, 
                        char risposta)
{
    domanda_t   *corrente,
                *precedente,
                *nuovo;
    
    for(precedente=corrente=*testa;
        (corrente!=NULL);
        precedente=corrente, corrente=corrente->pross);

    nuovo = (domanda_t *)malloc(sizeof(domanda_t));
    nuovo->domanda = risposta;
    nuovo->pross = NULL;
    
    if(corrente == *testa)
        *testa = nuovo;
    else
        precedente->pross = nuovo;
}  

  
void stampa_report(studente_t *esami, 
                   char *risposte, 
                   int studenti, 
                   int domande)
{    
    int i, 
        j,
        *errori;
        
    domanda_t *corrente;

    errori = (int *)calloc(domande, 
                           sizeof(int));
        
    printf("\nReport d'esame\n");
    
    printf("Domanda: ");
    for(j=0; 
        j<domande; 
        j++)
        printf("\t%d ", 
               j);
    printf("\n");
    
    printf("Risposta: ");
    for(j=0; 
        j<domande; 
        j++)
        printf("\t%c", 
               risposte[j]);

    printf("\n\nID \t Percentuale(%%)");
    
    for(i=0;
        (i<studenti);
        i++)
    {
        printf("\n%d \t ",
               esami[i].id);
               
        for(j=0, esami[i].risultato=0, corrente=esami[i].domande;
            (j<domande);
            j++, corrente=corrente->pross)
            if(corrente->domanda == risposte[j])
                esami[i].risultato++;
            else
                errori[j]++;
                 
        printf("%.1f%%",
               (double)esami[i].risultato * 100 / domande);
    }

    /*Stampa degli errori*/
    printf("\n\nDomanda: ");
    for(i=0; 
        i<domande; 
        i++)
        printf("\t%d", 
               i);
    printf("\nSbagliata da: ");
    for(i=0; 
        i<domande; 
        i++)
        printf("\t%d", 
               errori[i]);
}  


void quicksort(studente_t a[],
               int sx,
               int dx,
               int *passi)
{
    int pivot,
        i,
        j;
    
    studente_t tmp;
    
    for (pivot = a[(sx + dx) / 2].id, i = sx, j = dx;
         (i <= j);
        )
    {
        while (a[i].id < pivot)
        {
            i++;
            (*passi)++;
        }
        
        while (a[j].id > pivot)
        {
            j--;
            (*passi)++;
        }
        
        if (i <= j)
        {
            if (i < j)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
            
            i++;
            j--;
        }
    }
    
    if (sx < j)
        quicksort(a,
                  sx,
                  j,
                  passi);
    
    if (i < dx)
        quicksort(a,
                  i,
                  dx,
                  passi);
}


void quicksort_per_risultati(studente_t a[],
                             int sx,
                             int dx,
                             int *passi)
{
    int pivot,
        i,
        j;
    
    studente_t tmp;
    
    for (pivot = a[(sx + dx) / 2].risultato, i = sx, j = dx;
         (i <= j);
        )
    {
        while (a[i].risultato < pivot)
        {
            i++;
            (*passi)++;
        }
        
        while (a[j].risultato > pivot)
        {
            j--;
            (*passi)++;
        }
        
        if (i <= j)
        {
            if (i < j)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
            
            i++;
            j--;
        }
    }
    
    if (sx < j)
        quicksort(a,
                  sx,
                  j,
                  passi);
    
    if (i < dx)
        quicksort(a,
                  i,
                  dx,
                  passi);
}
