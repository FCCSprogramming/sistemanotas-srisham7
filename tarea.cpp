#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//Estructuras requeridas (notas, curso, estudiante)
struct Notas {
    float EP;  // Examen Parcial (30%)
    float EF;  // Examen Final (50%)
    float PP;  // Promedio de Prácticas (20%)
};

// Función para calcular promedio final
float calcularPromedio(Notas n) {
    return n.EP * 0.3 + n.EF * 0.5 + n.PP * 0.2;
}

// Función para determinar estado
string obtenerEstado(Notas n) {
    float prom = calcularPromedio(n);
    if (prom >= 10.5) return "Aprobado";
    else return "Desaprobado";
}

// Estructra de curso
struct Curso {
    string codigo;
    string nombre;
    int creditos;
    string profesor;
    Notas notas;

    void mostrarInformacion(const Curso& c) {
        cout << "\nCódigo curso: " << c.codigo;
        cout << "\nNombre: " << c.nombre;
        cout << "\nCréditos: " << c.creditos;
        cout << "\nProfesor: " << c.profesor;
    }
};

// Estructura de estudiante
struct Estudiante {
    string codigo;
    string nombre;
    string carrera;
    int ciclo;
    Curso cursos[6];  // Máximo 6 cursos por estudiante
    int cantidadCursos;

    void mostrarDatos() {
        cout << "\nCódigo: " << codigo;
        cout << "\nNombre: " << nombre;
        cout << "\nCarrera: " << carrera;
        cout << "\nCiclo: " << ciclo;
        cout << "\nCantidad de cursos: " << cantidadCursos;
    }
};

//1.1 Gestión de Estudiantes
// Prototipos de funciones a implementar

//Registrar estudiante
void registrarEstudiante(Estudiante estudiantes[], int& cantidad) {
    cout << "\n===REGISTRAR ESTUDIANTE===\n";
    cout << "Código: ";
    cin >> estudiantes[cantidad].codigo;
    cin.ignore();  // Limpiar el buffer
    cout << "Nombre: ";
    getline(cin, estudiantes[cantidad].nombre);
    cout << "Carrera: ";
    getline(cin, estudiantes[cantidad].carrera);
    cout << "Ciclo: ";
    cin >> estudiantes[cantidad].ciclo;

    estudiantes[cantidad].cantidadCursos = 0; // Inicializar cantidad de cursos
    cantidad++; //Sumar al contador
}

// Mostrar estudiantes
void mostrarEstudiantes(const Estudiante estudiantes[], int cantidad) {
    if (cantidad == 0) {
        cout << "\nNo hay estudiantes registrados.\n";
        return;
    }

    //Mostrar Lista
    cout << "\n=== Lista de Estudiantes ===\n";
    for (int i = 0; i < cantidad; i++) {

        cout << "Estudiante " << i + 1 << ":\n";
        cout << "Código: " << estudiantes[i].codigo << endl;
        cout << "Nombre: " << estudiantes[i].nombre << endl;
        cout << "Carrera: " << estudiantes[i].carrera << endl;
        cout << "Ciclo: " << estudiantes[i].ciclo << endl;
        cout << "Cursos matriculados: " << estudiantes[i].cantidadCursos << endl;
    }
}

// Buscar estudiante por codigo
Estudiante* buscarEstudiante(Estudiante estudiantes[], int cantidad, string codigo) {
    for (int i = 0; i < cantidad; i++) {
        if (estudiantes[i].codigo == codigo) {
            return &estudiantes[i];  // devuelve puntero al estudiante encontrado
        }
    }
    return nullptr;
}

//1.2 Gestión de Cursos por Estudiante
void matricularCurso(Estudiante& estudiante) {
    cout << "\n=== MATRICULAR CURSO ===\n";
    cout << "Estudiante: " << estudiante.codigo << " - " << estudiante.nombre<<"\n";

    Curso& c = estudiante.cursos[estudiante.cantidadCursos];

    cout << "Código curso: ";
    cin >> c.codigo;
    getline(cin, c.codigo);

    cout << "Nombre: ";
    getline(cin, c.nombre);

    cout << "Créditos: ";
    cin >> c.creditos;
    cin.ignore();

    cout << "Profesor: ";
    getline(cin, c.profesor);

    estudiante.cantidadCursos++;
}

void ingresarNotas(Estudiante& estudiante) {
    cout << "\n=== INGRESAR NOTAS ===\n";
    for (int i = 0; i < estudiante.cantidadCursos; i++) {
        Curso& c = estudiante.cursos[i];
        cout << "Curso: " << c.codigo << " - " << c.nombre << endl;

        cout << "Examen Parcial: ";
        cin >> c.notas.EP;
        cout << "Examen Final: ";
        cin >> c.notas.EF;
        cout << "Promedio de Prácticas: ";
        cin >> c.notas.PP;

    }
}

void mostrarCursosEstudiante(const Estudiante& estudiante) {
    if (estudiante.cantidadCursos == 0) {
        cout << "\nEl estudiante no tiene cursos matriculados.\n";
        return;
    }

    cout << "\n=== REPORTE DE CURSOS ===\n";
    cout << "Estudiante: " << estudiante.codigo << " - " << estudiante.nombre << "\n\n";

    cout << left << setw(10) << "Código" << setw(25) << "Curso"
        << setw(10) << "Créditos" << setw(10) << "EP"
        << setw(10) << "EF" << setw(10) << "PP"
        << setw(10) << "Promedio" << "Estado\n";

    for (int i = 0; i < estudiante.cantidadCursos; i++) {
        const Curso& c = estudiante.cursos[i];
        float prom = calcularPromedio(c.notas);
        string estado = obtenerEstado(c.notas);

        cout << left << setw(10) << c.codigo
            << setw(25) << c.nombre
            << setw(10) << c.creditos
            << setw(10) << c.notas.EP
            << setw(10) << c.notas.EF
            << setw(10) << c.notas.PP
            << setw(10) << prom << estado << endl;
    }
}

//Funciones Avanzadas
//2.1 Calculos Académicos

// Calcular promedio ponderado
float calcularPromedioPonderado(const Estudiante& estudiante) {
    if (estudiante.cantidadCursos == 0) return 0; // evita división entre 0

    float suma = 0;
    int creditos = 0;

    for (int i = 0; i < estudiante.cantidadCursos; i++) {
        float prom = calcularPromedio(estudiante.cursos[i].notas);

        suma += prom * estudiante.cursos[i].creditos;
        creditos += estudiante.cursos[i].creditos;
    }

    if (creditos == 0) return 0; // seguridad
    return suma / creditos;
}

// Calcular total de creditos
int calcularTotalCreditos(const Estudiante& estudiante) {
    int total = 0;
    for (int i = 0; i < estudiante.cantidadCursos; i++) {
        total += estudiante.cursos[i].creditos;  // Sumar creditos
    }
    return total;
}

void generarBoleta(const Estudiante& estudiante) {
    cout << "\n=== BOLETA DE NOTAS ===\n";
    cout << "Estudiante: " << estudiante.nombre << " (" << estudiante.codigo << ")\n";
    cout << "Carrera: " << estudiante.carrera << " - Ciclo: " << estudiante.ciclo << "\n\n";

    mostrarCursosEstudiante(estudiante);

    // Mostrar promedio ponderado y créditos totales
    float promedioPonderado = calcularPromedioPonderado(estudiante);
    int totalCreditos = calcularTotalCreditos(estudiante);

    cout << "\nPromedio Ponderado: " << fixed << setprecision(2) << promedioPonderado << endl;
    cout << "Total Créditos: " << totalCreditos << endl;
}

//2.2 Reportes del Sistema

// Mejr promedio
void mostrarMejorPromedio(const Estudiante estudiantes[], int cantidad) {
    if (cantidad == 0) { 
        cout << "\nNo hay estudiantes registrados.";
        return;
    }
    int mejor = 0; 
    float promMax = calcularPromedioPonderado(estudiantes[0]);
    for (int i = 1; i < cantidad; i++) {
        float p = calcularPromedioPonderado(estudiantes[i]); // calcular promedio ponderado
        if (p > promMax) { promMax = p; mejor = i; }
    }
    cout << "\nEstudiante con mejor promedio:\n";
    generarBoleta(estudiantes[mejor]); // Mostrar boleta mejor estudiante
}

//Estudiantes aprobados
void estudiantesAprobadosCurso(const Estudiante estudiantes[], int cantidad, string codigoCurso) {
    cout << "\n=== ESTUDIANTES APROBADOS EN CURSO\n" << codigoCurso << " ===\n";
    bool encontrado = false;

    for (int i = 0; i < cantidad; i++) {
        for (int j = 0; j < estudiantes[i].cantidadCursos; j++) {
            const Curso& c = estudiantes[i].cursos[j];
            if (c.codigo == codigoCurso) {
                float promedio = calcularPromedio(c.notas);
                string estado = obtenerEstado(c.notas);

                if (estado == "Aprobado") {
                    cout << " - " << estudiantes[i].nombre << " (" << estudiantes[i].codigo << ") | Promedio: "
                        << fixed << setprecision(2) << promedio << endl;
                    encontrado = true;
                }
            }
        }
    }

    if (!encontrado) {
        cout << "No se encontraron estudiantes en el curso.\n";
    }

}

//Reporte General
void reporteGeneral(const Estudiante estudiantes[], int cantidad) {
    cout << "\n=== REPORTE GENERAL ===\n";
    for (int i = 0; i < cantidad; i++) {
        const Estudiante& est = estudiantes[i];
        float promedioPonderado = calcularPromedioPonderado(est);
        int totalCreditos = calcularTotalCreditos(est);

        cout << "Estudiante: " << est.nombre << " (" << est.codigo << ")\n";
        cout << "Carrera: " << est.carrera << " - Ciclo: " << est.ciclo << "\n";
        cout << "Promedio Ponderado: " << fixed << setprecision(2) << promedioPonderado << "\n";
        cout << "Total Créditos: " << totalCreditos << "\n";
    }
}


int main() {
    Estudiante estudiantes[50];
    int cantidad = 0;
    int opcion;
    string codigo;

    cout << "\n=== SISTEMA DE GESTIÓN ACADÉMICA UNI ===\n";
    cout << "\n1. Registrar estudiante \n2. Matricular curso a estudiante ";
    cout << "\n3. Ingresar notas de curso \n4. Mostrar información de estudiante \n5. Generar boleta de notas";
    cout << "\n6. Mostrar mejor promedio \n7. Estudiantes aprobados por curso \n8. Reporte general \n9. Salir\n";
    cin >> opcion;
    cin.ignore();

    //Menú principal
    while (opcion != 9) {
        switch (opcion) {
        case 1:
            registrarEstudiante(estudiantes, cantidad);
            break;
        case 2:
            cout << "Ingrese código de estudiante: ";
            cin >> codigo;
            {
                Estudiante* est = buscarEstudiante(estudiantes, cantidad, codigo);
                if (est) {
                    matricularCurso(*est);
                }
                else {
                    cout << "Estudiante no encontrado.\n";
                }
            }
            break;
        case 3:
            cout << "Ingrese código de estudiante: ";
            cin >> codigo;
            {
                Estudiante* est = buscarEstudiante(estudiantes, cantidad, codigo);
                if (est) {
                    ingresarNotas(*est);
                }
                else {
                    cout << "Estudiante no encontrado.\n";
                }
            }
            break;
        case 4:
            mostrarEstudiantes(estudiantes, cantidad);
            break;
        case 5:
            cout << "Ingrese código de estudiante: ";
            cin >> codigo;
            {
                Estudiante* est = buscarEstudiante(estudiantes, cantidad, codigo);
                if (est) {
                    generarBoleta(*est);
                }
                else {
                    cout << "Estudiante no encontrado.\n";
                }
            }
            break;
        case 6:
            mostrarMejorPromedio(estudiantes, cantidad);
            break;
        case 7:
            cout << "Ingrese código de curso: ";
            cin >> codigo;
            estudiantesAprobadosCurso(estudiantes, cantidad, codigo);
            break;
        case 8:
            reporteGeneral(estudiantes, cantidad);
            break;
        default:
            cout << "Opción no válida.\n";
        }

        cout << "\nIngrese otra opción: ";
        cin >> opcion;
    }
}