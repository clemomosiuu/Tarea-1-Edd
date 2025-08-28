#include <iostream>
#include <iomanip>
#include <string>

struct Dato{

    unsigned int Id;      
    char Nombre [50];    
    char Fecha_Nacimiento [11]; 
    int Notas [3];      
    char Curso [7];      
    unsigned short VTR;   
};

void Menú(){

    std::cout << 
        "1) Agregar un alumno.\n" <<
        "2) Obtener promedio de un estudiante.\n" << 
        "3) Obtener por evaluación de una asignatura.\n" <<
        "4) Obtener los cursos en los que está inscrito un estudiante.\n" <<
        "5) Obtener los reprobados de un curso con cierto VTR.\n" <<
        "6) Generar informe por cursos.\n" <<
        "0) Salir del programa.\n" <<
        "Ingrese su opción: ";  
}

void Mostrar_Datos_Alumno(Dato* datos, int tamanio){

    /*
    *    Descripción: 
    *            Imprimir por consola los datos cargados en el parametro 'datos', mostrando los primeros 5 o menos en caso de que 'tamanio' sea menor a 5.
    *
    *    Parametros:
    *            Dato* datos: Puntero/arreglo que contiene los datos a querer mostrar.
    *            int tamanio: Tamaño del arreglo.
    *    
    *    Retorno:
    *            Función tipo void, no retorna nada.
    *    
    */
    
    std::cout << std::left 
                    << std::setw(8) << "ID" 
                    << std::setw(50) << "NOMBRE" 
                    << std::setw(12) << "CURSO" 
                    << std::setw(17) << "FECHA NAC." 
                    << std::setw(5) << "VTR" 
                    << std::endl;

    for (int i = 0; i < 5 && i < tamanio; i++) {

        std::cout << std::left
                    << std::setw(8) << datos[i].Id 
                    << std::setw(50) << datos[i].Nombre 
                    << std::setw(12) << datos[i].Curso 
                    << std::setw(17) << datos[i].Fecha_Nacimiento 
                    << std::setw(5) << datos[i].VTR 
                    << std::endl;
    }
}

int* Calcular_Promedio_Asignatura(Dato* datos , int cantidad_datos , const char* asignatura_a_buscar){
    int suma[3] = {0,0,0};
    int alumnosValidos = 0;
//   recorrer todo los datos de los estudian
    for(int i = 0; i < cantidad_datos; i++) {
        std::string cursoActual(datos[i].Curso);
        if (cursoActual == asignatura_a_buscar){
            suma[0] += datos[i].Notas[0];
            suma[1] += datos[i].Notas[1];
            suma[2] += datos[i].Notas[2];
            alumnosValidos++;
        }
    }

    if(alumnosValidos == 0) return NULL;

    int* promedios = new int[3];
    promedios[0] = (suma[0] + alumnosValidos/2) / alumnosValidos; // redondeo
    promedios[1] = (suma[1] + alumnosValidos/2) / alumnosValidos;
    promedios[2] = (suma[2] + alumnosValidos/2) / alumnosValidos;

    return promedios;
}

void Listar_Cursos_Estudiante(Dato* datos , int cantidad_datos , unsigned int id_alumno){
    bool encontrado = false; // para ver si se encontro al estudiante

    for (int i = 0; i < cantidad_datos; i++) {
        if (datos[i].Id == id_alumno) {
            if (!encontrado) {
                std::cout << "Las asignaturas inscritas por el estudiante son: ";
                encontrado = true; // se marca que encontro al estudiante
            }
            std::cout << datos[i].Curso << " "; //se improime el curso
        }
    }

    if (!encontrado) {
        std::cout << "No existe registro para el estudiante con Id " << id_alumno << ".";
    }

    std::cout << std::endl;
}

int* Listar_Reprobados_VTR(Dato* datos, int cantidad_datos, unsigned short VTR_a_buscar, const char* asignatura_a_buscar) {
    std::string cursoBuscado(asignatura_a_buscar);

    int* ids_temp = new int[cantidad_datos];
    int contador = 0;

    for (int i = 0; i < cantidad_datos; i++) {
        std::string cursoActual(datos[i].Curso);
        if (cursoActual == cursoBuscado && datos[i].VTR == VTR_a_buscar) {
            int promedio = (datos[i].Notas[0] + datos[i].Notas[1] + datos[i].Notas[2] + 1) / 3;
            if (promedio < 55) {
                ids_temp[contador] = datos[i].Id;
                contador++;
            }
        }
    }

    int* resultado = new int[contador + 1];
    resultado[0] = contador;
    for (int i = 0; i < contador; i++) {
        resultado[i + 1] = ids_temp[i];
    }

    delete[] ids_temp;
    return resultado;
}


void Generar_Informe(Dato* datos, int cantidad_datos) {
    // guardar cursos unicos
    std::string* cursos = new std::string[cantidad_datos];
    int cursosCount = 0;

    for (int i = 0; i < cantidad_datos; i++) {
        std::string cursoActual(datos[i].Curso);
        bool existe = false;
        for (int j = 0; j < cursosCount; j++) {
            if (cursos[j] == cursoActual) {
                existe = true;
            }
        }
        if (!existe) {
            cursos[cursosCount] = cursoActual;
            cursosCount++;
        }
    }

    // pocesar cada curso
    for (int c = 0; c < cursosCount; c++) {
        std::string curso = cursos[c];
        std::ofstream archivo(curso + ".txt");

        if (archivo.is_open()) {
            int cantidad = 0, aprobados = 0, reprobados = 0;
            int maxNotas[3] = {0,0,0};
            int minNotas[3] = {100,100,100};
            int vtr3_reprobados = 0;

            int* ids_vtr3 = new int[cantidad_datos];
            int idsCount = 0;

            //  recorrer los alumnos del curso
            for (int i = 0; i < cantidad_datos; i++) {
                std::string cursoActual(datos[i].Curso);
                if (cursoActual == curso) {
                    cantidad++;
                    int promedio = (datos[i].Notas[0] + datos[i].Notas[1] + datos[i].Notas[2] + 1) / 3;

                    archivo << datos[i].Id << " "
                            << datos[i].Nombre << " "
                            << datos[i].Curso << " "
                            << datos[i].Fecha_Nacimiento << " "
                            << datos[i].VTR << " "
                            << datos[i].Notas[0] << " "
                            << datos[i].Notas[1] << " "
                            << datos[i].Notas[2] << " "
                            << promedio << std::endl;

                    if (promedio >= 55) {
                        aprobados++;
                    } else {
                        reprobados++;
                    }

                    for (int n = 0; n < 3; n++) {
                        if (datos[i].Notas[n] > maxNotas[n]) {
                            maxNotas[n] = datos[i].Notas[n];
                        }
                        if (datos[i].Notas[n] < minNotas[n]) {
                            minNotas[n] = datos[i].Notas[n];
                        }
                    }

                    if (datos[i].VTR == 3 && promedio < 55) {
                        ids_vtr3[idsCount] = datos[i].Id;
                        idsCount++;
                        vtr3_reprobados++;
                    }
                }
            }

            
            archivo << cantidad << std::endl;
            archivo << "Aprobados: " << aprobados << std::endl;
            archivo << "Reprobados: " << reprobados << std::endl;

            int porcentaje = 0;
            if (cantidad > 0) {
                porcentaje = (aprobados * 100) / cantidad;
            }
            archivo << "Porcentaje de aprobación: " << porcentaje << "%" << std::endl;

            archivo << "Maximos: " << maxNotas[0] << " " << maxNotas[1] << " " << maxNotas[2] << std::endl;
            archivo << "Mínimos: " << minNotas[0] << " " << minNotas[1] << " " << minNotas[2] << std::endl;

            archivo << "VTR3 reprobados: " << vtr3_reprobados << std::endl;
            archivo << "Ids: ";
            for (int k = 0; k < idsCount; k++) {
                archivo << ids_vtr3[k] << " ";
            }
            archivo << std::endl;

            archivo.close();
            delete[] ids_vtr3;
        }
    }

    delete[] cursos;
}