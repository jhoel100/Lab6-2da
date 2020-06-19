//g++ orden.cpp -std=c++11 -lpthread -o orden.out
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <chrono>
#include <time.h>
#include <bits/stdc++.h>
#include <fstream>
#include <thread>

using namespace std;

int contador;

void imprimir(int arreglo[],int longitud){
	for(int i=0;i<longitud;i++){
		cout<<arreglo[i]<<" ";
	}
	cout<<endl;
}

//Algoritmo Maximo
int maximo(int arreglo[],int longitud,int& cont){
	int m=arreglo[0];
	for(int i=1;i<longitud;i++){
		if(arreglo[i]>m){
			m=arreglo[i];
			cont++;
		}
	}

	return m;
}

int main(){

	 int NUM_PUNTOS=13;

    // X, Y valores de los puntos a graficar
	 double * valoresX;
	 valoresX = new double [NUM_PUNTOS];
	 double * valoresY;
	 valoresY = new double [NUM_PUNTOS];
	 double * valoresY2;
	 valoresY2 = new double [NUM_PUNTOS];

	 int total=200; // pidio 200

	 double * registrados;
	 registrados = new double [total];

	 srand(time_t());
	 contador=0;

	 int maxval;
	 double prom;

	 for(int n=0;n<NUM_PUNTOS;n++){
		 double longitud = pow(2,(n+8));

		 valoresX[n] =longitud;
		 
	    int * arr;
		 arr = new int[(int)longitud];

		 prom=0;
		 for(int j=0;j<total;j++){
			 for(int i=1;i<=longitud;i++){
				arr[i-1]=1 + rand() % ( (int)longitud - 1);
			 }
			 maxval=maximo(arr,(int)longitud,contador);
			 registrados[j] =contador;
			 contador=0;
			 prom=prom+registrados[j];
		 }	  	 
		 prom=prom/total;
		 valoresY[n] =prom;
		 prom=0;

		 valoresY2[n]=n+9; // Estos es Log(n)+1, porque definimos n como 2exp(longitud+8)
		 delete [] arr;
	 }
	 
	 //Lee el archivo puntosGraficar par aguardar los valores
    FILE * archivoPuntos = fopen("Maximo.txt", "w");
    FILE * archivoPuntos2 = fopen("Log(n)+1.txt", "w");
    FILE * archivoPuntos3 = fopen("Cuadro1.txt", "w");
	
    for (int i=0;i<NUM_PUNTOS;i++){
 		 fprintf(archivoPuntos, "%lf %lf \n", valoresX[i], valoresY[i]);
 	 }
	 
    for (int i=0;i<NUM_PUNTOS;i++){
 		 fprintf(archivoPuntos2, "%lf %lf \n", valoresX[i], valoresY2[i]);
 	 }

    for (int i=0;i<NUM_PUNTOS;i++){
 		 fprintf(archivoPuntos3, "%lf %lf %lf \n", valoresX[i], valoresY[i],valoresY2[i]);
 	 }


    fclose(archivoPuntos);
    fclose(archivoPuntos2);
    fclose(archivoPuntos3);

	 delete [] valoresX;
	 delete [] valoresY;
	 delete [] valoresY2;
	 delete [] registrados;

   return 0;

}
