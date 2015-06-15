#include "echangeur.h"

void init_echangeur(echangeur* current,int id){
	
	current->ID=id;
	current->nbV=0;
	for(int i=0;i<4;++i){
		init_liste(&(current->file_attente[i]),i);
	}
/*	current->mutex = PTHREAD_MUTEX_INITIALIZER;
	current->condition = PTHREAD_COND_INITIALIZER;
	pthread_mutex_init(current->mutex,NULL); 
	pthread_cond_init(current->condition,NULL); */

}

int compter_vehicule(echangeur* echangeur){ //fonction qui actualise le nb de vehicule en attente dans un echangeur
	int nbVehicule=0;
	for(int i=0;i<4;++i){
		nbVehicule+=echangeur->file_attente[i].nbAttente;
	}
	return nbVehicule;
}
void afficheEtatR(echangeur* current){

	    printf("\nJe suis l'echangeur %d, de TID : %ld \n j'ai %d véhicules \n",current->ID,(long) pthread_self(),current->nbV);
    for(int i=0;i<4;++i){
	    print_liste(&(current->file_attente[i]));
    }
    fflush(stdout);
}

//File d'attente
void init_liste(file_Attente* attente,int id){

	for(int i=0;i<CAPACITE;++i){
		attente->list[i]=-1;
	}
	attente->ID=id;
	attente->lastUsed=0;
	attente->nbAttente=0;

}

int sortir_liste(file_Attente* attente) //fonction qui retire le véhicule en tete de la liste
{
	int current,tmp,i;
	current=attente->list[0];

	for(i=0;i<attente->nbAttente;++i){
		attente->list[i]=attente->list[i+1];	
	}
	attente->list[i]=-1;
	attente->nbAttente--;
	attente->lastUsed++;

	return current;
}

void ajouter_liste(file_Attente* attente, int Num_vehicule){
	attente->list[attente->nbAttente]=Num_vehicule;
	attente->nbAttente++;
}

void print_liste(file_Attente* attente){
	
	for(int i=0;i<attente->nbAttente;++i){
		printf("[%d] vehicule n°%d \n",i,attente->list[i]);
	}	
	printf("lastUsed = %d\n",attente->lastUsed);
	printf("nbAttente = %d\n",attente->nbAttente);
}

file_Attente* min_veh(echangeur* echangeur){	//test avec celle-ci
	
	int i=0;
	file_Attente* minimum=&(echangeur->file_attente[i]);
	for(i=1;i<4;i++){
		if(echangeur->file_attente[i].nbAttente>0 && echangeur->file_attente[i].nbAttente<minimum->nbAttente)minimum=&(echangeur->file_attente[i]);
	}
	return minimum;

}

file_Attente* max_veh(echangeur* echangeur){
	
	int i=0;
	file_Attente* maximum=&(echangeur->file_attente[i]);
	for(i=1;i<4;i++){
		if(echangeur->file_attente[i].nbAttente>maximum->nbAttente)maximum=&(echangeur->file_attente[i]);
	}
	return maximum;

}

file_Attente* last_used(echangeur* echangeur){
	
	int i=0;
	file_Attente* minimum=&(echangeur->file_attente[i]);
	for(i=1;i<4;i++){
		if(echangeur->file_attente[i].lastUsed<minimum->lastUsed)minimum=&(echangeur->file_attente[i]);
	}
	return minimum;

}

file_Attente* recently_used(echangeur* echangeur){
	
	int i=0;
	file_Attente* maximum=&(echangeur->file_attente[i]);
	for(i=1;i<4;i++){
		if(echangeur->file_attente[i].lastUsed>maximum->lastUsed)maximum=&(echangeur->file_attente[i]);
	}
	return maximum;

}

