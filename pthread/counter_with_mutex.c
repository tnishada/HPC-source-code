#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *print_message_function( void *ptr );
int counter = 0;
pthread_mutex_t counter_lock;
int main()
{
     int threadCount = 20;
     pthread_t threadAry[threadCount];   
     pthread_attr_t attr;

    pthread_mutex_init(&counter_lock, NULL);
    pthread_attr_init(&attr);

    int k; // used to iterate loops
    for(k = 0 ; k < threadCount; k++) {
        pthread_create( &threadAry[k], &attr, print_message_function, NULL);
    }

     for(k = 0 ; k < threadCount; k++) {
        pthread_join( threadAry[k], NULL);
    }

    printf("counter = %d\n",counter);

     return 0;
}

void *print_message_function( void * ptr )
{
     int index ;
    for(index = 0 ; index < 10000; index++) {
        pthread_mutex_lock(&counter_lock);
        counter = counter + 1;
        pthread_mutex_unlock(&counter_lock);
    }
}

