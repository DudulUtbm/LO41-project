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

#include "vehicule.h"
#include "echangeur.h"

#define NUM_INTERCHANGE	4
#define NUM_VEHICLES	10

//header of the main file

//Global variables

echangeur Echangeur_id[NUM_INTERCHANGE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

void erreur(const char *msg); //fonction pour afficher une erreur
void* threadEchangeur(void* data); //fonction qui gère un echangeur. Elle est lancé 1 fois par echangeur
void *threadVehicule(void *data); //fonction qui gère les déplacement d'un véhicule. Elle est lancée une fois par véhicule

#endif 
