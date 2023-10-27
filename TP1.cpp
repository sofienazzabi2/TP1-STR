#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>


void* voiture(void* arg);
void* camion(void* arg);

pthread_mutex_t mutex;
sem_t sem_poids; //init 3



void acquisition_pont(int poids){
	if (poids==15)
		{
		pthread_mutex_lock(&mutex); //bloquer l'accés au pont pour les autres
		sem_wait(&sem_poids);
		sem_wait(&sem_poids);
		sem_wait(&sem_poids);
		pthread_mutex_unlock(&mutex);
		}
	else {
		pthread_mutex_lock(&mutex);
		sem_wait(&sem_poids);
		pthread_mutex_unlock(&mutex);
	}
}

void liberation_pont(int poids){
	if (poids==15){
		sem_post(&sem_poids);
		sem_post(&sem_poids);
	}
	sem_post(&sem_poids);
}


int main(int argc, char* argv[]){
	
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_t t4;
	pthread_t t5;
	pthread_t t6;
	pthread_t t7;
	
	sem_init(&sem_poids,0,3);
	pthread_mutex_init(&mutex, NULL);
	
	pthread_create(&t1, NULL, voiture,(void*) 1);
	pthread_create(&t2, NULL, voiture,(void*) 2);
	pthread_create(&t3, NULL, voiture,(void*) 3);
	pthread_create(&t4, NULL, camion,(void*) 4);
	pthread_create(&t5, NULL, voiture,(void*) 5);
	pthread_create(&t5, NULL, camion,(void*) 6);
	pthread_create(&t5, NULL, voiture,(void*) 7);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);
	pthread_join(t5,NULL);
	pthread_join(t6,NULL);
	pthread_join(t7,NULL);
	
}


void* voiture(void* arg){

	acquisition_pont(5);
	printf("Voiture %d dans le pont\n",*((int*)(&arg)));
	usleep(100000);
	printf("Voiture %d sort du pont\n",*((int*)(&arg)));
	liberation_pont(5);

}


void* camion(void* arg){

	acquisition_pont(15);
	printf("Camion %d dans le pont\n",*((int*)(&arg)));
	usleep(100000);
	printf("Camion %d sort du pont\n",*((int*)(&arg)));
	liberation_pont(15);
}



