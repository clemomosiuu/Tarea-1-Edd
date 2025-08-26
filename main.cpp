#include <fstream>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;


//definimos struct

struct Dato {
    unsigned int Id;      
    char Nombre[50];    
    char Fecha_Nacimiento[11]; 
    int Notas[3];      
    char Curso[7];      
    unsigned short VTR;   
};

//funcion 1
Dato * Leer_Archivo ( const string & nombre_archivo ) {
   //abrir archivo
    ifstream fin(nombre_archivo, ios::binary);

    if (!fin.is_open()){
        cout<< "No se pudo abrir el archivo" << endl;
        fin.close();    
        return nullptr;
    }
    cout<< "Archivo abierto correctamente" << endl;

    //leer n inicial
    unsigned int n = 0;
    fin.read(reinterpret_cast<char*>(&n), sizeof(unsigned int));
    cout << "Cantidad de estudiantes: " << n << endl;


    //reservamos memoria dinamica para n

    Dato* datos = new Dato[n];
    unsigned int cantidad_datos = n;

    //recorremos los struct cvon un for

    for (unsigned int i = 0; i<n ; i++){
        fin.read((char*)&datos[i].Id, sizeof(unsigned int)); //3
        fin.read(datos[i].Nombre, 50); //53
        fin.read(datos[i].Fecha_Nacimiento, 11); //64
        fin.ignore(3); // padding //67
        fin.read((char*)datos[i].Notas, 3 * sizeof(int)); //79
        fin.read(datos[i].Curso, 7); //86
        fin.ignore(1); // padding //87
        fin.read((char*)&datos[i].VTR, sizeof(unsigned short)); //90
        fin.ignore(2); // padding //92
    }
    fin.close();
    return datos;  

}
//funcion 2
int Eliminar_Duplicados(Dato* datos, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; ) {
            if (datos[i].Id == datos[j].Id) {
                
                for (int k = j; k < n - 1; k++) {
                    datos[k] = datos[k + 1];
                }
                n--; 
                
            } else {
                j++;
            }
        }
    }
    return n; 
}

//funcion 3
void Agregar_Alumno ( Dato *& datos , Dato Alumno_nuevo ) {
cout<<"Ingrese los datos del estudiante:"<<endl;



//id
unsigned int id;
cout<<"ID ( NUmero mayor a 1500)"<<endl;
cin >> id;
if (id<=1500){
    cout<<"Id no valido"<<endl;
    return;
}
cin.ignore(1000, '\n');



//nombre
char nombre[50];
cout<<"Primer nombre y primer apellido :;"<<endl;
cin.getline(nombre,50);


//fecha
char fecha[11];
cout<<"Fecha de nacimiento ( formato YYYY/MM/DD ) :"<<endl;
cin.getline(fecha,11);

//3 notas
int n1,n2,n3;
cout<<"Notas de las 3 evaluaciones ( separadas por espacio ):"<<endl;
cin >> n1 >> n2 >> n3;
cin.ignore(1000, '\n');

//Curso
char curso[7];
cout<<"Sigla del curso ( ejemplo : INF134 ) :"<<endl;
cin.getline(curso,7);

//Veces tomado ramo
unsigned int vtr;
cout<<"VTR (1 -3) :"<<endl;
cin >> vtr;

//2fa
for (unsigned int i = 0; i < n_alumni; ++i) {
    if (datos[i].Id == id && strcmp(curso, datos[i].Curso) == 0) {
        cout << "Alumno ya ingresado en ese curso.";
        return;
    }
}

Alumno_nuevo.Id = id;
strncpy(Alumno_nuevo.Nombre, nombre, 49); Alumno_nuevo.Nombre[49] = '\0';
strncpy(Alumno_nuevo.Fecha_Nacimiento, fecha, 10); Alumno_nuevo.Fecha_Nacimiento[10] = '\0';
Alumno_nuevo.Notas[0] = n1; Alumno_nuevo.Notas[1] = n2; Alumno_nuevo.Notas[2] = n3;
strncpy(Alumno_nuevo.Curso, curso, 6); Alumno_nuevo.Curso[6] = '\0';
Alumno_nuevo.VTR = vtr;

Dato* crec = new Dato[n_alumni + 1];
for (unsigned int i = 0; i < n_alumni; ++i) crec[i] = datos[i];
crec[n_alumni] = Alumno_nuevo;

delete[] datos;
datos = crec;
n_alumni++;

cout << "Alumno agregado.";

};

//funcion 4
int Calcular_Promedio_Estudiante ( Dato * datos , unsigned int id_alumno , char
* asignatura_a_buscar ) {

    for (unsigned int i = 0; i < n_alumni; ++i) {
        if (datos[i].Id == id_alumno && strcmp(datos[i].Curso, asignatura_a_buscar) == 0) {
            int suma = datos[i].Notas[0] + datos[i].Notas[1] + datos[i].Notas[2];
            return suma / 3; 
        }
    }
    return -1; 
}




int main() {}    


