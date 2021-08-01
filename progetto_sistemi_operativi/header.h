#define TEST_ERROR    if (errno) {dprintf(STDERR_FILENO,		\
					  "%s:%d: PID=%5d: Error %d (%s)\n", \
					  __FILE__,			\
					  __LINE__,			\
					  getpid(),			\
					  errno,			\
					  strerror(errno));}

#define KEY_SEM 10
#define KEY_MEM 20
#define KEY_MSG 30
#define KEY_VOTE 40
#define POP_SIZE 100
#define SEM_VOTO 3
#define ID_SINCRO 0 /* id semaforo*/
#define ID_PADRE 1 /* id semaforo*/
#define ID_ALARM 2 /* id semaforo*/
#define RICHIESTA 2 /* messaggio di richiesta*/
#define ACCETTO 1 /*accetto richiesta*/
#define RIFIUTO -1
#define GESTORE 7
#define SIM_TIME 4


typedef struct Mystruct {
  int matricola; //se pid%2==0 matricola pari, altrimenti dispari
  int voto_AdE; //voto architettura 18 <= voto_AdE <= 30
	int nof_elems;
	int nof_invites;
	int max_reject;
	int leader;
	int accetto;
	int turno; // 1 turno dispari , 2 pari
  int chiuso; //0 chiuso , 1 aperto
  int group_id;
	int membri;
	int *gruppo;
	int voto_SO;
	int voto_max;

}student_t;

struct shared_data{
	student_t stud_vec[POP_SIZE];
	int group_2, group_3, group_4;
	int nof_invites;
	int max_reject;
};


union semun
{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
};

struct message {
  long mtype;
  int mtext;
	int from; 

};




int initMystruct(student_t* pDati);

void StampaStruct(student_t *pData,int i);

void get_info(int *nof_invites,int *max_reject, int *group_2, int *group_3, int *group_4);

int reserveSem(int id, int semNum);

int releaseSem(int id, int semNum);

int waitZero(int id, int semNum);
