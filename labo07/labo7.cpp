#include <iostream>
#include <fstream>


using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void burbuja(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int contarNumeros(const string &nombreArchivo) {
    ifstream entrada(nombreArchivo); 
    int n, contador = 0;
    if (entrada.is_open()) {
        while (entrada >> n) {
            contador++;
        }
        entrada.close();
    }
    return contador;
}

void mostrarArchivo(const string &nombreArchivo) {
    ifstream entrada(nombreArchivo);
    int n;
    cout << "\n Contenido de " << nombreArchivo ;
    if (entrada.is_open()) {
        bool archivoVacio = true;
        while (entrada >> n) {
            cout << n << endl;
            archivoVacio = false;
        }
        entrada.close();
        if (archivoVacio) {
             cout << "Archivo vacio o no existe.\n";
        }
    } else {
        cout << "ERROR: El archivo " << nombreArchivo << " no pudo ser abierto o no existe.\n";
    }
}

void crearArchivoOrigen(const string &nombreArchivo) {
    ofstream salida(nombreArchivo);
    if (salida.is_open()) {
        cout << "\nSe ha creado o sobrescrito " << nombreArchivo << " con datos de prueba:\n";
        salida << 5 << endl;
        salida << 12 << endl;
        salida << 3 << endl;
        salida << 8 << endl;
        salida << 21 << endl;
        salida << 10 << endl;
        salida.close();
        cout << "Datos de prueba escritos correctamente.\n";
    } else {
        cout << "ERROR CRITICO: No se pudo crear el archivo " << nombreArchivo << ".\n";
    }
}

void clasificarNumeros(const string &archivoEntrada, const string &archivoPares, const string &archivoImpares) {
    ifstream entrada(archivoEntrada);
    ofstream pares(archivoPares), impares(archivoImpares); 
    int n;

    if (!entrada.is_open()) {
        cout << "ERROR: No se pudo abrir " << archivoEntrada << ". Asegurese de haberlo creado (Opcion 0).\n";
        return;
    }

    while (entrada >> n) {
        if (n % 2 == 0) {
            pares << n << endl;
        } else {
            impares << n << endl;
        }
    }

    entrada.close();
    pares.close();
    impares.close();
    cout << "COMPLETADO: Numeros clasificados correctamente en " << archivoPares << " y " << archivoImpares << ".\n";
}

void ordenarArchivo(const string &nombreArchivo) {
    int num_elementos = contarNumeros(nombreArchivo);

    if (num_elementos <= 1) { 
        cout << "ADVERTENCIA: El archivo " << nombreArchivo << " esta vacio o ya ordenado. Se omite.\n";
        return;
    }

    int *numeros = new (std::nothrow) int[num_elementos]; 
    if (numeros == nullptr) {
        cout << "ERROR DE MEMORIA: Fallo la asignacion dinamica para el archivo " << nombreArchivo << ".\n";
        return;
    }
    
    ifstream entrada(nombreArchivo);
    if (entrada.is_open()) {
        for (int i = 0; i < num_elementos; i++) {
            if (!(entrada >> numeros[i])) { 
                cout << "ERROR DE LECTURA: Fallo al leer el elemento " << i + 1 << " de " << nombreArchivo << ".\n";
                entrada.close();
                delete[] numeros;
                return;
            }
        }
        entrada.close();
    } else {
        cout << "ERROR: No se pudo abrir " << nombreArchivo << " para lectura.\n";
        delete[] numeros;
        return;
    }

    burbuja(numeros, num_elementos);

    ofstream salida(nombreArchivo);
    if (salida.is_open()) {
        for (int i = 0; i < num_elementos; i++) {
            salida << numeros[i] << endl;
        }
        salida.close();
    } else {
        cout << "ERROR: No se pudo abrir " << nombreArchivo << " para escritura.\n";
    }
    
    delete[] numeros; 

    cout << "COMPLETADO: Archivo " << nombreArchivo << " ordenado correctamente.\n";
}

int main() {
    const string ARCHIVO_ORIGEN = "datos.txt";
    const string ARCHIVO_PARES = "pares.txt";
    const string ARCHIVO_IMPARES = "impares.txt";
    int opcion;
    bool clasificado = false;

    cout << "Clasificador y Ordenador de numeros \n";
   

    do {
        cout << "\n MENU PRINCIPAL \n";
        cout << "0. Crear/Resetear " << ARCHIVO_ORIGEN << " con datos de prueba.\n";
        cout << "1. Clasificar numeros\n";
        cout << "2. Ordenar archivos\n";
        cout << "3. Ver resultados\n";
        cout << "9. Salir\n";
        cout << "Elige una opcion: ";
        
        if (!(cin >> opcion)) {
             cout << "\nEntrada invalida. Limpiando buffer y saliendo.\n";
             cin.clear();
             while (cin.get() != '\n');
             opcion = 9;
             break;
        }

        switch (opcion) {
            case 0:
                crearArchivoOrigen(ARCHIVO_ORIGEN);
                clasificado = false; 
                break;
            case 1:
                clasificarNumeros(ARCHIVO_ORIGEN, ARCHIVO_PARES, ARCHIVO_IMPARES);
                clasificado = true;
                break;
            case 2:
                if (clasificado) {
                    cout << "\n Antes del ordenamiento \n";
                    mostrarArchivo(ARCHIVO_PARES);
                    mostrarArchivo(ARCHIVO_IMPARES);
                    
                    cout << "\n Procesando Ordenamiento \n";
                    ordenarArchivo(ARCHIVO_PARES);
                    ordenarArchivo(ARCHIVO_IMPARES);
                    
                    cout << "\n Despues del ordenamiento \n";
                    mostrarArchivo(ARCHIVO_PARES);
                    mostrarArchivo(ARCHIVO_IMPARES);
                    
                } else {
                    cout << "ERROR: Primero debes clasificar los numeros (Opcion 1).\n";
                }
                break;
            case 3:
                cout << "\n Mostrando Resultados \n";
                mostrarArchivo(ARCHIVO_ORIGEN);
                mostrarArchivo(ARCHIVO_PARES);
                mostrarArchivo(ARCHIVO_IMPARES);
                break;
            case 9:
                cout << "Saliendo del programa. Adios.\n";
                break;
            default:
                cout << "Opcion no valida. Intenta de nuevo.\n";
        }
    } while (opcion != 9);

    return 0;
}