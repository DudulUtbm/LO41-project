#ifndef MAIN_H_
#define MAIN_H_

//header of the main file
//
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
	    long num;
}echangeur ;


void erreur(const char *msg);
int get_random (int max);
void AfficheEtatV(vehicule* current);
void *creationVehicule(void *data);



#endif 
