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

//QUICK SORT
int Particion(int arreglo[], int inicio, int fin,int& cont)  
{  
	 int pivote=arreglo[fin];
	 int i=inicio-1;

	 int auxiliar;	 

	 for(int j=inicio;j<fin;j++){
			if(arreglo[j]<=pivote){
				i=i+1;
				auxiliar=arreglo[i];
				arreglo[i]=arreglo[j];
				arreglo[j]=auxiliar;
				cont++;
			}
	 }
	 auxiliar=arreglo[i+1];
	 arreglo[i+1]=arreglo[fin];
	 arreglo[fin]=auxiliar;
	 cont++;
	return i+1;
	
}  

void QuickSort(int arreglo[], int inicio, int fin,int& cont) 
{  
	if(inicio<fin){
		int medio=Particion(arreglo,inicio,fin,cont);
		QuickSort(arreglo,inicio,medio-1,cont);
		
		QuickSort(arreglo,medio+1,fin,cont);
	}
}

//MERGE SORT
void Intercala(int arreglo[], int inicio,int medio, int fin){
	vector<int> auxiliar(fin-inicio+1);
	int i;
	int j;
	int k;
	for(i=inicio;i<=medio;i++){
		auxiliar[i-inicio]=arreglo[i];
	}
	for(j=medio+1;j<=fin;j++){
		auxiliar[fin+medio+1-j-inicio]=arreglo[j];
	}
	i=inicio;
	j=fin;
	for(k=inicio;k<=fin;k++){
		if(auxiliar[i-inicio]<=auxiliar[j-inicio]){
			arreglo[k]=auxiliar[i-inicio];
			i=i+1;
		}else{
			arreglo[k]=auxiliar[j-inicio];
			j=j-1;
		}
	}

}

void MergeSort(int arreglo[], int inicio, int fin){
	if(inicio<fin){
		int medio=floor((inicio+fin)/2);
		MergeSort(arreglo,inicio,medio);
		MergeSort(arreglo,medio+1,fin);
		Intercala(arreglo,inicio,medio,fin);
		
	}	

}

//INSERTION SORT
void InsertionSort(int arreglo[],int longitud){
	for(int j=1;j<longitud;j++){
		int clave=arreglo[j];
		int i=j-1;
		while(i>=0 && arreglo[i]>clave){
			arreglo[i+1]=arreglo[i];
			i=i-1;
		}
		arreglo[i+1]=clave;
	}

}

//BUBBLE SORT
void BubbleSort(int arreglo[],int longitud)  
{  
	 int auxiliar;
    for (int i = 0; i < longitud-1; i++){            
	    // Last i elements are already in place  
	    for (int j = 0; j < longitud-i-1; j++){  
	        if (arreglo[j] > arreglo[j+1]){
					 auxiliar=arreglo[j];
					 arreglo[j]=arreglo[j+1];
					 arreglo[j+1]=auxiliar;
				}
		 }
	 }
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

	 int total=10; // pidio 200

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
			 QuickSort(arr,0,longitud,contador);
			 registrados[j] =contador;
			 contador=0;
			 prom=prom+registrados[j];
		 }	  	 
		 prom=prom/total;
		 valoresY[n] =prom;
		 prom=0;

		 valoresY2[n]=pow(2,(n+8))*(n+8); // Estos es Log(n)+1, porque definimos n como 2exp(longitud+8)
		 delete [] arr;
	 }
	 
	 //Lee el archivo puntosGraficar par aguardar los valores
    FILE * archivoPuntos = fopen("QuickSort.txt", "w");
    FILE * archivoPuntos2 = fopen("nLog(n).txt", "w");
    FILE * archivoPuntos3 = fopen("Cuadro2.txt", "w");
	
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
