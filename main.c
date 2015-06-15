#include "main.h"

//    echangeur Echangeur_id[NUM_INTERCHANGE];
//    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//    pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

//	current->mutex = PTHREAD_MUTEX_INITIALIZER;
//	current->condition = PTHREAD_COND_INITIALIZER;
//	pthread_mutex_init(current->mutex,NULL); 
//	pthread_cond_init(current->condition,NULL); 

//COMMON FUNCTIONS

void erreur(const char *msg)
{
    perror(msg);
    exit(1);
}

pthread_mutex_t* selectMutex(int ID){

	pthread_mutex_t* tmp;
	switch(ID){

		case 0:
			tmp=&mutex_echangeur0;
			break;
		case 1: 
			tmp=&mutex_echangeur1;
			break;
		case 2: 
			tmp=&mutex_echangeur2;
			break;
		case 3:
			tmp=&mutex_echangeur3;
			break;
	
		default:
			printf("Le numéro d'echangeur n'est pas bon");
			tmp = NULL;
			break;
	 }
	return tmp;
}

pthread_cond_t* selectCond(int ID){

	pthread_cond_t* tmp;
	switch(ID){

		case 0:
			tmp=&cond_echangeur0;
			break;
		case 1: 
			tmp=&cond_echangeur1;
			break;
		case 2: 
			tmp=&cond_echangeur2;
			break;
		case 3:
			tmp=&cond_echangeur3;
			break;

		default:
			printf("Le numéro d'echangeur n'est pas bon");
			tmp = NULL;
			break;
	 }
	return tmp;
}

pthread_mutex_t* selectMutexV(int position){

	pthread_mutex_t* tmp;
	switch(position){

		case 0:
			tmp=&mutex_echangeur0;
			break;
		case 1: 
			tmp=&mutex_echangeur0;
			break;
		case 2: 
			tmp=&mutex_echangeur1;
			break;
		case 3:
			tmp=&mutex_echangeur1;
			break;
		case 4:
			tmp=&mutex_echangeur2;
			break;
		case 5:  
			tmp=&mutex_echangeur2;
			break;
		case 6: 
			tmp=&mutex_echangeur3;
			break;
		case 7:
			tmp=&mutex_echangeur3;
			break;
		case 8:
			tmp=&mutex_echangeur0;
			break;
		case 9:
			tmp=&mutex_echangeur0;
			break;
		case 10:
			tmp=&mutex_echangeur1;
			break;
		case 11:
			tmp=&mutex_echangeur1;
			break;
		case 12:
			tmp=&mutex_echangeur2;
			break;
		case 13:
			tmp=&mutex_echangeur2;
			break;
		case 14:
			tmp=&mutex_echangeur3;
			break;
		case 15:
			tmp=&mutex_echangeur3;
			break;
		default:
			printf("Le numéro d'echangeur n'est pas bon");
			tmp = NULL;
			break;
	 }
	return tmp;
}

pthread_cond_t* selectCondV(int position){

	pthread_cond_t* tmp;
	switch(position){

		case 0:
			tmp=&cond_echangeur0;
			break;
		case 1: 
			tmp=&cond_echangeur0;
			break;
		case 2: 
			tmp=&cond_echangeur1;
			break;
		case 3:
			tmp=&cond_echangeur1;
			break;
		case 4:
			tmp=&cond_echangeur2;
			break;
		case 5:  
			tmp=&cond_echangeur2;
			break;
		case 6: 
			tmp=&cond_echangeur3;
			break;
		case 7:
			tmp=&cond_echangeur3;
			break;
		case 8:
			tmp=&cond_echangeur0;
			break;
		case 9:
			tmp=&cond_echangeur0;
			break;
		case 10:
			tmp=&cond_echangeur1;
			break;
		case 11:
			tmp=&cond_echangeur1;
			break;
		case 12:
			tmp=&cond_echangeur2;
			break;
		case 13:
			tmp=&cond_echangeur2;
			break;
		case 14:
			tmp=&cond_echangeur3;
			break;
		case 15:
			tmp=&cond_echangeur3;
			break;
		default:
			printf("Le numéro d'echangeur n'est pas bon");
			tmp = NULL;
			break;
	 }
	return tmp;
}

pthread_cond_t* choose_liste(echangeur* current){

	pthread_cond_t* tmp=NULL;
	file_Attente* liste=NULL;

	liste=max_veh(current); //a changer pour modifier l'algo d'ordonnacement
	switch(current->ID){
		case 0:
			switch(liste->ID){
				case 0:
					tmp = &ech0_fileN;
					break;
 				case 1:
					tmp = &ech0_fileE;
					break;
 				case 2:
					tmp = &ech0_fileS;
					break;
 				case 3:
					tmp = &ech0_fileO;
					break;
				default:
					tmp = NULL;
					break;
			}
			break;
		case 1:
			switch(liste->ID){
				case 0:
					tmp = &ech1_fileN;
					break;
 				case 1:
					tmp = &ech1_fileE;
					break;
 				case 2:
					tmp = &ech1_fileS;
					break;
 				case 3:
					tmp = &ech1_fileO;
					break;
				default:
					tmp = NULL;
					break;
			}
			break;
		case 2:
			switch(liste->ID){
				case 0:
					tmp = &ech2_fileN;
					break;
 				case 1:
					tmp = &ech2_fileE;
					break;
 				case 2:
					tmp = &ech2_fileS;
					break;
 				case 3:
					tmp = &ech2_fileO;
					break;
				default:
					tmp = NULL;
					break;
			}
			break;
		case 3:
			switch(liste->ID){
				case 0:
					tmp = &ech3_fileN;
					break;
 				case 1:
					tmp = &ech3_fileE;
					break;
 				case 2:
					tmp = &ech3_fileS;
					break;
 				case 3:
					tmp = &ech3_fileO;
					break;
				default:
					tmp = NULL;
					break;
			}
			break;
		default:
			tmp = NULL;
			break;
		tmp = NULL;
	}
		return tmp;
}
//ROUND ROBIN

void* threadEchangeur(void* data){

	int i = (int)data;
	echangeur* current;
	current = &Echangeur_id[i];
	pthread_mutex_t* current_mutex = selectMutex(i);
	pthread_cond_t* echangeur_cond = selectCond(i);
	pthread_cond_t* liste_cond = NULL;
	afficheEtatR(current);
	/* while(1)
	 * 	P(echangeur1)
	 * 	launch round robin
	 * 	reveille le thread en tete de la liste choisis
	 * end
	*/	
	while(1){
		
		compter_vehicule(current);
		if(current->nbV==0){
			pthread_mutex_lock(current_mutex);
			fprintf(stderr,"\nJe suis %ld, je me mets en attente.\n",pthread_self());
			pthread_cond_wait (echangeur_cond,current_mutex);
			fprintf(stderr,"\nJe suis %ld, je me reveille.\n",pthread_self());
			pthread_mutex_unlock(current_mutex);
		}

		//choisis une file d'attente et reveille le vehicule en tete de liste
		pthread_mutex_lock(current_mutex);
		fprintf(stderr,"\nJe suis %ld, je fais passer un vehicule.\n",pthread_self());
		liste_cond = choose_liste(current);
		pthread_cond_signal(liste_cond);
		pthread_mutex_unlock(current_mutex);
		//solution temporaire : 
		//-1 condition pour celui en tete de file d'attente
		//-les autres sont bloqués par un mutex bien précis quand le premier quitte la file, l'un des vehicules passe premier
		// 'pb' ce n'est plus un fifo
		sleep(1);
	}
    pthread_exit(NULL);

}

void *threadVehicule(void *data)
{
    vehicule* current;
    int ID = (int) data;

    current = creationVehicule(ID);
    pthread_mutex_t* current_mutex = selectMutexV(current->position);
    pthread_cond_t* echangeur_cond = selectCondV(current->position);
    pthread_cond_t* liste_cond = NULL;

    if(current_mutex==NULL)fprintf(stderr,"OMG mutex IS NULL\n");
    if(echangeur_cond==NULL)fprintf(stderr,"OMG condition IS NULL\n");
    enter_interchange(current,current_mutex,echangeur_cond); //arrivé initiale dans l'échangeur X
    //sleep(1);

    while(current->position!=current->destination){

	exit_interchange(current,current_mutex,echangeur_cond); //on attend l'autorisation, puis on passe dans l'echangeur
//    enter_interchange(current,current_mutex,echangeur_cond); //arrivé initiale dans l'échangeur X

    }

    deleteVehicule(current);
    pthread_exit(NULL);
}

void enter_interchange(vehicule* current,pthread_mutex_t* mutex,pthread_cond_t* condition){ //fonction d'arrivé dans un échangeur

	fprintf(stderr,"\nJe suis %ld, je veux rentrer dans l'échangeur %d.(A)\n",pthread_self(),current->num_curr_echangeur);
	
	file_Attente* pfile_attente = NULL;
	pfile_attente = &(Echangeur_id[current->num_curr_echangeur].file_attente[current->position]);
	pthread_cond_t* tmp;
	switch(current->num_curr_echangeur){
		case 0:
			switch(current->position){
				case 0:
					tmp = &ech0_fileN;
					break;
 				case 1:
					tmp = &ech0_fileE;
					break;
 				case 2:
					tmp = &ech0_fileS;
					break;
 				case 3:
					tmp = &ech0_fileO;
					break;
				default:
					tmp = NULL;
					break;
			}
			break;
		case 1:
			switch(current->position){
				case 0:
					tmp = &ech1_fileN;
					break;
 				case 1:
					tmp = &ech1_fileE;
					break;
 				case 2:
					tmp = &ech1_fileS;
					break;
 				case 3:
					tmp = &ech1_fileO;
					break;
				default:
					tmp = NULL;
					break;
			}
			break;
		case 2:
			switch(current->position){
				case 0:
					tmp = &ech2_fileN;
					break;
 				case 1:
					tmp = &ech2_fileE;
					break;
 				case 2:
					tmp = &ech2_fileS;
					break;
 				case 3:
					tmp = &ech2_fileO;
					break;
				default:
					tmp = NULL;
					break;
			}
			break;
		case 3:
			switch(current->position){
				case 0:
					tmp = &ech3_fileN;
					break;
 				case 1:
					tmp = &ech3_fileE;
					break;
 				case 2:
					tmp = &ech3_fileS;
					break;
 				case 3:
					tmp = &ech3_fileO;
					break;
				default:
					tmp = NULL;
					break;
			}
			break;
		default:
			tmp = NULL;
			break;
		tmp = NULL;
	}//
	//test si il reste de la place dans la liste d'attente
	//pthread_cond_wait(fileAttente);
	if(pfile_attente->nbAttente==10)pthread_cond_wait(tmp,mutex);
	
	pthread_mutex_lock(mutex);
	fprintf(stderr,"\nJe suis %ld, je rentre dans l'échangeur %d.(R)\n",pthread_self(),current->num_curr_echangeur);
	//entré dans la liste avec la fonction adéquate
	//
	

	
	ajouter_liste(pfile_attente,current); 


	pthread_cond_signal (condition); //signal a l'echangeur qu'un nouveau vehicule est present
	pthread_mutex_unlock(mutex);

	return tmp;

}

void exit_interchange(vehicule* current,pthread_mutex_t* mutex,pthread_cond_t* condition){ //fonction de sortie d'un échangeur

	pthread_mutex_lock(mutex);
        pthread_cond_wait(condition,mutex);

	file_Attente* pfile_attente = NULL;
	pfile_attente = &(Echangeur_id[current->num_curr_echangeur].file_attente[current->position]);
	pthread_cond_t* tmp;
	switch(current->num_curr_echangeur){
		case 0:
			switch(current->position){
				case 0:
					tmp = &ech0_fileN;
					break;
 				case 1:
					tmp = &ech0_fileE;
					break;
 				case 2:
					tmp = &ech0_fileS;
					break;
 				case 3:
					tmp = &ech0_fileO;
					break;
				default:
					tmp = NULL;
					break;
			}
			break;
		case 1:
			switch(current->position){
				case 0:
					tmp = &ech1_fileN;
					break;
 				case 1:
					tmp = &ech1_fileE;
					break;
 				case 2:
					tmp = &ech1_fileS;
					break;
 				case 3:
					tmp = &ech1_fileO;
					break;
				default:
					tmp = NULL;
					break;
			}
			break;
		case 2:
			switch(current->position){
				case 0:
					tmp = &ech2_fileN;
					break;
 				case 1:
					tmp = &ech2_fileE;
					break;
 				case 2:
					tmp = &ech2_fileS;
					break;
 				case 3:
					tmp = &ech2_fileO;
					break;
				default:
					tmp = NULL;
					break;
			}
			break;
		case 3:
			switch(current->position){
				case 0:
					tmp = &ech3_fileN;
					break;
 				case 1:
					tmp = &ech3_fileE;
					break;
 				case 2:
					tmp = &ech3_fileS;
					break;
 				case 3:
					tmp = &ech3_fileO;
					break;
				default:
					tmp = NULL;
					break;
			}
			break;
		default:
			tmp = NULL;
			break;
		tmp = NULL;
	}



	fprintf(stderr,"\nJe suis %ld, je sors de l'échangeur X.(S)\n",pthread_self());
	//sortie avec la fonction adéquate
	sortir_liste(pfile_attente);
	sleep(1);
	pthread_mutex_unlock(mutex);

}

file_Attente* determine_liste(int numFile){

	file_Attente* liste;

	switch(numFile){

		case 0:
			liste = &(Echangeur_id[0].file_attente[0]);
			break;
		case 1: 
			liste = &(Echangeur_id[0].file_attente[1]);
			break;
		case 2: 
			liste = &(Echangeur_id[1].file_attente[1]);
			break;
		case 3:
			liste = &(Echangeur_id[1].file_attente[2]);
			break;
		case 4:
			liste = &(Echangeur_id[2].file_attente[2]);
			break;
		case 5:  
			liste = &(Echangeur_id[2].file_attente[3]);
			break;
		case 6: 
			liste = &(Echangeur_id[3].file_attente[3]);
			break;
		case 7:
			liste = &(Echangeur_id[3].file_attente[0]);
			break;
		case 8:
			liste = &(Echangeur_id[0].file_attente[3]);
			break;
		case 9:
			liste = &(Echangeur_id[0].file_attente[2]);
			break;
		case 10:
			liste = &(Echangeur_id[1].file_attente[0]);
			break;
		case 11:
			liste = &(Echangeur_id[1].file_attente[3]);
			break;
		case 12:
			liste = &(Echangeur_id[2].file_attente[1]);
			break;
		case 13:
			liste = &(Echangeur_id[2].file_attente[0]);
			break;
		case 14:
			liste = &(Echangeur_id[3].file_attente[2]);
			break;
		case 15:
			liste = &(Echangeur_id[3].file_attente[1]);
			break;
		default:
			printf("Le numéro de file n'est pas bon");
			liste = NULL;
			break;
	 }
	return liste;


}

void cleanMemory(){ //fonction qui ferme tout correctement et vide la mémoire
/*
	for(int i=0;i<NUM_VEHICULES;++i){
		deleteVehicule(&Vthread_id[i]);
	}
	exit(2);
CA NE MARCHE PAS POUR LE MOMENT */
}

//MAIN FUNCTION

int main(void)
{

    int i;

    // SIGNAUX
    
  //  signal(SIGINT,cleanMemory);
  //  signal(SIGTSTP,cleanMemory);
	
	//INTERCHANGE
    fprintf(stderr,"\nCréation des échangeurs\n");

    for (i = 0; i < NUM_INTERCHANGE; i++) {
	init_echangeur(&Echangeur_id[i],i);
  }

    fprintf(stderr,"\nInitialisation des threads\n");
	//THREAD INIT
	pthread_attr_t thread_attr;

  if (pthread_attr_init (&thread_attr) != 0) {
    fprintf (stderr, "pthread_attr_init error");
    exit (1);
  }

  if (pthread_attr_setdetachstate (&thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
    fprintf (stderr, "pthread_attr_setdetachstate error");

    exit (1);
  }
	//THREAD CREATION
	
	    	//INTERCHANGES
	pthread_t Rthread_id[NUM_INTERCHANGE];
	
        fprintf(stderr,"\nthreads d'échangeur\n");
    for (i = 0; i < NUM_INTERCHANGE; i++) {

	if (pthread_create (&Rthread_id[i], &thread_attr,threadEchangeur ,(void*)i) < 0) {
		fprintf (stderr, "pthread_create error for thread \n");
		exit (1);
	}
	 
    }	
    	    	//VEHICLES
        fprintf(stderr,"\nCréation des threads\n");
	pthread_t Vthread_id[NUM_VEHICLES];
	
        fprintf(stderr,"\nthreads de véhicule\n");
    for (i = 0; i < NUM_VEHICLES; i++) {

	if (pthread_create (&Vthread_id[i], &thread_attr,threadVehicule ,(void*)i) < 0) {
		fprintf (stderr, "pthread_create error for thread \n");
		exit (1);
	}
	 
    }	    	 

    for(i=0;i<NUM_VEHICLES;++i){
	    pthread_join(Vthread_id[i],NULL);
    }
	pthread_exit(NULL);
}
