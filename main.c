#include "main.h"

//    echangeur Echangeur_id[NUM_INTERCHANGE];
//    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//    pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

//	current->mutex = PTHREAD_MUTEX_INITIALIZER;
//	current->condition = PTHREAD_COND_INITIALIZER;
//	pthread_mutex_init(current->mutex,NULL); 
//	pthread_cond_init(current->condition,NULL); 

//COMMON FUNCTIONS

void erreur(const char *msg)
{
    perror(msg);
    exit(1);
}

//ROUND ROBIN

void* threadEchangeur(void* data){

	int i = (int)data;
	echangeur current;
	current = Echangeur_id[i];
	afficheEtatR(&current);
	/* while(1)
	 * 	P(echangeur1)
	 * 	launch round robin
	 * 	reveille le thread en tete de la liste choisis
	 * end
	*/	
	while(1){
		
		pthread_mutex_lock(&mutex);
		fprintf(stderr,"\nJe suis %ld, je me mets en attente.\n",pthread_self());
		pthread_cond_wait (&condition,&mutex);
		fprintf(stderr,"\nJe suis %ld, je me reveille.\n",pthread_self());
		pthread_mutex_unlock(&mutex);

	}

}

void *threadVehicule(void *data)
{
    vehicule* current;
    int ID = (int) data;

    current = creationVehicule(ID);

    enter_interchange(current->num,&mutex,&condition); //fonction d'arrivé dans un échangeur

    deleteVehicule(current);
    pthread_exit(NULL);
}



//MAIN FUNCTION

int main(void)
{

    int i;
	
	//INTERCHANGE
    fprintf(stderr,"\nCréation des échangeurs\n");

    for (i = 0; i < NUM_INTERCHANGE; i++) {
	init_echangeur(&Echangeur_id[i],i);
  }

    fprintf(stderr,"\nInitialisation des threads\n");
	//THREAD INIT
	pthread_attr_t thread_attr;

  if (pthread_attr_init (&thread_attr) != 0) {
    fprintf (stderr, "pthread_attr_init error");
    exit (1);
  }

  if (pthread_attr_setdetachstate (&thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
    fprintf (stderr, "pthread_attr_setdetachstate error");

    exit (1);
  }
	//THREAD CREATION

    	    	//VEHICLES
        fprintf(stderr,"\nCréation des threads\n");
	pthread_t Vthread_id[NUM_VEHICLES];
	
        fprintf(stderr,"\nthreads de véhicule\n");
    for (i = 0; i < NUM_VEHICLES; i++) {

	if (pthread_create (&Vthread_id[i], &thread_attr,threadVehicule ,(void*)i) < 0) {
		fprintf (stderr, "pthread_create error for thread \n");
		exit (1);
	}
	 
    }	    	 
	    	//INTERCHANGES
	pthread_t Rthread_id[NUM_INTERCHANGE];
	
        fprintf(stderr,"\nthreads d'échangeur\n");
    for (i = 0; i < NUM_INTERCHANGE; i++) {

	if (pthread_create (&Rthread_id[i], &thread_attr,threadEchangeur ,(void*)i) < 0) {
		fprintf (stderr, "pthread_create error for thread \n");
		exit (1);
	}
	 
    }	
	pthread_exit(NULL);
}
