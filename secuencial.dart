import 'dart:io';
import 'dart:async';
import 'dart:convert';
import 'dart:core';
import 'dart:math';

/**
 * Función que compara si un número "a" es mayor, menor o igual que el número "b"
 * @param a Numero "a" a comparar
 * @param b Numero "b" a comparar
 * @return Devuelve si el numero a es mayor, igual o menos que el numero b
 */

int comparator(double a, double b){
  if (a < b){
    return -1;
  }
  if (a==b){
    return 0;
  }
  if (a > b){
    return 1;
  }
}

/**
 * Funcion que devuelve la desviacion estandar/tipica de un grupo de datos
 * @param li Lista con el grupo de datos
 * @param promedio Promedio del grupo de datos
 * @return Devuelve la desviación estandar/tipica de un grupo de datos
 */
double destip(List li, double promedio){
  double sumatoria = 0;
  for (int i=0;i<li.length;i++){
    sumatoria = sumatoria + ((li[i]-promedio)*(li[i]-promedio));
  }
  sumatoria=sumatoria/li.length;
  double root = pow(sumatoria,0.5);
  return root;

}

/**
 * Funcion que calcula la moda de un grupo de datos
 * @param li Lista con los datos de un grupo
 * @return Devuelve la moda de un grupo de datos
 */
double moda(List li){
  var contador = 0;
  var posicion = li[0];
  var contadorAux = 0;
  var posicionAux;
  for (int i=0;i<li.length;i++){
    if (posicion == li[i]){
      contador++;
    }
    else{
      if (contador > contadorAux){
        contadorAux=contador;
        posicionAux = posicion;
      }
      contador = 1;
      posicion = li[i];
    }
  }
  if (contadorAux>contador){
    contador = contadorAux;
    posicion = posicionAux;
  }
  return posicion;
}
/**
 * Calcula la mediana del grupo de datos
 * @param li Lista con los datos de un grupo
 * @return Devuelve la mediana del grupo de datos
 */
double mediana(List li){
  if (li.length%2 == 1){
    var mid = (li.length/2-1).ceil();
    return li[mid];
  }
  else{
    var mid = (li.length/2).ceil();
    return (li[mid]+li[mid-1])/2;
  }
}
/**
 * Imprime los obtenidos, media, promedio, moda, mediana y el nombre del grupo
 * @param media Promedio simple del grupo de datos
 * @param desv Desviación estandar del grupo de datos
 * @param moda Moda del grupo de datos
 * @param mediana Mediana del grupo de datos
 * @param name Nombre del grupo de datos
 */
void imprimir_datos(double media, double desv, var moda, double mediana, String name){
  print("===${name}===");
  print("Promedio: ${media}");
  print("Desviación estándar: ${desv}");
  print("Moda: ${moda}");
  print("Mediana: ${mediana}");
}
/**
 * Muestra los integrantes del grupo
 */
void integrantes(){
  print ("===Integrantes===");
  print ("Victor Araya Romero");
  print ("Israel Ramirez Cardoso");
  print ("Humberto Román Matamoros");
}

int main(List<String> args) {
  if(args.length >= 1){
    String ruta =args[0];
    final file = new File(ruta);
    Stream<List<int>> inputStream = file.openRead();
    List nem = [];
    List ranking = [];
    List matematica = [];
    List historia = [];
    List ciencias = [];
    List lenguaje = [];
    double promedio_nem = 0;
    double promedio_ranking = 0;
    double promedio_matematica = 0;
    double promedio_historia = 0;
    double promedio_ciencias = 0;
    double promedio_lenguaje = 0;

    inputStream
      .transform(utf8.decoder)
      .transform(new LineSplitter())
      .listen((String line) {
          var spl = line.split(';');
          nem.add(double.parse(spl[1]));
          promedio_nem = promedio_nem + double.parse(spl[1]);
          ranking.add(double.parse(spl[2]));
          promedio_ranking = promedio_ranking + double.parse(spl[2]);
          matematica.add(double.parse(spl[3]));
          promedio_matematica = promedio_matematica + double.parse(spl[3]);
          lenguaje.add(double.parse(spl[4]));
          promedio_lenguaje = promedio_lenguaje + double.parse(spl[4]);
          ciencias.add(double.parse(spl[5]));
          promedio_ciencias = promedio_ciencias + double.parse(spl[5]);
          historia.add(double.parse(spl[6]));
          promedio_historia = promedio_historia + double.parse(spl[6]);
          },
        onDone: () {
          promedio_nem = promedio_nem / nem.length;
          promedio_ranking = promedio_ranking / ranking.length;
          promedio_matematica = promedio_matematica / matematica.length; 
          promedio_historia = promedio_historia / historia.length;
          promedio_ciencias = promedio_ciencias / ciencias.length;
          promedio_lenguaje = promedio_lenguaje / lenguaje.length;
          double desviacion_nem = destip(nem,promedio_nem);
          double desviacion_ranking = destip(ranking,promedio_ranking);
          double desviacion_matematica = destip(matematica,promedio_matematica);
          double desviacion_lenguaje = destip(lenguaje,promedio_lenguaje);
          double desviacion_ciencias = destip(ciencias,promedio_ciencias);
          double desviacion_historia = destip(historia,promedio_historia);
          nem.sort();
          ranking.sort();
          matematica.sort();
          historia.sort();
          ciencias.sort();
          lenguaje.sort();
          imprimir_datos(promedio_nem, desviacion_nem,moda(nem),mediana(nem),"NEM");
          imprimir_datos(promedio_ranking, desviacion_ranking,moda(ranking),mediana(ranking),"RANKING");
          imprimir_datos(promedio_matematica, desviacion_matematica,moda(matematica),mediana(matematica),"MATEMATICA");
          imprimir_datos(promedio_lenguaje, desviacion_lenguaje,moda(lenguaje),mediana(lenguaje),"LENGUAJE");
          imprimir_datos(promedio_ciencias, desviacion_ciencias,moda(ciencias),mediana(ciencias),"CIENCIAS");
          imprimir_datos(promedio_historia, desviacion_historia,moda(historia),mediana(historia),"HISTORIA");

          integrantes();
          },
        onError: (e) { print(e.toString()); });
        return 0;
    }
    else{
      print("Es necesario ingresar la ruta del archivo con los datos...");
      return 1;
    }
}
