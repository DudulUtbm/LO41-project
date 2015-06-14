#ifndef MAIN_H_
#define MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>

#include "vehicule.h"
#include "echangeur.h"

#define NUM_INTERCHANGE	4
#define NUM_VEHICLES	10

//header of the main file

//Global variables

echangeur Echangeur_id[NUM_INTERCHANGE];

//Protection des echangeur (RC)

pthread_mutex_t mutex_echangeur0 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_echangeur1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_echangeur2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_echangeur3 = PTHREAD_MUTEX_INITIALIZER;

//Declenchement du choix de la liste

pthread_cond_t cond_echangeur0 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_echangeur1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_echangeur2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_echangeur3 = PTHREAD_COND_INITIALIZER;

//cond pour le premier de la file d'attente
pthread_cond_t ech0_fileN = PTHREAD_COND_INITIALIZER;
pthread_cond_t ech0_fileS = PTHREAD_COND_INITIALIZER;
pthread_cond_t ech0_fileE = PTHREAD_COND_INITIALIZER;
pthread_cond_t ech0_fileO = PTHREAD_COND_INITIALIZER;

pthread_cond_t ech1_fileN = PTHREAD_COND_INITIALIZER;
pthread_cond_t ech1_fileS = PTHREAD_COND_INITIALIZER;
pthread_cond_t ech1_fileE = PTHREAD_COND_INITIALIZER;
pthread_cond_t ech1_fileO = PTHREAD_COND_INITIALIZER;

pthread_cond_t ech2_fileN = PTHREAD_COND_INITIALIZER;
pthread_cond_t ech2_fileS = PTHREAD_COND_INITIALIZER;
pthread_cond_t ech2_fileE = PTHREAD_COND_INITIALIZER;
pthread_cond_t ech2_fileO = PTHREAD_COND_INITIALIZER;

pthread_cond_t ech3_fileN = PTHREAD_COND_INITIALIZER;
pthread_cond_t ech3_fileS = PTHREAD_COND_INITIALIZER;
pthread_cond_t ech3_fileE = PTHREAD_COND_INITIALIZER;
pthread_cond_t ech3_fileO = PTHREAD_COND_INITIALIZER;

//fonction generales

void erreur(const char *msg); //fonction pour afficher une erreur
pthread_mutex_t* selectMutex(int ID); //fonction pour determiner quel mutex utiliser
pthread_cond_t* selectCond(int ID); //fonction pour determiner quelle condition utiliser
void* threadEchangeur(void* data); //fonction qui gère un echangeur. Elle est lancé 1 fois par echangeur
void *threadVehicule(void *data); //fonction qui gère les déplacement d'un véhicule. Elle est lancée une fois par véhicule
pthread_cond_t* choose_liste(echangeur* current); //determine quelle condition liste sera la suivante a passer dans l'echangeur
void enter_interchange(vehicule* current,pthread_mutex_t* mutex,pthread_cond_t* condition); //fonction d'arrivé dans un échangeur
void exit_interchange(vehicule* current,pthread_mutex_t* mutex,pthread_cond_t* condition); //fonction de sortie d'un échangeur
file_Attente* determine_liste(int numFile); //renvoie un pointeur sur la file d'attente correspondant au numero de File
void cleanMemory(); //fonction qui ferme tout correctement et vide la mémoire

#endif 
