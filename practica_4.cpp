/**************************************
* NOMBRE: Yasin
* PRIMER APELLIDO: Boulahya
* SEGUNDO APELLIDO: Chairi
* DNI: 78967540
* EMAIL: yboulahya1@alumno.uned.es
***************************************/

/**************************************
* Practica 4:
* Sistema GesAMA:
* Gestionar el Alquiler de Maquinaria
* Agrícola
***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

/***************************************************************************************************
                                  TIPOS Y FUNCIONES CALENDARIO
***************************************************************************************************/
//Tipo enumerado de los meses del anno
typedef enum TipoMeses{
    Enero, Febrero, Marzo, Abril,
    Mayo, Junio, Julio, Agosto,
    Septiembre, Octubre, Noviembre, Diciembre
};

//Tipo enumerado de los dias de la semana
typedef enum TipoDiasSemana{
    Lunes, Martes, Miercoles,
    Jueves, Viernes,
    Sabado, Domingo
};

//Tipo estructurado que forma el registro de los componentes de un a�o
typedef struct Anno{
    TipoMeses mes;
    TipoDiasSemana semana;
    int anno;
};

//Tipo cadena para escribir los meses de un a�o
typedef char TipoNombreMeses[15];
//Tipo vector de cadena con espacio para los 12 meses del a�o
typedef TipoNombreMeses TipoMatrizMeses[12];
//Constante que contiene el nombre de los meses del anno
const TipoMatrizMeses cabecerasCalendario = {
    "ENERO     ", "FEBRERO   ", "MARZO     ", "ABRIL     ", "MAYO      ", "JUNIO     ",
    "JULIO     ", "AGOSTO    ", "SEPTIEMBRE", "OCTUBRE   ", "NOVIEMBRE ", "DICIEMBRE "
};


/*===================================================================================
                  FUNCION QUE DETERMINA SI UN ANNO ES BISIESTO
====================================================================================*/
int esBisiesto(int anno) {
    return (anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0);
}

// Funcion para determinar el dia de la semana
/*===================================================================================
                  FUNCION PARA DETERMINAR EL DIA DE LA SEMANA
====================================================================================*/
int obtenerDiaSemana(int anno, int mes, int dia) {
    int h;

    if (mes < 3) {
        mes = mes + 12;
        anno = anno -1;
    }
    // Ajuste para que el 1 de enero de 1601 sea Lunes
    h = (dia + 2 * mes + 3 * (mes + 1) / 5 + anno + anno / 4 - anno / 100 + anno / 400 + 1) % 7;
    return h;
}

/*===================================================================================
              FUNCION PARA DETERMINAR LA CANTIDAD DE DIAS EN UN MES
====================================================================================*/
int obtenerDiasEnMes(int anno, int mes) {
    if (mes == 2) {
        // Verificar si el anno es bisiesto
        if ((anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0)) {
            return 29; // Anno bisiesto, febrero tiene 29 dias
        } else {
            return 28; // Anno no bisiesto, febrero tiene 28 dias
        }
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        return 30; // Abril, junio, septiembre, noviembre tienen 30 dias
    } else {
        return 31; // Enero, marzo, mayo, julio, agosto, octubre, diciembre tienen 31 dias
    }
}

/*===================================================================================
            FUNCION PARA CALCULAR LA NUEVA FECHA EN BASE A LA FECHA DADA
====================================================================================*/
void calcularNuevaFecha(int dia, int mes, int anno, int diasAgregados) {
    int diasEnMes;

    // Ciclo para sumar los días
    while (diasAgregados > 0) {
        diasEnMes = obtenerDiasEnMes(anno, mes);

        // Si quedan más días en el mes actual
        if (dia + diasAgregados <= diasEnMes) {
            dia = dia + diasAgregados;
            diasAgregados = 0;
        } else {
            // Pasar al siguiente mes
            diasAgregados = diasAgregados - (diasEnMes - dia + 1);
            dia = 1;

            // Si queda más de un mes, avanzar al siguiente mes
            mes = mes + 1;
            if (mes > 12) {
                mes = 1;
                anno++;
            }
        }
    }

    // Imprimir la nueva fecha
    printf("%02d/%02d/%d", dia, mes, anno);
}

/*===================================================================================
                  FUNCION PARA IMPRIMIR TODA LA LOGICA DEL CALENDARIO
====================================================================================*/
void CalendarioDisplay(){
    int  diasDeLaSemana,
  diasDelMes, diasDelMesAnterior,
  diaActual, diasDelSiguienteMes, contador, indiceDiaSemana;
  Anno registroAnno;
  bool imprimirUltimaLinea;

  // Variable para controlar si se imprimir la ultima linea de puntos
  imprimirUltimaLinea = false;

  contador = 0 ;
  indiceDiaSemana=0;

  printf("Mes (1..12)? ");
  scanf("%d", &registroAnno.mes);

  printf("\nAnno (1601..3000)? ");
  scanf("%d", &registroAnno.anno);

  if( (registroAnno.anno >= 1601 && registroAnno.anno <= 3000)
      &&
      (registroAnno.mes >= 1 && registroAnno.mes <= 12) ) {
  printf("\n%s             %2d\n", cabecerasCalendario[registroAnno.mes-1] , registroAnno.anno);
  printf("===========================\n");
  printf("LU  MA  MI  JU  VI | SA  DO\n");
  printf("===========================\n");

  // Obtener el dia de la semana en el que comienza el mes
  diasDeLaSemana = obtenerDiaSemana(registroAnno.anno, registroAnno.mes, 1);

  // Obtener la cantidad de dias en el mes
  diasDelMes = obtenerDiasEnMes(registroAnno.anno, registroAnno.mes);

  // Calcular la cantidad de dias del mes anterior que se solapan
  if (diasDeLaSemana == 0) {
    diasDelMesAnterior = 6;
  } else {
    diasDelMesAnterior = diasDeLaSemana - 1;
  }

  // Variable para rastrear el dia actual
  diaActual = 1;


  // Imprimir los dias del mes
  for (int i = 0; i < 6 && !imprimirUltimaLinea; i++) { // incluye el numero de lineas
    for (int j = 0; j < 7; j++) {
      // Calcular la cantidad de dias del siguiente mes que se solapan
          diasDelSiguienteMes = 7 - j;
          indiceDiaSemana = 7 - j;
      // Imprimir "|" entre VI y SA
      if (j == 5) {
        printf("| ");
      }

      // Imprimir los numeros del dia o un punto si esta fuera del rango del mes
      if ((i == 0 && j < diasDelMesAnterior) || diaActual > diasDelMes) {
        if( indiceDiaSemana == 3/*j==4*/){
          printf(" . ");
        }else if(diasDelSiguienteMes ){
          printf(" .  ");
          contador = contador + 1;
        }
      } else {
        if (diaActual <= diasDelMes) {
          // Marcar que se imprimir la ultima linea si estamos en el ultimo dia del mes
          imprimirUltimaLinea = (diaActual == diasDelMes);
          if (j == 4) {
            printf("%2d ", diaActual);
          }else{
            printf("%2d  ", diaActual);
          }
          diaActual = diaActual+1;
        } else {


          // Calcular la cantidad de dias del siguiente mes que se solapan
          diasDelSiguienteMes = 7 - j;
          printf(" . ");
        }
      }
    }//fin for j12

    // Saltar a la siguiente linea despues de cada sabado
    printf("\n");

  }//fin for i
    printf("\n");
  } else {
    //Si no se introduce mes y anno bien, salta este mensaje
    printf("\nIntroduzca meses comprendidos del 1 al 12 y anno comprendido del 1601 al 3000.\n");
  }//fin condicion 1601 <= anno <= 3000
}


/**************************************************************************************************
                        TIPOS Y FUNCIONES GESTION DE MAQUINAS Y FINCAS
***************************************************************************************************/
const int RADIO = 6371; //Radio de la Tierra en kilómetros

//Tipos para los registros de la máquina:
typedef char TipoCadena20[20];  //nombre
typedef int TipoVector10[10];

//Estructura maquinas
typedef struct TipoDatosMaquinas {
  int id;
  TipoCadena20 nombre;
  char caracterEleccion;
  int capacidad;
  float latitud;
  float longitud;
  bool disponible;

  void BorrarMaquina(TipoDatosMaquinas maquina);
};
typedef TipoDatosMaquinas TipoTablaMaquinas[10];

//Estructura finca
typedef struct TipoDatosFinca {
  int id;
  TipoCadena20 nombre;
  char caracterEleccion;
  int tamanno;
  float latitud;
  float longitud;
  bool disponible;
};
typedef TipoDatosFinca TipoTablaFincas[20];

//Estructura alquiler de maquina
typedef struct TipoDatosAlquilerMaquina{
  int id;
  int dia;
  int mes;
  int anno;
  int idFinca;
  int idMaquina;
  bool disponible;

  void borrarAlquilerMaquina(TipoDatosAlquilerMaquina datos);
};
typedef TipoDatosAlquilerMaquina TipoTablaAlquiler[20];

TipoTablaMaquinas tablaMaquinas = {};
TipoTablaFincas tablaFincas = {};
TipoTablaAlquiler tablaAlquiler = {};

void TipoDatosAlquilerMaquina::borrarAlquilerMaquina(TipoDatosAlquilerMaquina datos){
  datos.id = 0;
  datos.mes = 0;
  datos.anno = 0;
  datos.idFinca = 0;
  datos.idMaquina = 0;
  datos.disponible = false;
}

/*=====================================================================================
                                    BORRAR MAQUINA
=======================================================================================*/
void TipoDatosMaquinas::BorrarMaquina(TipoDatosMaquinas maquina){
  /** REPARAR FUNCION, NO FUNCIONA **/
  maquina.id = 0;
  strcpy(maquina.nombre, "");
  maquina.caracterEleccion = '\0';
  maquina.capacidad = 0;
  maquina.latitud = 0.0;
  maquina.longitud = 0.0;
  maquina.disponible = false;

  tablaMaquinas[maquina.id-1] = maquina;
}

/*=====================================================================================
                                    BORRAR FINCA
=======================================================================================*/
void BorrarFinca(TipoDatosFinca finca, TipoTablaFincas tablaFincas, int id){
  finca.id = 0;
  strcpy(finca.nombre, "");
  finca.caracterEleccion = '\0';
  finca.tamanno = 0;
  finca.latitud = 0.0;
  finca.longitud = 0.0;
  finca.disponible = false;

  tablaFincas[id-1] = finca;
}

/*=====================================================================================
                                  EDITA LAS MAQUINAS
=======================================================================================*/
void EditarMaquina(){
  int opcionIdentificador;
  bool opcionGrano;
  bool opcionSN;
  char opcionCaracterSN;
  TipoCadena20 nombreAux;
  char opcionAux;
  int capacidadAux;
  float latitudAux;
  float longitudAux;
  TipoDatosMaquinas maquina;
  bool opcionBool;
  TipoTablaMaquinas tablaMaquinasAux;

  opcionGrano = true;
  opcionSN = true;

  printf("\nIdentificador (numero entre 1 y 10)?         Ejemplo: 3\n");
  printf("Nombre (entre 1 y 20 caracteres)?            Ejemplo: Apolo\n");
  printf("Tipo (G-Grano, U-Uva, A-Aceituna, B-Borrar)? Ejemplo: G\n");
  printf("Capacidad (hectareas/dia)?                   Ejemplo: 7\n");
  printf("Ubicacion inicial (Longitud)?                Ejemplo: 37.755\n");
  printf("Ubicacion Inicial (Latitud)?                 Ejemplo: -4.467\n");

  printf("\n\nIMPORTANTE: Esta opcion borra los datos anteriores\n");
  printf("Son Correctos los nuevos datos (S/N)?\n");
  printf("\n");

/***************************************************************************************
                              PROCESAMIENTO DE OPCIONES
****************************************************************************************/
  //Identificador:
  printf("\nIdentificador (numero entre 1 y 10)?         Ejemplo: 3\n");
  do{
    scanf("%d", &maquina.id);
    fflush(stdin);
    if(maquina.id<1 || maquina.id>10){
      printf("Introduce un numero entre 1 y 10\n");
    }
  }while(maquina.id<1 || maquina.id>10);
  printf("Identificador: %d\n\n", maquina.id);

  //Introduce nombre de maquina
  printf("Nombre (entre 1 y 20 caracteres)?\n");
  do{
    gets(maquina.nombre);
    fflush(stdin);
    if(strlen(maquina.nombre)>20){
      printf("El nombre debe ser de hasta 20 caracteres\n");
    }
  }while(strlen(maquina.nombre)>20);
  fflush(stdin);
  printf("Nombre: %s\n\n",maquina.nombre );

  //Seleccion de Tipo de cosecha/opcion borrar
  printf("Tipo  (G-Grano, U-Uva, A-Aceituna, B-Borrar)?\n");
  opcionAux = '\0';
  maquina.caracterEleccion = '\0';
  while(opcionGrano){
    scanf("%s", &opcionAux);
    maquina.caracterEleccion = toupper(opcionAux);
    switch(maquina.caracterEleccion){
      case 'G':
        maquina.caracterEleccion = 'G';
        opcionGrano = false;
        break;
      case 'U':
        maquina.caracterEleccion = 'U';
        opcionGrano = false;
        break;
      case 'A':
        maquina.caracterEleccion = 'A';
        opcionGrano = false;
        break;
      case 'B':
        maquina.caracterEleccion = 'B';
        opcionGrano = false;
        break;
      default:
        printf("Introduce un caracter valido: Tipo  (G-Grano, U-Uva, A-Aceituna, B-Borrar)?\n");
    }
  }

  printf("Tipo: %c",maquina.caracterEleccion);
  if(maquina.caracterEleccion =='G'){
    printf("-Grano\n\n");
  }else if(maquina.caracterEleccion == 'U'){
    printf("-Uva\n\n");
  }else if(maquina.caracterEleccion =='A'){
    printf("-Aceituna\n\n");
  }else if(maquina.caracterEleccion == 'B'){
    printf("-Borrar\n\n");
  }

  //hectaria/dia
  printf("Capacidad (hectareas/dia)?\n");
  scanf("%d", &maquina.capacidad);
  fflush(stdin);
  printf("Capacidad: %d (hectareas/dia)\n\n", maquina.capacidad);

  //Latitud
  printf("Ubicacion inicial (Latitud)?\n");
  scanf("%f", &maquina.latitud);
  fflush(stdin);
                                     //%.3f solo permite 3 decimales
  printf("Ubicacion inicial (Latitud): %.3f\n\n", maquina.latitud);

  //Longitud
  printf("Ubicacion inicial (Longitud)?\n");
  scanf("%f", &maquina.longitud);
  fflush(stdin);
                                      //%.3f solo permite 3 decimales
  printf("Ubicacion inicial (Longitud): %.3f\n\n", maquina.longitud);

  //Pregunta si esta seguro del cambio
  printf("IMPORTANTE: Esta opcion borra los datos anteriores\n");
  printf("Son correctos los nuevos datos (S/N)?\n");

  do{
    opcionAux = '\0';
    opcionCaracterSN = '\0';
    scanf("%s", &opcionAux);
    opcionCaracterSN = toupper(opcionAux);
    fflush(stdin);
    if(opcionCaracterSN == 'S' || opcionCaracterSN == 'N'){
      opcionSN = false;
      if(opcionCaracterSN == 'S'){
        if(maquina.caracterEleccion == 'B'){
          if(tablaMaquinas[maquina.id-1].caracterEleccion != NULL){
            tablaMaquinas[maquina.id-1].id = 0;
            strcpy(tablaMaquinas[maquina.id-1].nombre, "");
            tablaMaquinas[maquina.id-1].caracterEleccion = '\0';
            tablaMaquinas[maquina.id-1].capacidad = 0;
            tablaMaquinas[maquina.id-1].latitud = 0.0;
            tablaMaquinas[maquina.id-1].longitud = 0.0;
            tablaMaquinas[maquina.id-1].disponible = false;
            //maquina.BorrarMaquina(maquina);
            printf("La maquina %s con ID %d se elimino de BBDD\n", maquina.nombre, maquina.id);
          }
        }else{
          tablaMaquinasAux[maquina.id-1] = maquina;
        }
      }else{
        continue;
      }
    }else{
      printf("Introduce una opcion correcta\n");
      printf("IMPORTANTE: Esta opcion borra los datos anteriores\n");
      printf("Son correctos los nuevos datos (S/N)?\n");
      opcionSN = true;
    }
  }while(opcionSN);
    if(opcionCaracterSN == 'S' && maquina.caracterEleccion != 'B'){
      printf("\n");
      printf("ID\t");
      printf("Nombre\t\t");
      printf("Tipo\t");
      printf("Capacidad\t\t");
      printf("Latitud\t\t");
      printf("Longitud\n");

      printf("%-8d", maquina.id);
      printf("%-16s", maquina.nombre);
      printf("%-8c", maquina.caracterEleccion);
      printf("%d (Hectarea/dia)\t", maquina.capacidad);
      printf("%.3f\t\t", maquina.latitud);
      printf("%.3f\n\n", maquina.longitud);

      tablaMaquinas[maquina.id-1] = tablaMaquinasAux[maquina.id-1];
    }else{
      printf("No se han guardado los datos\n");
    }


    system("pause");
}

/*=====================================================================================
                                    EDITA LAS FINCAS
=======================================================================================*/
void EditarFinca(){
  int opcionIdentificador;
  bool opcionGrano;
  bool opcionSN;
  char opcionCaracterSN;
  TipoCadena20 nombreAux;
  char caracterEleccionAux;
  int capacidadAux;
  float latitudAux;
  float longitudAux;
  TipoDatosFinca finca;
  bool opcionBool;
  TipoTablaFincas tablaFincasAux;
  char opcionAux;

  opcionGrano = true;
  opcionSN = true;

  printf("Identificador (numero entre 1 y 20)?         5\n");
  printf("Nombre (entre 1 y 20 caracteres)?            Espartal\n");
  printf("Tipo (G-Grano, U-Uva, A-Aceituna, B-Borrar)? G\n");
  printf("Tamanno (Hectareas)?                         75\n");
  printf("Ubicacion (Latitud)?                         42.454\n");
  printf("Ubicacion (Longitud)?                        -4.059\n");

/***************************************************************************************
                              PROCESAMIENTO DE OPCIONES
****************************************************************************************/
  //Identificador:
  printf("\nIdentificador (numero entre 1 y 10)?         Ejemplo: 3\n");
  do{
    scanf("%d", &finca.id);
    fflush(stdin);
    if(finca.id<1 || finca.id>10){
      printf("Introduce un numero entre 1 y 10\n");
    }
  }while(finca.id<1 || finca.id>10);
  printf("Identificador: %d\n\n", finca.id);

  //Introduce nombre de maquina
  printf("Nombre (entre 1 y 20 caracteres)?\n");
  do{
    gets(finca.nombre);
    fflush(stdin);
    if(strlen(finca.nombre)>20){
      printf("El nombre debe ser de hasta 20 caracteres\n");
    }
  }while(strlen(finca.nombre)>20);
  fflush(stdin);
  printf("Nombre: %s\n\n",finca.nombre);

  //Seleccion de Tipo de cosecha/opcion borrar
  printf("Tipo  (G-Grano, U-Uva, A-Aceituna, B-Borrar)?\n");
  while(opcionGrano){
    opcionAux = '\0';
    finca.caracterEleccion = '\0';
    scanf("%s", &opcionAux);
    finca.caracterEleccion = toupper(opcionAux);
    switch(finca.caracterEleccion){
      case 'G':
        finca.caracterEleccion = 'G';
        opcionGrano = false;
        break;
      case 'U':
        finca.caracterEleccion = 'U';
        opcionGrano = false;
        break;
      case 'A':
        finca.caracterEleccion = 'A';
        opcionGrano = false;
        break;
      case 'B':
        finca.caracterEleccion = 'B';
        opcionGrano = false;
        break;
      default:
        printf("Introduce un caracter valido: Tipo  (G-Grano, U-Uva, A-Aceituna, B-Borrar)?\n");
    }
  }

  printf("Tipo: %c",finca.caracterEleccion);
  if(finca.caracterEleccion =='G'){
    printf("-Grano\n\n");
  }else if(finca.caracterEleccion == 'U'){
    printf("-Uva\n\n");
  }else if(finca.caracterEleccion =='A'){
    printf("-Aceituna\n\n");
  }else if(finca.caracterEleccion == 'B'){
    printf("-Borrar\n\n");
  }

  //hectaria/dia
  printf("Tamanno (Hectareas)?\n");
  scanf("%d", &finca.tamanno);
  fflush(stdin);
  printf("Tamanno: %d (Hectareas)\n\n", finca.tamanno);

  //Latitud
  printf("Ubicacion inicial (Latitud)?\n");
  scanf("%f", &finca.latitud);
  fflush(stdin);
                                     //%.3f solo permite 3 decimales
  printf("Ubicacion inicial (Latitud): %.3f\n\n", finca.latitud);

  //Longitud
  printf("Ubicacion inicial (Longitud)?\n");
  scanf("%f", &finca.longitud);
  fflush(stdin);
                                      //%.3f solo permite 3 decimales
  printf("Ubicacion inicial (Longitud): %.3f\n\n", finca.longitud);

  //Pregunta si esta seguro del cambio
  printf("IMPORTANTE: Esta opcion borra los datos anteriores\n");
  printf("Son correctos los nuevos datos (S/N)?\n");

  do{
    opcionAux = '\0';
    opcionCaracterSN = '\0';
    scanf("%s", &opcionAux);
    opcionCaracterSN = toupper(opcionAux);
    fflush(stdin);
    if(opcionCaracterSN == 'S' || opcionCaracterSN == 'N'){
      opcionSN = false;
      if(opcionCaracterSN == 'S'){
        if(finca.caracterEleccion == 'B'){
          if(tablaFincas[finca.id-1].caracterEleccion != NULL){
            tablaFincas[finca.id-1].id = 0;
            strcpy(tablaFincas[finca.id-1].nombre, "");
            tablaFincas[finca.id-1].caracterEleccion = '\0';
            tablaFincas[finca.id-1].tamanno = 0;
            tablaFincas[finca.id-1].latitud = 0.0;
            tablaFincas[finca.id-1].longitud = 0.0;
            tablaFincas[finca.id-1].disponible = false;
            printf("La finca %s con ID %d se elimino de BBDD\n", finca.nombre, finca.id);
          }

          //BorrarFinca(finca,tablaFincas, finca.id-1);
        }else{
          tablaFincasAux[finca.id-1] = finca;
        }
      }else{
        continue;
      }
    }else{
      printf("Introduce una opcion correcta\n");
      printf("IMPORTANTE: Esta opcion borra los datos anteriores\n");
      printf("Son correctos los nuevos datos (S/N)?\n");
      opcionSN = true;
    }
  }while(opcionSN);
    if(opcionCaracterSN == 'S' && finca.caracterEleccion != 'B'){
      printf("\n");
      printf("ID\t");
      printf("Nombre\t\t");
      printf("Tipo\t");
      printf("Tamanno\t\t");
      printf("Latitud\t\t");
      printf("Longitud\n");

      printf("%-8d", finca.id);
      printf("%-16s", finca.nombre);
      printf("%-8c", finca.caracterEleccion);
      printf("%d hectareas\t", finca.tamanno);
      printf("%.3f\t\t", finca.latitud);
      printf("%.3f\n\n", finca.longitud);

      tablaFincas[finca.id-1] = finca;
    }else{
      printf("Los datos introducidos no se han guardado\n");
    }
    system("pause");
}

/*=====================================================================================
                                  LISTAR MAQUINAS
=======================================================================================*/
void ListarMaquinas(){
  char opcionLista;
  char opcionListaAux;

  printf("Tipo de maquinas a listar (G-Grano, U-Uva, A-Aceituna, T-Todas)?\n");
  opcionLista = '\0';
  opcionListaAux = '\0';
  scanf("%s", &opcionListaAux);
  opcionLista = toupper(opcionListaAux);
  printf("\n");
  printf("ID\t");
  printf("Nombre\t\t");
  printf("Tipo\t");
  printf("Capacidad\t\t\n");
  //printf("Latitud\t\t");
  //printf("Longitud\n");
  for(int i=0; i<10; i++){
    if(tablaMaquinas[i].caracterEleccion == opcionLista){
      printf("%-8d", tablaMaquinas[i].id);
      printf("%-16s", tablaMaquinas[i].nombre);
      printf("%-8c", tablaMaquinas[i].caracterEleccion);
      printf("%d hectareas/dia\n", tablaMaquinas[i].capacidad);
      //printf("%.3f \t\t", tablaMaquinas[i].latitud);
      //printf("%.3f\n\n", tablaMaquinas[i].longitud);
    }else if(opcionLista == 'T'){
      printf("%-8d", tablaMaquinas[i].id);
      printf("%-16s", tablaMaquinas[i].nombre);
      printf("%-8c", tablaMaquinas[i].caracterEleccion);
      printf("%d hectareas/dia\n", tablaMaquinas[i].capacidad);

      //printf("%.3f \t\t", tablaMaquinas[i].latitud);
      //printf("%.3f\n\n", tablaMaquinas[i].longitud);
    }
  }
  system("pause");
}

/*=====================================================================================
                                  LISTAR FINCAS
=======================================================================================*/
void EstadoFincas(){
  char opcionLista;
  char opcionListaAux;

  printf("Estado de fincas a listar (G-Grano, U-Uva, A-Aceituna, T-Todas)?\n");
  opcionLista = '\0';
  opcionListaAux = '\0';
  scanf("%s", &opcionListaAux);
  opcionLista = toupper(opcionListaAux);
  printf("\n");
  printf("ID\t");
  printf("Nombre\t\t");
  printf("Tipo\t");
  printf("Tamanno\t\t");
  printf("Latitud\t\t");
  printf("Longitud\n");
  for(int i=0; i<10; i++){
    if(tablaFincas[i].caracterEleccion == opcionLista){
      printf("%-8d", tablaFincas[i].id);
      printf("%-16s", tablaFincas[i].nombre);
      printf("%-8c", tablaFincas[i].caracterEleccion);
      printf("%d hectarea\t", tablaFincas[i].tamanno);
      printf("%.3f \t\t", tablaFincas[i].latitud);
      printf("%.3f\n\n", tablaFincas[i].longitud);
    }else if(opcionLista == 'T'){
      printf("%-8d", tablaFincas[i].id);
      printf("%-16s", tablaFincas[i].nombre);
      printf("%-8c", tablaFincas[i].caracterEleccion);
      printf("%d hectarea\t", tablaFincas[i].tamanno);
      printf("%.3f \t\t", tablaFincas[i].latitud);
      printf("%.3f\n\n", tablaFincas[i].longitud);
    }
  }
  system("pause");
}

/*=====================================================================================
                                CALCULO HECTAREA/DIA
=======================================================================================*/
int CalculoHectariasDias(float capacidad, float tamanno){
  int resultado;

  //Si tiene decimas de más se redondea hacia arriba agregando un dia mas
  resultado = int(ceil(tamanno/capacidad));

  return resultado;
}

/*=====================================================================================
                              CALCULO DE GRADO A RADIANES
=======================================================================================*/
float gradosARadianes(float grados){
  return (grados * M_PI) / 180.0;
}

/*=====================================================================================
                          CALCULO DE TIEMPO RECORRIDO EN DIAS
=======================================================================================*/
float calcularTiempo(float distancia, float velocidad) {
    // Calcular el tiempo en horas
    float tiempoEnHoras = distancia/velocidad;
    // Convertir el tiempo a días
    float tiempoEnDias = tiempoEnHoras/ 24.0;

    return tiempoEnDias;
}

/*=====================================================================================
                    CALCULO DE DISTANCIA DE GRADOS A KILOMETROS
=======================================================================================*/
float distanciaHarvesine(float lat1, float lon1, float lat2, float lon2){
  float deltaLat;
  float deltaLon;
  float a;
  float c;
  float distancia;

  // Convertir las coordenadas de grados a radianes
  lat1 = gradosARadianes(lat1);
  lon1 = gradosARadianes(lon1);
  lat2 = gradosARadianes(lat2);
  lon2 = gradosARadianes(lon2);

  // Calcular las diferencias de latitud y longitud
  deltaLat = lat2 - lat1;
  deltaLon = lon2 - lon1;

  // Aplicar la fórmula haversine
  a = (sin(deltaLat / 2.0) * sin(deltaLat / 2.0)) + (cos(lat1) * cos(lat2) * sin(deltaLon / 2.0) * sin(deltaLon / 2.0));
  c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

  // Calcular la distancia en línea recta en kilómetros
  distancia = RADIO * c;

  return distancia;
}

// Función para verificar la disponibilidad de la máquina en una fecha específica
bool verificarDisponibilidad(TipoDatosAlquilerMaquina datosAlquiler, int dia, int mes, int anno) {
    int diasTranscurridos;

    // Verificar si la fecha solicitada está dentro del período de alquiler de la máquina
    if (anno > datosAlquiler.anno || (anno == datosAlquiler.anno && mes > datosAlquiler.mes) ||
        (anno == datosAlquiler.anno && mes == datosAlquiler.mes && dia >= datosAlquiler.dia)) {
        diasTranscurridos = (anno - datosAlquiler.anno) * 365 + (mes - datosAlquiler.mes) * 30 + (dia - datosAlquiler.dia);

        // Verificar si la máquina está disponible en la fecha solicitada
        if (diasTranscurridos < datosAlquiler.dia) {
            printf("La máquina esta ocupada hasta el %02d/%02d/%d\n", datosAlquiler.dia, datosAlquiler.mes, datosAlquiler.anno);
            return false;
        } else {
            printf("La máquina esta disponible hasta el %02d/%02d/%d\n", datosAlquiler.dia, datosAlquiler.mes, datosAlquiler.anno);
            return true;
        }
    } else {
        printf("La fecha solicitada está fuera del período de alquiler de la máquina.\n");
        return false;
    }
}

/*=====================================================================================
                                  ALQUILER MAQUINA
=======================================================================================*/
void AlquilerMaquina(){
  TipoDatosAlquilerMaquina datosAlquilerMaquina = {};
  bool ciclo;
  int calcHectDias;
  float distancia;
  int tiempoEnDias;
  int calHecDia;
  bool cicloAlquiler;
  char opcionSN;
  bool bOpcionSN;
  char opcionSNAux;
  int diaAux;
  int mesAux;
  int annoAux;
  int idFincaAux;
  int idMaquinaAux;
  bool disponibilidadMaquina;

  ciclo = true;
  cicloAlquiler = true;

  while(cicloAlquiler){
    printf("Fecha comienzo cosecha: Dia?                    Ejemplo: 9\n");
    do{
      diaAux = 0;
      scanf("%d", &diaAux);
      datosAlquilerMaquina.dia = diaAux;
      if(datosAlquilerMaquina.dia<1 || datosAlquilerMaquina.dia>31){
        ciclo = true;
        printf("Introduce una dia entre 1 y 31\n");
      }else{
        ciclo = false;
      }
    }while(ciclo);

    printf("Fecha comienzo cosecha: Mes?                    Ejemplo: 7\n");
    do{
      mesAux = 0;
      scanf("%d", &mesAux);
      datosAlquilerMaquina.mes = mesAux;
      if(datosAlquilerMaquina.mes<1 || datosAlquilerMaquina.mes>12){
        ciclo = true;
        printf("Introduce un mes entre 1 y 12\n");
      }else{
        ciclo = false;
      }
    }while(ciclo);

    printf("Fecha comienzo cosecha: Anno?                   Ejemplo: 2024\n");
    do{
      annoAux = 0;
      scanf("%d", &annoAux);
      datosAlquilerMaquina.anno = annoAux;
      if(datosAlquilerMaquina.anno<2023 && datosAlquilerMaquina.mes>2100){
        ciclo = true;
        printf("Introduce el anno de la citas\n");
      }else{
        ciclo = false;
      }
    }while(ciclo);

    printf("Identificador de finca (numero entre 1 y 20)?   Ejemplo: 5\n");
    do{
      idFincaAux = 0;
      scanf("%d", &idFincaAux);
      datosAlquilerMaquina.idFinca = idFincaAux;
      if(datosAlquilerMaquina.idFinca<1 || datosAlquilerMaquina.idFinca>20){
        ciclo = true;
        printf("Introduce el id de la finca entre 1 y 20\n");
      }else{
        ciclo = false;
      }
    }while(ciclo);

    printf("Identificador de maquina (numero entre 1 y 10)? Ejemplo: 3\n");
    do{
      idMaquinaAux = 0;
      scanf("%d", &idMaquinaAux);
      datosAlquilerMaquina.idMaquina = idMaquinaAux;
      if(datosAlquilerMaquina.idMaquina<1 || datosAlquilerMaquina.idMaquina>10){
        ciclo = true;
        printf("Introduce el id de la maquina entre 1 y 10\n");
      }else{
        ciclo = false;
      }
    }while(ciclo);

/***************************************************************************
              COMPROBAR SI LA MAQUINA Y LA FINCA EXISTEN
****************************************************************************/

    if( (tablaMaquinas[datosAlquilerMaquina.idMaquina-1].id != datosAlquilerMaquina.idMaquina ||
    tablaFincas[datosAlquilerMaquina.idFinca-1].id != datosAlquilerMaquina.idFinca) &&
   (tablaMaquinas[datosAlquilerMaquina.idMaquina-1].id != datosAlquilerMaquina.idMaquina ||
    tablaFincas[datosAlquilerMaquina.idFinca-1].id != datosAlquilerMaquina.idFinca)){
      if(tablaMaquinas[datosAlquilerMaquina.idMaquina-1].id != datosAlquilerMaquina.idMaquina){
        printf("Maquina no registrada\n");
      }
      if(tablaFincas[datosAlquilerMaquina.idFinca-1].id != datosAlquilerMaquina.idFinca){
        printf("Finca no registrada\n");
      }
      printf("no se puede hacer el calculo del alquiler\n");
      cicloAlquiler = false;
      system("pause");
    }else{
      datosAlquilerMaquina.disponible = true;
      disponibilidadMaquina = verificarDisponibilidad(tablaAlquiler[datosAlquilerMaquina.id-1], diaAux, mesAux, annoAux);


      printf("\n");
      printf("ID\t");
      printf("Nombre Maquina\t");
      printf("Tipo\t");
      printf("Capacidad\t\t");
      printf("Latitud\t\t");
      printf("Longitud\t");
      printf("Disponibilidad\n");

      printf("%-8d",tablaMaquinas[datosAlquilerMaquina.idMaquina-1].id);
      printf("%-16s",tablaMaquinas[datosAlquilerMaquina.idMaquina-1].nombre);
      printf("%-8c",tablaMaquinas[datosAlquilerMaquina.idMaquina-1].caracterEleccion);
      printf("%-24d",tablaMaquinas[datosAlquilerMaquina.idMaquina-1].capacidad);
      printf("%.3f\t\t",tablaMaquinas[datosAlquilerMaquina.idMaquina-1].latitud);
      printf("%.3f\t\t",tablaMaquinas[datosAlquilerMaquina.idMaquina-1].longitud);
      if(tablaMaquinas[datosAlquilerMaquina.idMaquina-1].disponible == true){
        printf("No\n");
      }else{
        printf("Si\n");
      }
      printf("Maquina registrada\n");

      printf("\n");

      printf("\n");
      printf("ID\t");
      printf("Nombre Finca\t");
      printf("Tipo\t");
      printf("Tamanno\t\t");
      printf("Latitud\t\t");
      printf("Longitud\t");
      printf("Ocupada\n");

      printf("%-8d",tablaFincas[datosAlquilerMaquina.idMaquina-1].id);
      printf("%-16s",tablaFincas[datosAlquilerMaquina.idMaquina-1].nombre);
      printf("%-8c",tablaFincas[datosAlquilerMaquina.idMaquina-1].caracterEleccion);
      printf("%-24d\t\t",tablaFincas[datosAlquilerMaquina.idMaquina-1].tamanno);
      printf("%.3f\t\t",tablaFincas[datosAlquilerMaquina.idMaquina-1].latitud);
      printf("%.3f\t",tablaFincas[datosAlquilerMaquina.idMaquina-1].longitud);
      if(tablaFincas[datosAlquilerMaquina.idMaquina-1].disponible == true){
        printf("Si\n");
      }else{
        printf("No\n");
      }
      printf("Finca registrada\n");

      //Se establece el id del registro de la tabla como el id de la maquina
      datosAlquilerMaquina.id = datosAlquilerMaquina.idMaquina;

      printf("\n");
      printf("\t\t\tResumen alquiler:\n");
      printf("\n");

      printf("Maquina alquilada: %s (Id = %d)\n", tablaMaquinas[datosAlquilerMaquina.id-1].nombre, tablaMaquinas[datosAlquilerMaquina.id-1].id);
      printf("Finca a cosechar: %s (Id = %d)\n", tablaFincas[datosAlquilerMaquina.id-1].nombre, tablaFincas[datosAlquilerMaquina.id-1].id);
      printf("Traslado desde: finca %s (Id = %d)\n", tablaFincas[datosAlquilerMaquina.id-1].nombre, tablaFincas[datosAlquilerMaquina.id-1].id);
      distancia = distanciaHarvesine(
        tablaMaquinas[datosAlquilerMaquina.id-1].latitud,
        tablaMaquinas[datosAlquilerMaquina.id-1].longitud,
        tablaFincas[datosAlquilerMaquina.id-1].latitud,
        tablaFincas[datosAlquilerMaquina.id-1].longitud
      );
      printf("Distancia entre fincas: %.3f km en linea recta\n", distancia);
      //Algoritmo que calcule el tiempo de traslado en base a la latitud y longitud
      //Partimos del supuesto que la velocidad media para trasportar la máquina en remolque es de 60Km/h
      tiempoEnDias = 0;
      tiempoEnDias = ceil(calcularTiempo(distancia, 60.00));

      //Tiempo de traslado
      printf("Tiempo de traslado: ");
      calcularNuevaFecha(
        datosAlquilerMaquina.dia,
        datosAlquilerMaquina.mes,
        datosAlquilerMaquina.anno,
        tiempoEnDias
      );
      printf("(%d dia/s)\n", tiempoEnDias);

      //Fecha de comienzo
      printf("Fecha comienzo: ");
      calcularNuevaFecha(
        datosAlquilerMaquina.dia,
        datosAlquilerMaquina.mes,
        datosAlquilerMaquina.anno,
        tiempoEnDias
      );
      printf(" (%d dia/s)\n", tiempoEnDias);

      /*PENDIENTE DE TERMINAR*/
      calHecDia = 0;
      calHecDia = CalculoHectariasDias(tablaMaquinas[datosAlquilerMaquina.id-1].capacidad,tablaFincas[datosAlquilerMaquina.id-1].tamanno);

      printf("Duracion cosecha: %d dia/s\n", calHecDia);
      /*PENDIENTE DE TERMINAR*/

      printf("Fecha finalizacion: ");
      calcularNuevaFecha(
        datosAlquilerMaquina.dia,
        datosAlquilerMaquina.mes,
        datosAlquilerMaquina.anno,
        calHecDia
      );
      printf(" (%d dia/s)\n", calHecDia);

      /*
      printf("Fecha finalizacion: %d/%d/%d\n",
      (datosAlquilerMaquina.dia + calHecDia),
      (datosAlquilerMaquina.mes),
      (datosAlquilerMaquina.anno),
      calHecDia);
      */
      system("pause");
      /* PREGUNTAR: Es correcta la operacion? (S/N) */
      while(bOpcionSN){
        bOpcionSN = true;
        printf("Es correcta la operacion? (S/N)\n");
        opcionSNAux = '\0';
        opcionSN = '\0';
        scanf("%s", &opcionSNAux);
        opcionSN = toupper(opcionSNAux);
        switch(opcionSN){
          case 'S':
            bOpcionSN = false;
            cicloAlquiler = false;
            tablaAlquiler[datosAlquilerMaquina.id-1] = datosAlquilerMaquina;
            tablaMaquinas[datosAlquilerMaquina.idMaquina-1].disponible = datosAlquilerMaquina.disponible;
            tablaFincas[datosAlquilerMaquina.idMaquina-1].disponible = datosAlquilerMaquina.disponible;

            printf("\n");
            printf("ID\t");
            printf("Dia\t");
            printf("Mes\t");
            printf("Anno\t");
            printf("ID Finca\t");
            printf("ID Maquina\n");

            printf("%d\t", tablaAlquiler[datosAlquilerMaquina.id-1].id);
            printf("%d\t", tablaAlquiler[datosAlquilerMaquina.id-1].dia);
            printf("%d\t", tablaAlquiler[datosAlquilerMaquina.id-1].mes);
            printf("%d\t", tablaAlquiler[datosAlquilerMaquina.id-1].anno);
            printf("%d\t\t", tablaAlquiler[datosAlquilerMaquina.id-1].idFinca);
            printf("%d\n", tablaAlquiler[datosAlquilerMaquina.id-1].idMaquina);
            printf("Se han guardado los datos correctamente\n");
            system("pause");
            break;

          case 'N':
            datosAlquilerMaquina.borrarAlquilerMaquina(datosAlquilerMaquina);
            bOpcionSN = false;
            cicloAlquiler = false;
            break;
          default:
            bOpcionSN = true;
            printf("Introduce Si o No (S/N)\n");
        }
      }
    }
  }
}

/**************************************************************************************
                                      MAIN
***************************************************************************************/
int main(){
  char opcion;
  bool cicloMenu;
  int contador;
  char opcionAux;

  contador = 0;
  cicloMenu = true;

/*=====================================================================================
                              GESTION DEL MEMU PRINCIPAL
=======================================================================================*/
  //introducimos la condicion para que no exceda el máximo de ciclos deseados
  while(cicloMenu){

    system("cls"); //LIMPA PANTALLA
    printf("GesAMA: Gestion de Alquiler de Maquinas Agricolas\n\n");
    printf("Editar Maquina                         (Pulsar M)\n");
    printf("Editar Finca                           (Pulsar F)\n");
    printf("Listar Maquinas                        (Pulsar L)\n");
    printf("Estado Fincas                          (Pulsar E)\n");
    printf("Alquiler Maquinas                      (Pulsar A)\n");
    printf("Plan Mensual Maquina                   (Pulsar P)\n");
    printf("Salir                                  (Pulsar S)\n");
    printf("\nTeclear una opcion valida (M|F|L|E|A|P|S)?\n");

    opcion = '\0';
    opcionAux = '\0';
    scanf("%c", &opcionAux);
    opcion = toupper(opcionAux);
    switch(opcion){
      case 'M':
        EditarMaquina();
        printf("\nM: Maquina editada\n");
        cicloMenu = true;
        break;
      case 'F':
        EditarFinca();
        printf("\nF: Finca Finca\n");
        cicloMenu = true;
        break;
      case 'L':
        ListarMaquinas();
        printf("\nL: Maquinas Listadas\n");
        cicloMenu = true;
        break;
      case 'E':
        EstadoFincas();
        printf("\nE: Estado Fincas Listado\n");
        cicloMenu = true;
        break;
      case 'A':
        AlquilerMaquina();
        printf("\nA: Alquiler Maquinas Listadas\n");
        cicloMenu = true;
        break;
      case 'P':
        printf("\nP: Plan Mensual Maquina\n");
        cicloMenu = true;
        break;
      case 'S':
        printf("\nS: Salir\n");
        cicloMenu = false;
        break;
      //-------------
      default:
        printf("\nIntroduce opcion correcta\n");
    }
  }

  return 0;
}
