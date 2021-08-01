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
#define COMMAND "gcc -o studente studente.c funzioni.c"



void handler(int signal);
void voto_SO();
void media_SO();
void media_Arch();

struct message my_msg,v_msg;

int pop_size,voto_so;

int shm_id,sem_id,msg_id,vote_msg;

pid_t *kid_pids;

struct shared_data * pMem;

struct sembuf sops;

int main(int argc, char const *argv[]){

  int i = 0,status;

  pid_t child_pid;

  student_t dati_studente;

  char * my_argv[3];


  if (argc > 1) {
      if (!(pop_size = atoi(argv[1]))) {
        pop_size = POP_SIZE;
      }
    } else {
      pop_size = POP_SIZE;
    }
    status=system(COMMAND);

    char num[pop_size];
    char pop[pop_size];


    shm_id=shmget(KEY_MEM, sizeof(struct shared_data), IPC_CREAT | IPC_EXCL | 0600); //mem condivisa per struttura condivisa
    TEST_ERROR;

    pMem = shmat(shm_id, NULL, 0);
    TEST_ERROR;

    get_info(&pMem->nof_invites,&pMem->max_reject, &pMem->group_2, &pMem->group_3, &pMem->group_4);

    msg_id = msgget (KEY_MSG, IPC_CREAT | 0600);
  	TEST_ERROR;

    vote_msg  = msgget (KEY_VOTE, IPC_CREAT | 0600);
    TEST_ERROR;

    sem_id=semget(KEY_SEM,4,IPC_CREAT | 0600);
    TEST_ERROR;
    semctl(sem_id ,ID_SINCRO , SETVAL,pop_size);
    semctl(sem_id,ID_PADRE , SETVAL, 0);
    semctl(sem_id, ID_ALARM, SETVAL, 1);
    semctl(sem_id, SEM_VOTO, SETVAL, 1);

    kid_pids = malloc(pop_size*sizeof(*kid_pids));


    for(i = 0; i < pop_size; i++){

      switch(kid_pids[i]=fork()) {

        case -1:
          fprintf(stderr, "Error with the fork\n");
            exit(EXIT_FAILURE);

        case 0: //figlio

          sprintf(num, "%d", i);
          sprintf(pop,"%d",pop_size);
          my_argv[0] = num;
          my_argv[1] = pop;
          my_argv[2] = NULL;

          execve("./studente",my_argv,NULL);

          break;

          default:

          break;
    }
  }

    sops.sem_flg=0;
    sops.sem_num = ID_PADRE;
    sops.sem_op = -pop_size;
    semop(sem_id,&sops , 1); /* attendo che ogni figlio abbia incrementato il semaforo per poter partire*/



    signal(SIGALRM, handler);


    if (reserveSem(sem_id, SEM_VOTO) == -1 )
      TEST_ERROR;

    alarm(SIM_TIME);

      i=0;
      while (i < pop_size && (child_pid = waitpid(kid_pids[i], &status, 0)) != -1) {
          i++;
      }

}


void handler(int signal) {

  if (reserveSem(sem_id, ID_ALARM) == -1 )
    TEST_ERROR;

    voto_SO();

    sops.sem_flg=0;
    sops.sem_num = SEM_VOTO;
    sops.sem_op = -pop_size;
    semop(sem_id,&sops , 1);

    media_Arch();
    media_SO();

    free(kid_pids);

    if(semctl(sem_id, 0, IPC_RMID, NULL) == -1)
      TEST_ERROR;

    if(shmctl(shm_id, 0, IPC_RMID)==-1)
      TEST_ERROR;

    if(msgctl(msg_id, IPC_RMID, NULL) ==-1)
      TEST_ERROR;

    if(msgctl(vote_msg, IPC_RMID, NULL)==-1)
      TEST_ERROR;

    exit(EXIT_SUCCESS);
}


void media_Arch(){

  double media =0;

  for(int j=18; j<=30; j++){
      int contatore=0;

      for(int i=0; i<pop_size; i++){
          if(pMem->stud_vec[i].voto_AdE==j)
            contatore++;
      }

      media = media + (contatore*j);
      printf("Architettura degli Elaboratori: Studenti %d con voto: %d\n", contatore, j);
  }
  printf("\nVOTO MEDIO DI ARCHITETTURA DEGLI ELABORATORI: %f\n", media/pop_size);
  printf("\n");
}


void voto_SO(){

  for(int i =0; i < pop_size; i++){

    if(pMem->stud_vec[i].membri==1){
      pMem->stud_vec[i].voto_SO=0;

    }else if(pMem->stud_vec[i].membri!=pMem->stud_vec[i].nof_elems && pMem->stud_vec[i].membri!=1){
      pMem->stud_vec[i].voto_SO=pMem->stud_vec[i].voto_max-3;

    }else{
      pMem->stud_vec[i].voto_SO=pMem->stud_vec[i].voto_max;
    }

    v_msg.mtype = pMem->stud_vec[i].matricola;
    v_msg.from = GESTORE;

    if(msgsnd(vote_msg ,&v_msg, sizeof(v_msg) - sizeof(long),0) == -1){
      TEST_ERROR;
      exit(EXIT_FAILURE);
    }
  }
}


void media_SO(){

  double media =0;

  for(int j=15; j<=30; j++){
    int contatore=0;

    for(int i=0; i<pop_size; i++){
      if(pMem->stud_vec[i].voto_SO==j)
        contatore++;
      }

    media = media + (contatore*j);
    printf("Sistemi Operativi: Studenti %d con voto: %d\n", contatore, j);
  }
  printf("\nVOTO MEDIO DI SISTEMI OPERATIVI: %f\n", media/pop_size);
  printf("\n");
}
