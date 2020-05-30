#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>
#include <omp.h>

using namespace std;

/**
 * Muestra a los participantes del grupo
 */
void participante();
/**
 * Funcion para obtener el promedio de todos los datos de un arreglo
 * @param arreglo recibe un array con los datos 
 * @param fin recibe el largo del arreglo
 * @return devuelve el promedio del arreglo
 */
double promedio(vector<int> arreglo, int fin);
/**
 * Funcion para obtener la desviación estandar de todos los datos de un arreglo
 * @param arreglo recibe un array con los datos
 * @param fin recibe el largo del arreglo
 * @return devuelve la desviación estandar del arreglo
 */
double desvS(vector<int> arreglo, int fin, double promedio);
/**
 * Funcion para obtener la moda de todos los datos de un arreglo
 * @param arreglo recibe un array con los datos
 * @param fin recibe el largo del arreglo
 * @return devuelve la moda del arreglo
 */
double moda(vector<int> arreglo, int fin);
/**
 * Funcion para obtener la mediana de todos los datos de un arreglo
 * @param arreglo recibe un array con los datos
 * @param fin recibe el largo del arreglo
 * @return devuelve la mediana del arreglo
 */
float mediana(vector<int> arreglo, int fin);
/**
 * Funcion para separar los datos de una linea string separada por ";"
 * @param linea linea con puntajes y rut
 * @return devuelve un array vector con los datos separados de la linea
 */
vector<int> obtenerPuntajes(string linea);
/**
 * Función para ordenar los datos de un arreglo con el metodo de quickSort
 * @param arreglo Arreglo con los datos
 * @param inicio Inicio del arreglo
 * @param fin Fin del arreglo
 */
void quickSort(vector<int> *arreglo, int inicio, int fin);
/**
 * 
 * @param argc Cantidad de argumentos traspasados por consola
 * @param argv Array con argumentos traspasados por consola
 * @return Devuelve el código de error
 */
int main(int argc, char** argv) {
    if(argc > 1){
        string ruta(argv[1]);
        ifstream entrada(ruta);
        if(entrada){
            // Apartado de obtención y clasificación de datos //
            vector<int> nem,ranking,matematica,lenguaje,ciencias,historia;
            vector<vector<int> > datos;
#pragma omp parallel
            {
#pragma omp single
                {
                    for(string linea; getline(entrada, linea);){
#pragma omp task
                        {
                            vector<int> puntajes = obtenerPuntajes(linea);
                            if(!linea.empty()){
#pragma omp critical        
                                {
                                nem.push_back(puntajes.at(1));
                                ranking.push_back(puntajes.at(2));
                                matematica.push_back(puntajes.at(3));
                                lenguaje.push_back(puntajes.at(4));
                                ciencias.push_back(puntajes.at(5));
                                historia.push_back(puntajes.at(6));
                                }
                                
                            }
                            puntajes.clear();
                            
                        }
                    }
                }
            }
            // fin: Apartado de obtención y clasificación de datos //
            // Apartado de cálculo de datos //
            int tamano = nem.size();
            datos.push_back(nem);
            datos.push_back(ranking);
            datos.push_back(matematica);
            datos.push_back(lenguaje);
            datos.push_back(ciencias);
            datos.push_back(historia);

            vector<double> promedios;
            vector<double> desvSs;
            vector<int> modas;
            vector<double> medianas;

            promedios.resize(6);
            desvSs.resize(6);
            modas.resize(6);
            medianas.resize(6);
            // fin: Apartado de cálculo de datos //
            // Apartado de impresión de datos //
            string names[] = {"NEM","RANKING","MATEMATICA","LENGUAJE","CIENCIAS","HISTORIA"};
#pragma omp parallel
            {
#pragma omp for
                for(int i=0;i<6;i++){
                    quickSort(&datos[i],0,tamano-1);
                    promedios[i] = promedio(datos[i],tamano);
                }
            }

#pragma omp parallel
            {
#pragma omp for
                for(int i = 0; i<6; i++){
                    desvSs[i] = desvS(datos[i],tamano,promedios[i]);
                    modas[i]=moda(datos[i],tamano);
                    medianas[i]=mediana(datos[i],tamano);
#pragma omp critical
                    {
                        cout<<endl<<"="<<names[i]<<"="<<endl<<"Promedio: "<<promedios[i]<<endl<<"Desviaci�n Estandar: " <<desvSs[i]<<endl<<"Moda: "<<modas[i]<<endl<<"Mediana: "<<medianas[i]<<endl;
                    }
                }
            }
            // fin: Apartado de impresión de datos //
        }
        else{
            cout<<"Es necesario subir un archivo primero..."<<endl;
            return 1;
        }
    }
    else{
        cout<<"No se ha ingresado la ruta del archivo puntajes..."<<endl;
        return 1;
    }
    
    return 0;
}
// Apartado de funciones //
void participante(){
    cout<<endl<<"==== Participantes ===="<<endl;
    cout<<"Israel Ramirez Cardoso"<<endl;
    cout<<"Humberto Román Matamoros"<<endl;
    cout<<"Victor Araya Romero"<<endl;
}

vector<int> obtenerPuntajes(std::string linea) {
    vector<int> arreglo;
    std::stringstream ss(linea);
    std::string item;

    while (std::getline(ss, item, ';')) {
        int valor = atoi(item.c_str());
        arreglo.push_back(valor);
    }

    return arreglo;
}

void quickSort(vector<int> *arreglo, int inicio,int fin){
    int InicioLocal= inicio, FinLocal=fin;
    float Temp, Pivote;
    if(fin>inicio)
    {
        Pivote= (*arreglo).at((inicio+fin)/2);
        while(InicioLocal<FinLocal)
        {
            while((InicioLocal<fin) && ((*arreglo).at(InicioLocal)<Pivote))  {++InicioLocal;}
            while((FinLocal>inicio) && ((*arreglo).at(FinLocal)>Pivote)) {--FinLocal;}
            if(InicioLocal<=FinLocal)
            {
                Temp=(*arreglo).at(InicioLocal);
                (*arreglo).at(InicioLocal)=(*arreglo).at(FinLocal);
                (*arreglo).at(FinLocal)=Temp;
                ++InicioLocal;
                --FinLocal;
            }
        }
        if(inicio<FinLocal) quickSort(arreglo,inicio,FinLocal);
        if(InicioLocal<fin) quickSort(arreglo,InicioLocal,fin);
    }
}

double promedio(vector<int> arreglo, int fin){
    double suma = 0;
    for(int i=0; i<fin; i++){
        suma += arreglo.at(i);
    }
    return suma/fin;
}
double desvS(vector<int> arreglo, int fin, double promedio){
    double suma = 0;
    for(int i=0; i<fin; i++){
        suma += pow((arreglo.at(i)-promedio),2);
    }
    return sqrt(suma/fin);
}

double moda(vector<int> arreglo, int fin){
    int contador = 0, numero = arreglo.at(0), contadorAux = 0, numeroAux;

    for(int i=0;i<fin;i++){
        if(numero == arreglo.at(i)){
            contador++;
        }
        else{
            if(contador > contadorAux){
                contadorAux = contador;
                numeroAux = numero;
            }
            contador = 1;
            numero = arreglo.at(i);
        }
    }

    if(contadorAux > contador){
        contador = contadorAux;
        numero = numeroAux;
    }

    return numero;
}

float mediana(vector<int> arreglo, int fin){
    if(fin%2!=0){
        return arreglo.at((fin-1)/2);
    }
    else{
        float limitDer = arreglo.at(fin/2);
        float limitIzq = arreglo.at((fin/2)-1);
        return (limitIzq+limitDer)/2;
    }
}
// fin: Apartado de funciones //