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

int initMystruct(student_t *pDati){
  if(!pDati) return -1;
  pDati->voto_AdE=18+rand()%13;
  pDati->chiuso=0;
  pDati->accetto=0;
  pDati->leader=0;
  pDati->voto_SO=0;
  pDati->membri=1;
  pDati->voto_max=pDati->voto_AdE;
  if(pDati->matricola%2==0)
    pDati->turno=2;
  else
    pDati->turno=1;

  return 0;
}


void StampaStruct(student_t* pDati,int i){

    printf("Matricola %d \
            Turno: %d       Preferenza: %d   Voto Architettura:%d\n",getpid(),pDati->turno,pDati->nof_elems,pDati->voto_AdE);

}

int reserveSem(int id, int semNum) {
    struct sembuf sops;


    sops.sem_num = semNum;
    sops.sem_op = -1;
    sops.sem_flg = 0;

    return semop(id, &sops, 1);

}

int releaseSem(int id, int semNum) {
    struct sembuf sops;


    sops.sem_num = semNum;
    sops.sem_op = 1;
    sops.sem_flg = 0;

    return semop(id, &sops, 1);

}

int waitZero(int id, int semNum) {
    struct sembuf sops;


    sops.sem_num = semNum;
    sops.sem_op = 0;
    sops.sem_flg = 0;

    return semop(id, &sops, 1);

}

void get_info(int *nof_invites,int *max_reject, int *group_2, int *group_3, int *group_4){
  FILE *opt;
    char  attributo[50];
    char valore[50];
    opt=fopen("opt.conf","r");
    fgets(attributo,15,opt);
    fgets(valore,4,opt);
    *group_2=atoi(valore);

    fgets(attributo,15,opt);
    fgets(valore,4,opt);
    *group_3=atoi(valore);

    fgets(attributo,15,opt);
    fgets(valore,4,opt);
    *group_4=atoi(valore);

    fgets(attributo,15,opt);
    fgets(valore,4,opt);
    *nof_invites=atoi(valore);

    fgets(attributo,15,opt);
    fgets(valore,4,opt);
    *max_reject=atoi(valore);
    fclose(opt);
}
