#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include "queue.h"

using namespace std;

static const int  NUM_PRODUCER_THREADS =  3;
static const int  NUM_CONSUMER_THREADS =  4;



Queue<int> box(6);


pthread_t threads_producer[NUM_PRODUCER_THREADS];
pthread_t threads_consumer[NUM_CONSUMER_THREADS];


static int r = 0;

void *Produce(void *threadid) {

    long tid;
    tid = (long)threadid;
    int i=0;
    while( i < 400){
            //int r = rand() % 1000000 + 1;
            box.push(r);
            ++r;
            std::cout << "producer # " << tid << " ,product #" << r << std::endl;
            i++;
    }
    pthread_exit(NULL);
}

void *Consumer(void *threadid) {

    long tid;
    tid = (long)threadid;
    int i=0 ;
    while( i < 300 ){
        int p = box.pop();
        std::cout << "consumer # " << tid << " ,consume #" << p<< std::endl;
        i++;

    }

    pthread_exit(NULL);
}

void creatingProducers();

void creatingConsumers();

int main () {
    creatingProducers();
    creatingConsumers();

    pthread_exit(NULL);
}
void creatingProducers(){
    int rc,i;
    for( i = 0; i < NUM_PRODUCER_THREADS; i++ ) {
        cout << "main() : creating producer, " << i << endl;
        rc = pthread_create(&threads_producer[i], NULL, Produce, reinterpret_cast<void *>(i));
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
}
void creatingConsumers(){
    int rc,i;
    for( i = 0; i < NUM_CONSUMER_THREADS; i++ ) {
        cout << "main() : creating consumer, " << i << endl;
        rc = pthread_create(&threads_consumer[i], NULL, Consumer, reinterpret_cast<void *>(i));
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
}
//#include <iostream>
//#include <cstdlib>
//#include <pthread.h>
//#include <syscall.h>
//#include "queue.h"
//#include <unistd.h>
//using namespace std;
//Queue<int> waitQueue(6);
//static int to_print = 0;
//void *produce(void *arg)
//{
//    int producers_count = 400;
//    pid_t t_id = syscall(__NR_gettid);
//    while (1)
//    {
//        int randomNumber = (rand() % 600000) + 1;
//        int randomNumber = to_print++;
//        cout << "producing: " << randomNumber << " on: " << t_id << endl;
//        waitQueue.push(randomNumber);
//        producers_count--;
//        if (producers_count == 0)
//        {
//            return NULL;
//        }
//        // enable sleep for less CPU
//        else
//        {
//            usleep(100);
//        }
//    }
//}
//void *consume(void *arg)
//{
//    int consumers_count = 300;
//    pid_t t_id = syscall(__NR_gettid);
//
//    while (1)
//    {
//        int numb = waitQueue.pop();
//        cout << "consuming " << numb << " on: " << t_id << endl;
//        consumers_count--;
//        if (consumers_count == 0)
//        {
//            return NULL;
//        }
//        else
//        {
//            usleep(100);
//        }
//    }
//}
//void solve()
//{
//    int numOfProducers = 3;
//    int numOfConsumers = 4;
//    void *res;
//    pthread_t producers[numOfProducers];
//    pthread_t consumers[numOfConsumers];
//    for (int i = 0; i < numOfProducers; i++)
//    {
//        pthread_create(&producers[i], NULL, produce, NULL);
//    }
//    for (int i = 0; i < numOfConsumers; i++)
//    {
//        pthread_create(&consumers[i], NULL, consume, NULL);
//    }
//    for (int i = 0; i < numOfProducers; i++)
//    {
//        pthread_join(producers[i], &res);
//    }
//    for (int i = 0; i < numOfConsumers; i++)
//    {
//        pthread_join(consumers[i], &res);
//    }
//    pthread_exit(NULL);
//}
//int main()
//{
//    //assert(waitQueue.is_empty());
//    solve();
//    //assert(waitQueue.is_empty());
//    return 0;
//}