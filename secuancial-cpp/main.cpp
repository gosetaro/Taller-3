#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>

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
int main(int argc, char** argv){
    if(argc > 1){
        //Ruta del archivo a leer
        string ruta(argv[1]);
        ifstream entrada(ruta);
        if(entrada){
            // Apartado de obtención de datos //
            int contador = 0;
            //Se obtienen los datos y se guardan en vectores, según la columna que se ingresa
            vector<int> nem, ranking, matematica, lenguaje, ciencias, historia;
            for(string linea; getline(entrada, linea);){
                if(!linea.empty()){
                    vector<int> datos = obtenerPuntajes(linea);
                    nem.push_back(datos.at(1));
                    ranking.push_back(datos.at(2));
                    matematica.push_back(datos.at(3));
                    lenguaje.push_back(datos.at(4));
                    ciencias.push_back(datos.at(5));
                    historia.push_back(datos.at(6));
                    contador++;
                }
            }
            // fin: Apartado de obtención de datos //
            // Apartado de cálculo e impresión de datos //
            quickSort(&nem,0,contador-1);
            quickSort(&ranking,0,contador-1);
            quickSort(&matematica,0,contador-1);
            quickSort(&lenguaje,0,contador-1);
            quickSort(&ciencias,0,contador-1);
            quickSort(&historia,0,contador-1);
            double promedioNem = promedio(nem,contador);
            double promedioRanking = promedio(ranking,contador);
            double promedioMatematica = promedio(matematica,contador);
            double promedioLenguaje = promedio(lenguaje,contador);
            double promedioCiencias = promedio(ciencias,contador);
            double promedioHistoria = promedio(historia,contador);
            cout<<endl<<"=NEM="<<endl<<"Promedio: "<<promedioNem << endl << "Desviaci�n Estandar: " <<desvS(nem,contador, promedioNem)<<endl<<"Moda: "<<moda(nem,contador)<<endl<<"Mediana: "<<mediana(nem,contador)<<endl;
            cout<<endl<<"=RANKING="<<endl<<"Promedio: "<<promedioRanking << endl << "Desviaci�n Estandar: " <<desvS(ranking,contador, promedioRanking)<<endl<<"Moda: "<<moda(ranking,contador)<<endl<<"Mediana: "<<mediana(ranking,contador)<<endl;
            cout<<endl<<"=MATEMATICAS="<<endl<<"Promedio: "<<promedioMatematica << endl << "Desviaci�n Estandar: " <<desvS(matematica,contador, promedioMatematica)<<endl<<"Moda: "<<moda(matematica,contador)<<endl<<"Mediana: "<<mediana(matematica,contador)<<endl;
            cout<<endl<<"=LENGUAJE="<<endl<<"Promedio: "<<promedioLenguaje << endl << "Desviaci�n Estandar: " <<desvS(lenguaje,contador, promedioLenguaje)<<endl<<"Moda: "<<moda(lenguaje,contador)<<endl<<"Mediana: "<<mediana(lenguaje,contador)<<endl;
            cout<<endl<<"=CIENCIAS="<<endl<<"Promedio: "<<promedioCiencias << endl << "Desviaci�n Estandar: " <<desvS(ciencias,contador, promedioCiencias)<<endl<<"Moda: "<<moda(ciencias,contador)<<endl<<"Mediana: "<<mediana(ciencias,contador)<<endl;
            cout<<endl<<"=HISTORIA="<<endl<<"Promedio: "<<promedioHistoria << endl << "Desviaci�n Estandar: " <<desvS(historia,contador, promedioHistoria)<<endl<<"Moda: "<<moda(historia,contador)<<endl<<"Mediana: "<<mediana(historia,contador)<<endl;
            return 0;
            // fin: Apartado de cálculo e impresión de datos //
        }
        else{
            cout<<endl<<"No se pudo cargar el archivo..."<<endl;
            return 1;
        }
    }
    else{
        cout<<endl<<"No se ingresó la ruta del archivo..."<<endl;
        return 1;
    }
}
// Apartado de funciónes //
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