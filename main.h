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
	    int num;
}vehicule ;

typedef struct file_Attente
{
	int list[CAPACITE]; //a harmoniser
	int lastUsed;
	int nbAttente;
}file_Attente;

typedef struct echangeur
{
	    int nbV;
	    file_Attente file_attente[4];
/*	    file_Attente nord; id=0
	    file_Attente sud; id=1
	    file_Attente est; id=2
	    file_Attente ouest; id=3  */
}echangeur ;


void erreur(const char *msg); //fonction pour afficher une erreur
int get_random (int max); //fonction qui génère un nombre random entre 0 et max-1
void AfficheEtatV(vehicule* current); //fonction qui affiche l'etat un véhicule
void *creationVehicule(void *data); //fonction d'initialisation d'un véhicule
void enter_interchange(long numVehicule); //fonction d'arrivé dans un échangeur
int sortir_liste(file_Attente attente); //fonction qui retire le véhicule en tete de la liste
void init_liste(file_Attente attente); //fonction qui initiale une liste d'attente
void ajouter_liste(file_Attente attente, vehicule vehicule); //fonction qui ajoute un véhiculeà une liste d'attente
file_Attente min_veh(echangeur echangeur);//retourne la file d'attente avec le nb minimum de vehicule
file_Attente max_veh(echangeur echangeur);//retourne la file d'attente avec le nb maximum de vehicule
void round_robin(echangeur echangeur); //fonction qui gère le round robin

#endif 
