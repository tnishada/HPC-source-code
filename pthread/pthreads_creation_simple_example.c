#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function( void *ptr );

int main()
{
     pthread_t thread1, thread2;
     int message1 = 123;
     int message2 = 456;
     
     pthread_attr_t attr;

    pthread_attr_init(&attr);

    /* Create independent threads, each of it will execute function */
     pthread_create( &thread1, &attr, print_message_function, (void *)&message1);
     pthread_create( &thread2, &attr, print_message_function, (void *)&message2);

     /* Wait till threads are complete before the main thread continues.   */
     /* Unless we run the risk of executing an exit. which will terminate ->  */
     /* the process and all threads before the threads have completed.     */

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 

     return 0;
}

void *print_message_function( void * ptr )
{
     int *message;
     message = (int* ) ptr;
     printf("%d \n", *message);
}