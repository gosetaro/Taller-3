import 'dart:io';
import 'dart:async';
import 'dart:convert';
import 'dart:core';
import 'dart:math';

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

double destip(List li, double promedio){
  double sumatoria = 0;
  for (int i=0;i<li.length;i++){
    sumatoria = sumatoria + ((li[i]-promedio)*(li[i]-promedio));
  }
  sumatoria=sumatoria/li.length;
  double root = pow(sumatoria,0.5);
  return root;

}


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

void imprimir_datos(double media, double desv, var moda, double mediana, String name){
  print("===${name}===");
  print("Promedio: ${media}");
  print("Desviación estándar: ${desv}");
  print("Moda: ${moda}");
  print("Mediana: ${mediana}");
}

void integrantes(){
  print ("===Integrantes===");
  print ("Victor Araya Romero");
  print ("Israel Ramirez Cardoso");
  print ("Humberto Román Matamoros");
}
double promedio (List a){
  double valor = 0;
  for (int i = 0;i<a.length;i++){
    valor = valor + a[i];
  }
  return valor/a.length;
}


 

main() {
  stdout.write("Ingree la ruta del archivo: ");
  String ruta =stdin.readLineSync();
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
        imprimir_datos(promedio_ranking, desviacion_ranking,moda(ranking),mediana(ranking),"NEM");
        imprimir_datos(promedio_matematica, desviacion_matematica,moda(matematica),mediana(matematica),"NEM");
        imprimir_datos(promedio_lenguaje, desviacion_lenguaje,moda(lenguaje),mediana(lenguaje),"NEM");
        imprimir_datos(promedio_ciencias, desviacion_ciencias,moda(ciencias),mediana(ciencias),"NEM");
        imprimir_datos(promedio_historia, desviacion_historia,moda(historia),mediana(historia),"NEM");

        integrantes();
        },
      onError: (e) { print(e.toString()); });



}
