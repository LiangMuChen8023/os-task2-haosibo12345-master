<<<<<<< HEAD
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

// 定义信号量
sem_t sem_f, sem_h, sem_i;

void* thread_f(void* arg) {
    for (int i = 0; i < 10; i++) {
        printf("f");
        computation();
    }
    sem_post(&sem_h);  // 释放h的信号量
    return NULL;
}

void* thread_h(void* arg) {
    sem_wait(&sem_h);  // 等待f完成
    for (int i = 0; i < 10; i++) {
        printf("h");
        computation();
    }
    sem_post(&sem_i);  // 释放i的信号量
    return NULL;
}

void* thread_i(void* arg) {
    sem_wait(&sem_i);  // 等待h完成
    for (int i = 0; i < 10; i++) {
        printf("i");
        computation();
    }
    return NULL;
}

void* thread_b(void* arg) {
    for (int i = 0; i < 10; i++) {
        printf("b");
        computation();
    }
    return NULL;
}

void* thread_c(void* arg) {
    for (int i = 0; i < 10; i++) {
        printf("c");
        computation();
    }
    return NULL;
}

void* thread_d(void* arg) {
    for (int i = 0; i < 10; i++) {
        printf("d");
        computation();
    }
    return NULL;
}

void* thread_k(void* arg) {
    for (int i = 0; i < 10; i++) {
        printf("k");
        computation();
    }
    return NULL;
}

int lab2_init() {
    // 初始化信号量
    sem_init(&sem_f, 0, 1);
    sem_init(&sem_h, 0, 0);  // h等待f
    sem_init(&sem_i, 0, 0);  // i等待h

    pthread_t threads[7];
    pthread_create(&threads[0], NULL, thread_f, NULL);  // f
    pthread_create(&threads[1], NULL, thread_h, NULL);  // h
    pthread_create(&threads[2], NULL, thread_i, NULL);  // i
    pthread_create(&threads[3], NULL, thread_b, NULL);  // b
    pthread_create(&threads[4], NULL, thread_c, NULL);  // c
    pthread_create(&threads[5], NULL, thread_d, NULL);  // d
    pthread_create(&threads[6], NULL, thread_k, NULL);  // k

    // 等待所有线程结束
    for (int i = 0; i < 7; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem_f);
    sem_destroy(&sem_h);
    sem_destroy(&sem_i);

=======
#include "lab2.h"
#include <iostream>
#include <cstring>
#include <pthread.h>
#include <semaphore.h>

#define NUMBER_OF_THREADS 10

// thread identifiers
pthread_t tid[NUMBER_OF_THREADS];
// critical section lock
pthread_mutex_t lock;
// semaphores for sequential threads
sem_t semE, semF, semG, semH, semI, semK;

int err;

unsigned int lab2_thread_graph_id() 
{
    return 999;
}

const char* lab2_unsynchronized_threads()
{
    return "bcd";
}

const char* lab2_sequential_threads()
{
    return "fhi";
}

void *thread_a(void *ptr);
void *thread_b(void *ptr);
void *thread_c(void *ptr);
void *thread_d(void *ptr);
void *thread_e(void *ptr);
void *thread_f(void *ptr);
void *thread_g(void *ptr);
void *thread_h(void *ptr);
void *thread_i(void *ptr);
void *thread_k(void *ptr);

void *thread_a(void *ptr)
{
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "a" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    return ptr;
}

void *thread_b(void *ptr)
{
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "b" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    return ptr;
}

void *thread_c(void *ptr)
{
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "c" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    return ptr;
}

void *thread_d(void *ptr)
{
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "d" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    return ptr;
}

void *thread_e(void *ptr)
{
    sem_wait(&semE);
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "e" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    sem_post(&semF);
    return ptr;
}

void *thread_f(void *ptr)
{
    sem_wait(&semF);
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "f" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    sem_post(&semG);
    return ptr;
}

void *thread_g(void *ptr)
{
    sem_wait(&semG);
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "g" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    sem_post(&semH);
    return ptr;
}

void *thread_h(void *ptr)
{
    sem_wait(&semH);
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "h" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    sem_post(&semI);
    return ptr;
}

void *thread_i(void *ptr)
{
    sem_wait(&semI);
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "i" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    sem_post(&semK);
    return ptr;
}

void *thread_k(void *ptr)
{
    sem_wait(&semK);
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "k" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    return ptr;
}

int lab2_init()
{
    // initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        std::cerr << "Mutex init failed" << std::endl;
        return 1;
    }
    // initialize semaphores
    if (sem_init(&semE, 0, 0) != 0 || 
        sem_init(&semF, 0, 0) != 0 ||
        sem_init(&semG, 0, 0) != 0 ||
        sem_init(&semH, 0, 0) != 0 ||
        sem_init(&semI, 0, 0) != 0 ||
        sem_init(&semK, 0, 0) != 0) {
        std::cerr << "Semaphore init failed" << std::endl;
        return 1;
    }

    // start threads a, b, c
    err = pthread_create(&tid[0], NULL, thread_a, NULL);
    if (err != 0) std::cerr << "Can't create thread a. Error: " << strerror(err) << std::endl;
    err = pthread_create(&tid[1], NULL, thread_b, NULL);
    if (err != 0) std::cerr << "Can't create thread b. Error: " << strerror(err) << std::endl;
    err = pthread_create(&tid[2], NULL, thread_c, NULL);
    if (err != 0) std::cerr << "Can't create thread c. Error: " << strerror(err) << std::endl;

    // wait for thread a to finish
    pthread_join(tid[0], NULL);

    // start thread d
    err = pthread_create(&tid[3], NULL, thread_d, NULL);
    if (err != 0) std::cerr << "Can't create thread d. Error: " << strerror(err) << std::endl;

    // wait for threads b, d to finish
    pthread_join(tid[1], NULL);
    pthread_join(tid[3], NULL);

    // start thread e
    sem_post(&semE);
    err = pthread_create(&tid[4], NULL, thread_e, NULL);
    if (err != 0) std::cerr << "Can't create thread e. Error: " << strerror(err) << std::endl;

    // wait for thread c to finish
    pthread_join(tid[2], NULL);

    // wait for thread e to finish
    pthread_join(tid[4], NULL);

    // start threads f, h, i
    sem_post(&semF);
    err = pthread_create(&tid[5], NULL, thread_f, NULL);
    if (err != 0) std::cerr << "Can't create thread f. Error: " << strerror(err) << std::endl;
    err = pthread_create(&tid[6], NULL, thread_h, NULL);
    if (err != 0) std::cerr << "Can't create thread h. Error: " << strerror(err) << std::endl;
    err = pthread_create(&tid[7], NULL, thread_i, NULL);
    if (err != 0) std::cerr << "Can't create thread i. Error: " << strerror(err) << std::endl;

    // wait for thread f to finish
    pthread_join(tid[5], NULL);

    // start thread g
    sem_post(&semG);
    err = pthread_create(&tid[8], NULL, thread_g, NULL);
    if (err != 0) std::cerr << "Can't create thread g. Error: " << strerror(err) << std::endl;

    // wait for threads h, g to finish
    pthread_join(tid[6], NULL);
    pthread_join(tid[8], NULL);

    // start thread k
    sem_post(&semK);
    err = pthread_create(&tid[9], NULL, thread_k, NULL);
    if (err != 0) std::cerr << "Can't create thread k. Error: " << strerror(err) << std::endl;

    // wait for threads i, k to finish
    pthread_join(tid[7], NULL);
    pthread_join(tid[9], NULL);

    // destroy mutex and semaphores
    pthread_mutex_destroy(&lock);
    sem_destroy(&semE);
    sem_destroy(&semF);
    sem_destroy(&semG);
    sem_destroy(&semH);
    sem_destroy(&semI);
    sem_destroy(&semK);
    std::cout << std::endl;
>>>>>>> 8f44d2bb42e9d468ceebc754d1b244bbb297b91b
    return 0;

}

