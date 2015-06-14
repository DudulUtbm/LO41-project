#ifndef ECHANGEUR_H_
#define ECHANGEUR_H_

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
//header of the echangeur and file attente library

#define CAPACITE 10

typedef struct file_Attente
{
	int list[CAPACITE]; 
	int lastUsed;
	int nbAttente;
	int ID;
}file_Attente;

typedef struct echangeur
{
	    int ID;
	    int nbV;
	    file_Attente file_attente[4];
/*	    file_Attente nord; id=0
	    file_Attente sud; id=1
	    file_Attente est; id=2
	    file_Attente ouest; id=3  */
}echangeur ;

void init_echangeur(echangeur* current,int id); //fonction qui initialise un echangeur
void afficheEtatR(echangeur* current); //fonction qui affiche l'etat d'un echangeur
int sortir_liste(file_Attente* attente); //fonction qui retire le véhicule en tete de la liste
void init_liste(file_Attente* attente,int id); //fonction qui initiale une liste d'attente
void ajouter_liste(file_Attente* attente, int Num_vehicule); //fonction qui ajoute un véhiculeà une liste d'attente
void print_liste(file_Attente* attente); //fonction qui affiche le contenue et les attributs de la liste 
file_Attente* min_veh(echangeur* echangeur);//retourne la file d'attente avec le nb minimum de vehicule
file_Attente* max_veh(echangeur* echangeur);//retourne la file d'attente avec le nb maximum de vehicule
file_Attente* recently_used(echangeur* echangeur);//retourne la file d'attente avec utilisé le plus recement
file_Attente* last_used(echangeur* echangeur);//retourne la file d'attente avec utilisé il y le plus longtemps

#endif
