/*
* Universidad del Valle de Guatemala
* Programación de Microprocesadores - Sección: 20
* Mario Antonio Guerra Morales - Carné: 21008
* Ejercicio1_Lab4.cpp
* Programa que permita verificar si se generan utilidades en &Café
*/

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <cstdint>
using namespace std;

struct arrayDatos{
    std::string producto;
    double precioUnitario;
    double costoFijo;
    double unidadesVendidas;
};

void *calculosMes(void *numeros){
    long tid;
    tid = (long)numeros;
    arrayDatos arrayInfo[16];
    double ventasJ;
    double ventasA;
    double utilidadJ;
    double utilidadA;
    double ventasMesJ;
    double ventasMesA;
    double utilidadTJ;
    double utilidadTA;
    double costosVarJ = 45640;
    double costosVarA = 40590;
    double utilidadMesJ;
    double utilidadMesA;
    
    arrayInfo[0] = {"Pastel de Chocolate", 60.00, 20.00, 300};
    arrayInfo[1] = {"White Mocha", 32.00, 19.20, 400};
    arrayInfo[2] = {"Café Americano", 22.00, 13.20, 1590};
    arrayInfo[3] = {"Latte", 24.00, 17.20, 200};
    arrayInfo[4] = {"Toffee Coffee", 28.00, 20.10, 390};
    arrayInfo[5] = {"Cappuccino", 24.00, 17.20, 1455};
    arrayInfo[6] = {"S'mores Latte", 32.00, 23.00, 800};
    arrayInfo[7] = {"Café Tostado Molido", 60.00, 20.00, 60};
    arrayInfo[8] = {"Pastel de Chocolate", 60.00, 20.00, 250};
    arrayInfo[9] = {"White Mocha", 32.00, 19.20, 380};
    arrayInfo[10] = {"Café Americano", 22.00, 13.20, 800};
    arrayInfo[11] = {"Latte", 24.00, 17.20, 250};
    arrayInfo[12] = {"Toffee Coffee", 28.00, 20.10, 600};
    arrayInfo[13] = {"Cappuccino", 24.00, 17.20, 1200};
    arrayInfo[14] = {"S'mores Latte", 32.00, 23.00, 1540};
    arrayInfo[15] = {"Café Tostado Molido", 60.00, 20.00, 15};
    
    cout<<"Reporte del mes: Julio"<<endl;
    cout<<"Ventas por producto: "<<endl;
    for(int i=0;i<8;i++){
        ventasJ = arrayInfo[i].unidadesVendidas * arrayInfo[i].precioUnitario;
        cout<<arrayInfo[i].producto<<": Q"<<ventasJ<<endl;
    }
    cout<<"\n";
    cout<<"Utilidad por producto: "<<endl;
    for(int i=0; i<8;i++){
        ventasJ = arrayInfo[i].unidadesVendidas * arrayInfo[i].precioUnitario;
        utilidadJ = ventasJ - (arrayInfo[i].unidadesVendidas * arrayInfo[i].costoFijo);
        cout<<arrayInfo[i].producto<<": Q"<<utilidadJ<<endl;
        ventasMesJ += ventasJ;
        utilidadTJ += utilidadJ;
        if(i==7){
        cout<<"\n";
            utilidadMesJ = utilidadTJ - costosVarJ;
            cout<<"Total ventas: Q"<<ventasMesJ<<endl;
            cout<<"Costos variables: Q"<<costosVarJ<<endl;
            cout<<"Utilidad del mes: Q"<<utilidadMesJ<<endl;
        }
    }
    cout<<"\n";
    cout<<"Reporte del mes: Agosto"<<endl;
    cout<<"Ventas por producto: "<<endl;
    for(int i=8;i<16;i++){
        ventasA = arrayInfo[i].unidadesVendidas * arrayInfo[i].precioUnitario;
        cout<<arrayInfo[i].producto<<": Q"<<ventasA<<endl;
    }
    cout<<"\n";
    cout<<"Utilidad por producto: "<<endl;
    for(int i=8; i<16;i++){
        ventasA = arrayInfo[i].unidadesVendidas * arrayInfo[i].precioUnitario;
        utilidadA = ventasA - (arrayInfo[i].unidadesVendidas * arrayInfo[i].costoFijo);
        cout<<arrayInfo[i].producto<<": Q"<<utilidadA<<endl;
        ventasMesA += ventasA;
        utilidadTA += utilidadA;
        if(i==15){
        cout<<"\n";
            utilidadMesA = utilidadTA - costosVarA;
            cout<<"Total ventas: Q"<<ventasMesA<<endl;
            cout<<"Costos variables: Q"<<costosVarA<<endl;
            cout<<"Utilidad del mes: Q"<<utilidadMesA<<endl;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    pthread_attr_t attr;
    arrayDatos arrayInfo[16];
    double ventasJ;
    double ventasA;
    double utilidadJ;
    double utilidadA;
    double ventasMesJ;
    double ventasMesA;
    double costosVarJ = 45640;
    double costosVarA= 40590;
    double utilidadMesJ;
    double utilidadMesA;

    pthread_create(&tid, NULL, calculosMes, (void*)NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    pthread_join(tid,NULL);
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
}
