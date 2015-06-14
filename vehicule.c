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

    printf("\nJe suis la voiture  #%d \nde TID : %ld \nde type %d \nje pars de %d et je vais à %d\n",current->num,(long) pthread_self(),current->type,current->position,current->destination);
    fflush(stdout);
}


vehicule* creationVehicule(int num) //alloue de la mémoire et initialise les attributs

{
    /* random pour le type de voiture 0->normal 1->prioritaire.
     * random pour la position 
     * random pour la destination
    */
    vehicule* newVehicule=(vehicule*)malloc(sizeof(vehicule));
    newVehicule->num = num;
    newVehicule->type = get_random(2); 
    newVehicule->position = get_random(8);
    do{
	    newVehicule->destination = get_random(8);
    }while(newVehicule->position==newVehicule->destination);
    switch(newVehicule->position){
	    case 0:
		    newVehicule->num_curr_echangeur=0;
		    break;
	    case 1:
		    newVehicule->num_curr_echangeur=0;
		    break;
	    case 2:
		    newVehicule->num_curr_echangeur=1;
		    break;
            case 3:
		    newVehicule->num_curr_echangeur=1;
		    break;
            case 4:
		    newVehicule->num_curr_echangeur=2;
		    break;
            case 5:
		    newVehicule->num_curr_echangeur=2;
		    break;
            case 6:
		    newVehicule->num_curr_echangeur=3;
		    break;
            case 7:
		    newVehicule->num_curr_echangeur=3;
		    break;
	    default:
		    newVehicule->num_curr_echangeur=-1;
		    break;
    }
    AfficheEtatV(newVehicule);

    return newVehicule;

}

void deleteVehicule(vehicule* current) //libère la mémoire du véhicule
{
	free(current);
}

