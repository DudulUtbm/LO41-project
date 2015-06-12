#include "vehicule.h"

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


vehicule* creationVehicule(int num) //alloue de la mémoire et initialise les attributs

{
    /* random pour le type de voiture 0->normal 1->prioritaire.
     * random pour la position 
     * random pour l'itinéraire
    */
    vehicule* newVehicule=(vehicule*)malloc(sizeof(vehicule));

    newVehicule->num = num;
    newVehicule->type = get_random(2); 
    newVehicule->position = get_random(8);
    do{
	    newVehicule->itineraire = get_random(8);
    }while(newVehicule->position==newVehicule->itineraire);

    AfficheEtatV(newVehicule);

    return newVehicule;

}

void deleteVehicule(vehicule* current) //libère la mémoire du véhicule
{
	free(current);
}

void enter_interchange(long numVehicule,pthread_mutex_t* mutex,pthread_cond_t* condition){ //fonction d'arrivé dans un échangeur

	sleep(2);

	pthread_mutex_lock(mutex);
	pthread_cond_signal (condition);
	pthread_mutex_unlock(mutex);

	sleep(2);


}
