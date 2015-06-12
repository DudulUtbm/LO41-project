#ifndef VEHICULE_H_
#define VEHICULE_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//header of the vehicule library


typedef struct vehicule
{
	    int type;
	    int position;
	    int itineraire;
	    int num;
}vehicule ;

vehicule* creationVehicule(int num); //alloue de la mémoire et initialise les attributs
void deleteVehicule(vehicule* current); //libère la mémoire du véhicule
void AfficheEtatV(vehicule* current); //fonction qui affiche l'etat un véhicule
int get_random (int max); //fonction qui génère un nombre random entre 0 et max-1
void enter_interchange(long numVehicule,pthread_mutex_t* mutex,pthread_cond_t* condition); //fonction d'arrivé dans un échangeur


#endif
