#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include "main.h"

echangeur Echangeur_id[NUM_INTERCHANGE];

//COMMON FUNCTIONS

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

//THREAD VEHICLES FUNCTIONS

void AfficheEtatV(vehicule* current)
{

    printf("\nJe suis la voiture  #%d \nde TID : %ld \nde type %d \nje pars de %d et je vais à %d\n",current->num,(long) pthread_self(),current->type,current->position,current->itineraire);
    fflush(stdout);
}


void *creationVehicule(void *data)
{
    /* random pour le type de voiture 0->normal 1->prioritaire.
     * random pour la position 
     * random pour l'itinéraire
    */
    vehicule newVehicule;

    newVehicule.num = (int) data;
    newVehicule.type = get_random(2); 
    newVehicule.position = get_random(8);
    do{
	    newVehicule.itineraire = get_random(8);
    }while(newVehicule.position==newVehicule.itineraire);

//    enter_interchange(newVehicule.num); //fonction d'arrivé dans un échangeur

    AfficheEtatV(&newVehicule);
    pthread_exit(NULL);

}

//File d'attente
void init_liste(file_Attente attente){

	for(int i=0;i<CAPACITE;+i){
		attente.list[i]=-1;
	}
	attente.lastUsed=0;
	attente.nbAttente=0;

}

int sortir_liste(file_Attente attente) //fonction qui retire le véhicule en tete de la liste
{
	int current,tmp,i;
	current=attente.list[0];

	for(i=0;i<attente.nbAttente;++i){
		attente.list[i]=attente.list[i+1];	
	}
	attente.list[i]=-1;
	attente.nbAttente--;
	attente.lastUsed++;

	return current;
}

void ajouter_liste(file_Attente attente, vehicule vehicule){
	attente.list[attente.nbAttente]=vehicule.num;
	attente.nbAttente++;
}

void print_liste(file_Attente attente){
	
	for(int i=0;i<attente.nbAttente;++i){
		printf("[%d] vehicule n°%d \n",i,attente.list[i]);
	}	
	printf("lastUsed = %d\n",attente.lastUsed);
	printf("nbAttente = %d\n",attente.nbAttente);
}

file_Attente min_veh(echangeur echangeur){
	
	int i=0;
	file_Attente minimum=echangeur.file_attente[i];
	for(i=1;i<4;i++){
		if(echangeur.file_attente[i].nbAttente>0 && echangeur.file_attente[i].nbAttente<minimum.nbAttente)minimum=echangeur.file_attente[i];
	}
	return minimum;

}

file_Attente max_veh(echangeur echangeur){
	
	int i=0;
	file_Attente maximum=echangeur.file_attente[i];
	for(i=1;i<4;i++){
		if(echangeur.file_attente[i].nbAttente>maximum.nbAttente)maximum=echangeur.file_attente[i];
	}
	return maximum;

}

file_Attente last_used(echangeur echangeur){
	
	int i=0;
	file_Attente minimum=echangeur.file_attente[i];
	for(i=1;i<4;i++){
		if(echangeur.file_attente[i].lastUsed<minimum.lastUsed)minimum=echangeur.file_attente[i];
	}
	return minimum;

}

file_Attente recently_used(echangeur echangeur){
	
	int i=0;
	file_Attente maximum=echangeur.file_attente[i];
	for(i=1;i<4;i++){
		if(echangeur.file_attente[i].lastUsed>maximum.lastUsed)maximum=echangeur.file_attente[i];
	}
	return maximum;

}
//ROUND ROBIN

void round_robin(void* data){

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

}

void afficheEtatR(echangeur* current){

	    printf("\nJe suis l'echangeur de TID : %ld \n j'ai %d véhicules \n",(long) pthread_self(),current->nbV);
    for(int i=0;i<4;++i){
	    print_liste(current->file_attente[i]);
    }
    fflush(stdout);
}


//MAIN FUNCTION

int main(void)
{

    int i;
	
	//INTERCHANGE
	
    for (i = 0; i < NUM_INTERCHANGE; i++) {
	Echangeur_id[i].nbV=0;
	//init file d'attente

  }

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
	pthread_t Vthread_id[NUM_VEHICLES];
	
    for (i = 0; i < NUM_VEHICLES; i++) {

	if (pthread_create (&Vthread_id[i], &thread_attr,creationVehicule ,(void*)i) < 0) {
		fprintf (stderr, "pthread_create error for thread \n");
		exit (1);
	}
	 
    }	    	 
	    	//Round Robin
	pthread_t Rthread_id[NUM_INTERCHANGE];
	
    for (i = 0; i < NUM_INTERCHANGE; i++) {

	if (pthread_create (&Rthread_id[i], &thread_attr,round_robin ,(void*)i) < 0) {
		fprintf (stderr, "pthread_create error for thread \n");
		exit (1);
	}
	 
    }	
	pthread_exit(NULL);
}
