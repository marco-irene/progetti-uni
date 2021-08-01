#include <stdio.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include "header.h"



void handler(int signal);
void send_msg(int to,int t);
void voto_Max();
void aggiorno_membri();
void send_msg(int to,int t);
void gruppo_chiuso();
int search();
int search_all();

int indice,last=0,last_st=0;

struct shared_data * pMem;

int ricevente,inviti=0,membri =1;

struct message my_msg,v_msg;

int shm_id,shm_id2,sem_id,msg_id,vote_msg;

student_t dati_studente;

int pop_size;

struct sembuf sops;

int main(int argc, char *argv[]){

  int result;

  int allarme=0;


  srand(getpid());

  indice = atoi(argv[0]);

  pop_size=atoi(argv[1]);

  shm_id=shmget(KEY_MEM, 0, 0); //mem condivisa per struttura condivisa
  pMem = shmat(shm_id, NULL, 0);

  sem_id = semget(KEY_SEM,0,0);

  msg_id = msgget (KEY_MSG, 0);

  vote_msg = msgget (KEY_VOTE, 0);



  int temp =rand()%(0-99+1)+0;
  int preferenza;
  if(temp<pMem->group_2)
    preferenza = 2;
  else if(temp>=pMem->group_2 && temp<pMem->group_3+pMem->group_2)
    preferenza = 3;
  else
    preferenza = 4;


  dati_studente.matricola=getpid();
  dati_studente.nof_elems = preferenza;
  dati_studente.nof_invites=pMem->nof_invites;
  dati_studente.max_reject=pMem->max_reject;
  dati_studente.gruppo=(int*) malloc(membri*sizeof(int));

  result=initMystruct(&dati_studente); //inizializzo struttura
    if(result != 0){
      fprintf(stderr, "Error with the struct\n");
    }

  pMem->stud_vec[indice]=dati_studente;
  StampaStruct(&dati_studente,indice);


  if (reserveSem(sem_id, ID_SINCRO) == -1 )
    TEST_ERROR;


  if (waitZero(sem_id, ID_SINCRO) == -1 )
    TEST_ERROR;

  if (releaseSem(sem_id, ID_PADRE) == -1 )
    TEST_ERROR;


    while((allarme=semctl(sem_id, ID_ALARM, GETVAL, NULL)) == 1){

      while(msgrcv(msg_id, &my_msg ,sizeof(my_msg) - sizeof(long),getpid(), IPC_NOWAIT)!=-1){ // controllo se ho messaggi

        if(my_msg.mtext==RICHIESTA){ // se è una richesta di uno studente

         if(pMem->stud_vec[indice].leader!=1 && pMem->stud_vec[indice].accetto!=1 && pMem->stud_vec[my_msg.from].membri != pMem->stud_vec[my_msg.from].nof_elems ){ // se non sono leader , non ho un gruppo e il gruppo del leader non è pieno valuto se accettare

           if( pMem->stud_vec[indice].max_reject>0){ // se ho ancora rifiuti..

             if( pMem->stud_vec[my_msg.from].voto_AdE>=24){ // e il voto di chi mi ha mandato la richiesta è >= 24 accetto

              pMem->stud_vec[indice].accetto=ACCETTO;
              pMem->stud_vec[my_msg.from].leader=1;
              pMem->stud_vec[my_msg.from].membri++;

              send_msg(pMem->stud_vec[my_msg.from].matricola,ACCETTO);

             }else{  //altrimenti rifiuto
              send_msg(pMem->stud_vec[my_msg.from].matricola,RIFIUTO);
              pMem->stud_vec[indice].max_reject--;
             }

          }else{ //se non posso più rifiutare accetto invito da qualunque studente

            pMem->stud_vec[indice].accetto=ACCETTO;
            pMem->stud_vec[my_msg.from].leader=1;
            pMem->stud_vec[my_msg.from].membri++;

            send_msg(pMem->stud_vec[my_msg.from].matricola,ACCETTO);
          }


        }else{ // se sono leader oppure ho già un gruppo rifiuto
           send_msg(pMem->stud_vec[my_msg.from].matricola,RIFIUTO);
         }

      }else if(my_msg.mtext==ACCETTO){ // risposta di accettazione da parte di uno studente , mi impegno a formare un gruppo
        membri++;
        dati_studente.gruppo=(int*) realloc(dati_studente.gruppo,membri);
        pMem->stud_vec[indice].membri=membri;
        pMem->stud_vec[indice].group_id=indice;
        pMem->stud_vec[my_msg.from].group_id=indice;
        pMem->stud_vec[indice].gruppo[0]=indice;
        pMem->stud_vec[indice].gruppo[membri-1]=my_msg.from;

        aggiorno_membri(); //aggiorno numero di membri agli altri membri del gruppo

        //printf("[%d]FORMO GRUPPO CON: %d %d\n",dati_studente.matricola,pMem->stud_vec[my_msg.from].matricola,membri);

        voto_Max(); // voto max di ADE
        gruppo_chiuso(); // se membri riaggiungo nof elems chiudo gruppo
     }
    }

    if(pMem->stud_vec[indice].chiuso!=1  && pMem->stud_vec[indice].accetto!=1  && inviti<pMem->stud_vec[indice].nof_elems &&  membri < pMem->stud_vec[indice].nof_elems ) { //cerco chi invitare

      if(pMem->stud_vec[indice].nof_invites>1 ){

        if((ricevente=search()) == pop_size) {
          continue;
        }

        inviti++;
        pMem->stud_vec[indice].nof_invites--;
        send_msg(pMem->stud_vec[ricevente].matricola,RICHIESTA);

      }else if(pMem->stud_vec[indice].nof_invites==1){

        if((ricevente=search_all()) == pop_size) {
          continue;
        }

        inviti++;
        pMem->stud_vec[indice].nof_invites--;
        send_msg(pMem->stud_vec[ricevente].matricola,RICHIESTA);
      }
    }
  }

  if(msgrcv(vote_msg, &v_msg ,sizeof(v_msg) - sizeof(long),pMem->stud_vec[indice].matricola,0)!=-1){

    signal(SIGINT,handler);
    kill(getpid(),SIGINT);

  }
}


//FUNZIONI
int search(){

  for(int i = last_st; i<pop_size; i++){
    if(indice!=i && pMem->stud_vec[indice].turno == pMem->stud_vec[i].turno && pMem->stud_vec[i].accetto!=1 && pMem->stud_vec[i].leader!=1 && pMem->stud_vec[i].nof_elems==pMem->stud_vec[indice].nof_elems && last!=i){
      last_st=i;
      last=i;
      return i;
    }
  }
}

int search_all(){

  for(int i = last_st; i<pop_size; i++){
    if(indice!=i && pMem->stud_vec[indice].turno == pMem->stud_vec[i].turno && pMem->stud_vec[i].accetto!=1 && pMem->stud_vec[i].leader!=1 && last!=i){
      last_st=i;
      last=i;
      return i;
    }
  }
}

void send_msg(int to,int t){ /* invia un messaggio*/

  my_msg.mtype = to;
  my_msg.mtext = t;
  my_msg.from = indice;

  if(msgsnd(msg_id, &my_msg, sizeof(my_msg) - sizeof(long),0) == -1){

    TEST_ERROR;
    exit(EXIT_FAILURE);
  }
}

void gruppo_chiuso(){

  for (int i=0; i<pop_size; i++){
    if(pMem->stud_vec[i].membri==1) pMem->stud_vec[i].group_id=-1;
    if(pMem->stud_vec[i].membri==pMem->stud_vec[i].nof_elems)
      pMem->stud_vec[i].chiuso=1;
    else
      pMem->stud_vec[i].chiuso=0;

  }
}

void voto_Max(){

    if(pMem->stud_vec[indice].voto_max>=pMem->stud_vec[my_msg.from].voto_max ){
      pMem->stud_vec[my_msg.from].voto_max=pMem->stud_vec[indice].voto_max;
    }else{
      pMem->stud_vec[indice].voto_max=pMem->stud_vec[my_msg.from].voto_max;
    }

  for(int j=1; j<pMem->stud_vec[indice].membri;j++){
   pMem->stud_vec[pMem->stud_vec[indice].gruppo[j]].voto_max=pMem->stud_vec[indice].voto_max;
  }
}

void aggiorno_membri(){
  for(int j=1; j<membri; j++){
   pMem->stud_vec[pMem->stud_vec[indice].gruppo[j]].membri=membri;
  }
}



void handler(int signal) {

  printf("STUDENTE: %d ---- TURNO: %d ---- VOTO ARCH: %d ---- ID GRUPPO:  %d  ---- MEMBRI:  %d ---- VOTO SO:  %d  \
            STATO GRUPPO:  %d  %s\n",pMem->stud_vec[indice].matricola,pMem->stud_vec[indice].turno, pMem->stud_vec[indice].voto_AdE,pMem->stud_vec[indice].group_id,pMem->stud_vec[indice].membri,pMem->stud_vec[indice].voto_SO,pMem->stud_vec[indice].chiuso,pMem->stud_vec[indice].chiuso !=0 ? "chiuso" : "aperto");

  if (releaseSem(sem_id, SEM_VOTO) == -1 )
    TEST_ERROR;

  exit(EXIT_SUCCESS);
}
