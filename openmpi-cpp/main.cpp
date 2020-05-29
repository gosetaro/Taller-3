#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>
#include <mpi.h>
#include <omp.h>

using namespace std;

#define LARGO 100

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
 * @param linea linea con puntajes 
 * @return devuelve un array vector con los datos separados de la linea
 */
vector<string> splitter(string linea);
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
 * Función para indicar si todos los procesadores han terminado
 * @param procesadores array con el estado de todos los procesadores
 * @return Devuelve si todos los procesadores han terminado o no
 */
bool isEnd(vector<bool> procesadores);

/**
 * 
 * @param argc Cantidad de argumentos traspasados por consola
 * @param argv Array con argumentos traspasados por consola
 * @return Devuelve el código de error
 */
int main(int argc, char** argv) {
    int mi_rango;
    int procesadores;
    int maestro = 0;
    int tag =0;

    MPI_Status estado;
    string stop("stop");
    string ready("ready");
    string files[6] = {"nem","ranking","matematica","lenguaje","ciencias","historia"};
    //Se verifica que se ingresó la ruta del archivo con los puntajes
    if(argc > 1){

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);
        MPI_Comm_size(MPI_COMM_WORLD, &procesadores);

        if(procesadores < 2){
            cout<<endl<<"Se re quiere un mínimo de 2 procesadores..."<<endl;
            return EXIT_FAILURE;
        }

        if(mi_rango == 0){
            string ruta(argv[1]);
            ifstream entrada(ruta);
            //Se verifica que exista tal archivo
            if(entrada){
                //Vectores con los puntajes
                ofstream nem("nem.csv"),ranking("ranking.csv"),matematica("matematica.csv"),lenguaje("lenguaje.csv"),ciencias("ciencias.csv"),historia("historia.csv");
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
                                    nem << puntajes.at(1)<<'\n';
                                    ranking << puntajes.at(2)<<'\n';
                                    matematica << puntajes.at(3)<<'\n';
                                    lenguaje << puntajes.at(4)<<'\n';
                                    ciencias << puntajes.at(5)<<'\n';
                                    historia << puntajes.at(6)<<'\n';
                                    }
                                    
                                }
                                puntajes.clear();
                                
                            }
                        }
                    }
                }
                nem.close();
                ranking.close();
                matematica.close();
                lenguaje.close();
                ciencias.close();
                historia.close();
            
                for(int procesador=1,file=0;file < 6;file++,procesador++){
                    if(procesador >= procesadores){
                        procesador = 1;
                    }
                    MPI_Send((char *) files[file].c_str(),files[file].length() + 1, MPI_CHAR, procesador, tag, MPI_COMM_WORLD);
                }
                for(int procesador=1;procesador < procesadores;procesador++){
                    
                    MPI_Send((char *) stop.c_str(),stop.length() + 1, MPI_CHAR, procesador, tag, MPI_COMM_WORLD);
                }
                entrada.close();
            }
        }
        if(mi_rango == 0){
            vector<bool> isend;
            for(int i = 0; i< procesadores;i++){
                isend.push_back(false);
            }
            isend[0]=true;
            while(!isEnd(isend)){
                for(int i =1;i< procesadores;i++){
                    if(!isend[i]){
                        char* msg = (char *) calloc (LARGO, sizeof (char));
                        MPI_Recv(msg, LARGO, MPI_CHAR, i, tag, MPI_COMM_WORLD, &estado);
                        string info(msg);
                        if(!info.empty()){
                            if(stop.compare(info)==0){
                                isend[i]=true;
                            }
                            else{
                                vector<string> split = splitter(info);
                                cout<<endl<<"="<<split[0]<<"="<<endl<<"Promedio: "<<split[1]<<endl<<"Desviación estandar: "<<split[2]<<endl<<"Moda: "<<split[3]<<endl<<"Mediana: "<<split[4]<<endl;
                            }
                        }
                    }
                    
                }
            }
        }
        else{
            vector<string> file;
            while(true){
                char* msg = (char *) calloc (LARGO, sizeof (char));
                MPI_Recv(msg, LARGO, MPI_CHAR, maestro, tag, MPI_COMM_WORLD, &estado);
                string info(msg);
                if(!info.empty()){
                    if(stop.compare(info)==0){
                        break;
                    }
                    else{
                        file.push_back(info);
                    }
                }
                free(msg);
            }
            
            for(int i = 0; i < file.size(); i++){
                ifstream archivo(file[i]+".csv");
                vector<int> puntos;
                for(string linea; getline(archivo,linea);){
                    if(!linea.empty()){
                        puntos.push_back(atoi(linea.c_str()));
                    }
                }
                int tamano = puntos.size();
                quickSort(&puntos,0,tamano-1);
                double prom = promedio(puntos,tamano);
                double dvs = desvS(puntos, tamano, prom);
                int mod = moda(puntos, tamano);
                int media = mediana(puntos, tamano);

                string info = file[i]+";"+to_string(prom)+";"+to_string(dvs)+";"+to_string(mod)+";"+to_string(media);
                MPI_Send((char *) info.c_str(), info.length()+1, MPI_CHAR, maestro, tag, MPI_COMM_WORLD);
                
                archivo.close();

                ofstream test(file[i]+".csv");
                test << info;
                test.close();

            }
            MPI_Send((char *) stop.c_str(),stop.length() + 1, MPI_CHAR, maestro, tag, MPI_COMM_WORLD);
        }
        
    }
    MPI_Finalize();
        
        
    return 0;
}

void participante(){
    cout<<endl<<"==== Participantes ===="<<endl;
    cout<<"Israel Ramirez Cardoso"<<endl;
    cout<<"Humberto Román Matamoros"<<endl;
    cout<<"Victor Araya Romero"<<endl;
}
vector<string> splitter(std::string linea) {
    vector<string> arreglo;
    std::stringstream ss(linea);
    std::string item;

    while (std::getline(ss, item, ';')) {
        arreglo.push_back(item.c_str());
    }

    return arreglo;
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

bool isEnd(vector<bool> procesadores){
    for(int i =0; i<procesadores.size();i++){
        if(!procesadores[i]){
            return false;
        }
    }
    return true;
}
