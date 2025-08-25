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




int main() {    
    Dato* datos = Leer_Archivo("datos.dat"); 
    if (!datos) return 0;                    

    
    for (int i = 0; i < 5; i++) {
        cout << "ID: " << datos[i].Id
            << "  Nombre: " << datos[i].Nombre
            << "  Fecha: " << datos[i].Fecha_Nacimiento
            << "  Curso: " << datos[i].Curso
            << "  VTR: " << datos[i].VTR << endl;
    }

    delete[] datos;
    return 0;
}

