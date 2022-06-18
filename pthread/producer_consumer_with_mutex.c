#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define TOTAL_ELEMENTS 10

int bucket[1] = {-100}; // bucket can hold only a single item
int bucketFull = 0;

pthread_mutex_t mutex;

void *producer(void *arg){
    int *ary = (int*) arg; 
    int index = 0;
    int addedToBucket;

    printf("about to start producer bucket\n");
    while (index < TOTAL_ELEMENTS/2)
    {
        addedToBucket = 0;
        int value = ary[index++];
        while (addedToBucket == 0)
        {
            pthread_mutex_lock(&mutex);
            if(bucketFull == 0) {
                bucket[0] = value; // add to bucket
                bucketFull = 1;
                addedToBucket = 1;
                printf("producer --> added value: %d\n", value);
            }
            pthread_mutex_unlock(&mutex);
        }  
    }
}

void *consumer() {
    int extractedFromBucket = 0;
    int index = 0;
    int extractedValue;

 printf("about to start consumer bucket\n");
     while (index < TOTAL_ELEMENTS) {

         extractedFromBucket = 0;

        while (extractedFromBucket == 0)
        {
            pthread_mutex_lock(&mutex);
            if(bucketFull == 1) {
                extractedValue = bucket[0];
                bucketFull = 0;
                extractedFromBucket = 1;
                index++;
            }
            pthread_mutex_unlock(&mutex);
        }

         printf("consumer --> square value: %d\n", extractedValue * extractedValue);
     }

}

int main() {

    int producer1DataSet[5] = {1,2,3,4,5};
    int producer2DataSet[5] = {6,7,8,9,10};

    pthread_t threadProducer, threadProducer2, threadConsumer;   
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&threadProducer, &attr, producer, (void *)producer1DataSet);
    pthread_create(&threadProducer2, &attr, producer, (void *)producer2DataSet);
    pthread_create(&threadConsumer, &attr, consumer, NULL);

    pthread_join(threadProducer, NULL);
    pthread_join(threadConsumer, NULL);
    pthread_join(threadProducer2, NULL);

    return 0;
}