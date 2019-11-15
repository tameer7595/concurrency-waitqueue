//
// Created by tameer on 11/13/19.
//

#ifndef PRODUCERWITHQUEUE_QUEUE_H
#define PRODUCERWITHQUEUE_QUEUE_H

#include <iostream>
#include <queue>
pthread_cond_t push_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t pop_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
template<class T>
class Queue{
public:
    Queue(int capacity):m_capacity(capacity){}
    T pop(){
        //std::cout<<"starting pop lock "<<std::endl;
        pthread_mutex_lock(&lock);
        //std::cout<<"ended pop lock "<<std::endl;
        while(m_arr.empty()) {
            std::cout << "wait for push"<<std::endl;
            pthread_cond_wait(&push_cond, &lock);
            std::cout << "wake up from pop"<<std::endl;
        }
        T element = m_arr.front();
        m_arr.pop();

        pthread_cond_signal(&pop_cond);
        pthread_mutex_unlock(&lock);
        return element;

    }

    void push(T elem){
        //std::cout<<"starting push lock"<<std::endl;
        pthread_mutex_lock(&lock);
        //std::cout<<"ended push lock"<<std::endl;

        while(m_capacity == m_arr.size()) {
            std::cout << "wait for pop"<<std::endl;
            pthread_cond_wait(&pop_cond, &lock);
            std::cout << "wake up from push"<<std::endl;

        }
        m_arr.push(elem);
        pthread_cond_signal(&push_cond);
        pthread_mutex_unlock(&lock);
    }


private:
    int m_capacity;
    std::queue<T> m_arr;
};

#endif //PRODUCERWITHQUEUE_QUEUE_H
