#ifndef MAIN_H_
#define MAIN_H_

//header of the main file

#define CAPACITE 10  
#define NUM_INTERCHANGE	4
#define NUM_VEHICLES	10

typedef struct vehicule
{
	    int type;
	    int position;
	    int itineraire;
	    long num;
}vehicule ;

typedef struct echangeur
{
	    int nbV;
	    pthread_t nord[CAPACITE];
	    pthread_t sud[CAPACITE];
	    pthread_t est[CAPACITE];
	    pthread_t ouest[CAPACITE];
}echangeur ;


void erreur(const char *msg);
int get_random (int max);
void AfficheEtatV(vehicule* current);
void *creationVehicule(void *data);



#endif 
