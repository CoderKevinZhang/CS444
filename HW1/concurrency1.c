/**********************************
 * Name: Nikhil Kishore
 * Class: CS444
 * Assignment #1
 * Date: 4/11/16
************************************/




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "mt19937ar.c"


#define MAX 32       
pthread_mutex_t control;
pthread_cond_t conditionalCons, conditionalProd;

struct passData{
	int value;
	int wait;
};	

struct passData buffer[MAX];
int bufferLength = 0;

void* consumer(void *ptr) {
	int i;
	while(1){
	  	   pthread_mutex_lock(&control);
		   while (bufferLength <= 0){
	      		printf("Waiting for producer... \n");
			pthread_cond_wait(&conditionalCons, &control);
		   }
		   pthread_mutex_unlock(&control);	
		   sleep(buffer[bufferLength-1].wait);

		   pthread_mutex_lock(&control); 
		   printf("Consumer: Consumed item with value %d, Buffer at %d\n", buffer[bufferLength-1].value, bufferLength-1);
		   bufferLength--;
		   pthread_cond_signal(&conditionalProd);
		   pthread_mutex_unlock(&control); 
	}
	pthread_exit(0);
}

void* producer(void *ptr) {
	int i;
	int wait;  
	while(1) {
		   wait = (genrand_int32() % 5) + 3;
		   sleep(wait);
		   pthread_mutex_lock(&control);
		   while(bufferLength == (MAX)){
			      printf("Waiting for consumer... \n");
			      pthread_cond_wait(&conditionalProd, &control);	
		   }	
		   buffer[bufferLength].wait = (genrand_int32() % 8) + 2; 
		   buffer[bufferLength].value = genrand_int32() % 100; 
		   bufferLength++;
		   printf("Producer: Produced item with value %d. Buffer at %d \n", buffer[bufferLength-1].value, bufferLength);
		   pthread_cond_signal(&conditionalCons); 
		   pthread_mutex_unlock(&control); 
	}
	pthread_exit(0);
}

int main(int argc, char **argv) {
	pthread_t produce, consume;
	init_genrand(time(NULL));

	pthread_mutex_init(&control, NULL);
	pthread_cond_init(&conditionalCons, NULL); 
	pthread_cond_init(&conditionalProd, NULL); 

	pthread_create(&consume, NULL, consumer, NULL);
	pthread_create(&produce, NULL, producer, NULL);

	pthread_join(consume, NULL);
	pthread_join(produce, NULL);

	pthread_mutex_destroy(&control); 
	pthread_cond_destroy(&conditionalCons); 
	pthread_cond_destroy(&conditionalProd); 
}
