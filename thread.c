#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#define NUM_THREADS	10

void erreur(const char *msg)
{
    perror(msg);
    exit(1);
}

//fonction qui retourne un nombre entre 0 et max.
int get_random (int max){
	   double val;
      val = (double) max * rand ();
	 val = val / (RAND_MAX + 1.0);
	    return ((int) val);
}

void *AfficheEtat(void *data)
{

    long num;
    int type, position, itineraire;
    num = (long) data;
    /* random pour le type de voiture 0->normal 1->prioritaire.
     * random pour la position 
     * random pour l'itinéraire
    */
    type = get_random(2); 
    position = get_random(8);
    do{
	    itineraire = get_random(8);
    }while(position==itineraire);



    printf("\nJe suis la voiture  #%ld \nde TID : %ld \nde type %d \nje pars de %d et je vais à %d\n",num,(long) pthread_self(),type,position,itineraire);
    fflush(stdout);
    pthread_exit(NULL);
}

int main(void)
{
	pthread_attr_t thread_attr;

  if (pthread_attr_init (&thread_attr) != 0) {
    fprintf (stderr, "pthread_attr_init error");
    exit (1);
  }

  if (pthread_attr_setdetachstate (&thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
    fprintf (stderr, "pthread_attr_setdetachstate error");

    exit (1);
  }

    int i,j, rc;
    pthread_t thread_id[NUM_THREADS];
	
    for (i = 0; i < NUM_THREADS; i++) {

	if (pthread_create (&thread_id[i], &thread_attr, AfficheEtat,(void*)i) < 0) {
          fprintf (stderr, "pthread_create error for thread 1\n");
        exit (1);
  }
	 
    }
		    	 
	pthread_exit(NULL);
}
