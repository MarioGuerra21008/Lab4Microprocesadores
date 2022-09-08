/*
* Universidad del Valle de Guatemala
* Programación de Microprocesadores - Sección: 20
* Mario Antonio Guerra Morales - Carné: 21008
* Ejercicio2_Lab4.cpp
* Programa que produce café en zona 17 capitalina.
*/

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <cstdint>
#include <sstream>
#include <fstream>

using namespace std;

pthread_mutex_t lock;
int contador;

struct monitoreoCafe{
    int cafeTostadora = 0;
    int cafeSilo = 0;
    int cafeBodega = 0;
};

void *tostadora1(void *bolsasCafe){
    monitoreoCafe *estructCafe = (monitoreoCafe*) bolsasCafe;
    pthread_mutex_lock(&lock);
    cout<<"Tostadora 1 produjo: 1 lb de cafe tostada"<<endl;
    estructCafe->cafeTostadora += 1;
    pthread_mutex_unlock(&lock);
    pthread_mutex_destroy(&lock);
    return NULL;
}

void *tostadora2(void *bolsasCafe){
    monitoreoCafe *estructCafe = (monitoreoCafe*) bolsasCafe;
    pthread_mutex_lock(&lock);
    cout<<"Tostadora 2 produjo: 1 lb de cafe tostada"<<endl;
    estructCafe->cafeTostadora += 1;
    pthread_mutex_unlock(&lock);
    pthread_mutex_destroy(&lock);
    return NULL;
}

void *empacadora(void *bolsasCafe){
    monitoreoCafe *estructCafe = (monitoreoCafe*) bolsasCafe;
    pthread_mutex_lock(&lock);
    cout<<"Empacadora produjo: 1 bolsa de 1 lb de cafe"<<endl;
    estructCafe->cafeBodega += 1;
    cout<<"Lbs de cafe en bodega: "<<estructCafe->cafeBodega<<endl;
    pthread_mutex_unlock(&lock);
    pthread_mutex_destroy(&lock);
    return NULL;
}

int main() {
    double creador;
    bool totalCafe = false;
    monitoreoCafe plantaCafe;
    pthread_t tid[2];
    pthread_attr_t attr;
    cout<<"Iniciando producción de café."<<endl;

    while(totalCafe==false){
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
        creador = pthread_create(&tid[0],&attr,tostadora2,(void *)&plantaCafe);
        creador = pthread_join(tid[0],NULL);
        if(plantaCafe.cafeBodega == 395){
            plantaCafe.cafeTostadora -= 4;
            plantaCafe.cafeBodega = 399;
            totalCafe = true;
        }
        if((plantaCafe.cafeTostadora % 5 == 0)||(plantaCafe.cafeTostadora== 5)){
            plantaCafe.cafeTostadora -= 1;
            cout<<"Lbs de cafe en silo: "<<plantaCafe.cafeTostadora<<endl;
            creador = pthread_create(&tid[2],&attr,empacadora,(void *)&plantaCafe);
            creador = pthread_join(tid[2],NULL);
        }
        creador = pthread_create(&tid[1],&attr,tostadora1,(void *)&plantaCafe);
        creador = pthread_join(tid[1],NULL);
        sleep(1);
        if(plantaCafe.cafeBodega == 395){
            plantaCafe.cafeTostadora -= 4;
            plantaCafe.cafeBodega = 400;
            totalCafe = true;
        }
        if((plantaCafe.cafeTostadora % 5 == 0)||(plantaCafe.cafeTostadora== 5)){
            plantaCafe.cafeTostadora -=1;
            cout<<"Lbs de cafe en silo: "<<plantaCafe.cafeTostadora<<endl;
            creador = pthread_create(&tid[2],&attr,empacadora,(void *)&plantaCafe);
            creador = pthread_join(tid[2],NULL);
        }
    }

    cout<<"Lbs de cafe en silo: 0"<<endl;
    cout<<"Lbs de cafe en bodega: 400"<<endl;
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);

    return 0;
}
