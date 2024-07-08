#include <math.h>
#include <iomanip>
#include <cstring>
#include <cmath>

#include "Matriz.hpp"


using std::cout;
using std::cin;
using std::endl;
using std::left;
using std::fixed;
using std::setprecision;

//***************************************************
void Matriz::EstablecerDim(int m, int n)
{
    if (m < 1 || n < 1)throw "Valor fuera de rango";
    this->n = n;
    this->m = m;
}

//***********************************
//Constructor
Matriz::Matriz(int m, int n) {
    EstablecerDim(m, n);
    try {
        componente = new tipo*[m];
        componente[0] = new tipo[m * n];
        for (int i = 1; i < m; ++i)
            componente[i] = componente[0] + i * n;

        // Inicializar la matriz con ceros
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                componente[i][j] = 0;
            }
        }
    } catch(std::bad_alloc &) {
        throw "No es posible construir una Matriz";
    }
}

//***********************************
// Constructor de copia
Matriz::Matriz(const Matriz &v) : m(v.m), n(v.n), componente(nullptr) {
    try {
        componente = new tipo*[m];
        componente[0] = new tipo[m * n];
        for (unsigned int i = 1; i < m; ++i)
            componente[i] = componente[0] + i * n;

        // Copiar los elementos de v a la matriz actual
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                componente[i][j] = v.componente[i][j];
            }
        }
    } catch(std::bad_alloc &) {
        throw "No es posible construir una Matriz";
    }
}
//***********************************
// Operador de asignación
Matriz & Matriz::operator=(const Matriz &v) {
    if (this == &v) return *this;
    try {
        delete[] componente[0];
        delete[] componente;
        componente = nullptr;

        m = v.m;
        n = v.n;

        componente = new tipo*[m];
        componente[0] = new tipo[m * n];
        for (unsigned int i = 1; i < m; ++i) {
            componente[i] = componente[0] + i * n;
        }

        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                componente[i][j] = v.componente[i][j];
            }
        }
    } catch (std::bad_alloc &) {
        throw "No es posible construir una Matriz";
    }

    return *this;
}
//***********************************
// Destructor
Matriz::~Matriz() {
        delete[] componente[0];
        delete[] componente;
        componente = nullptr;
}

//***********************************
void Matriz::Capturar()
{
    for(unsigned int i = 0 ; i < m ; ++i){
        for(unsigned int j = 0; j<n; ++j){
                    cin >> componente[i][j];
        }
    }

}
//***********************************
void Matriz::Imprimir() const
{
    cout << left;
    cout << char(ESI);
    for(unsigned int j = 0; j < n ; ++j) cout << "\t";
    cout << char(ESD) << endl;

    for(unsigned int i = 0 ; i < m ; ++i){
        cout << char(BV);
        for(unsigned int j = 0; j < n ; ++j) {
            if (componente[i][j] - static_cast<int>(componente[i][j]) !=0 || componente[i][j] - round(componente[i][j]) !=0 ) {
                cout << fixed << setprecision(2) << componente[i][j] << "\t" ;
            } else {
                cout << componente[i][j] << "\t" ;
            }
        }
        cout << char(BV);
        cout << endl;
    }

    cout  << char(EII);
    for(unsigned int j = 0; j < n ; ++j) cout << "\t";
    cout << char(EID);

    cout << endl << endl;
}
//***********************************
int Matriz::ObtenerNumRen() const
{
    return m;
}
//***********************************
int Matriz::ObtenerNumCol() const
{
    return n;
}
//*******************************************************************
void Matriz::Redimensionar(unsigned int nuevo_m, unsigned int nuevo_n)
{
    if (nuevo_m < 1 || nuevo_n < 1) {
        throw "Valor fuera de rango para las dimensiones de la matriz";
    }
    if (nuevo_m == m && nuevo_n == n) {
        return;
    }
    try {
        tipo** nueva_componente = new tipo*[nuevo_m];
        nueva_componente[0] = new tipo[nuevo_m * nuevo_n];
        for (unsigned int i = 1; i < nuevo_m; ++i) {
            nueva_componente[i] = nueva_componente[0] + i * nuevo_n;
        }

        for (unsigned int i = 0; i < nuevo_m; ++i) {
            for (unsigned int j = 0; j < nuevo_n; ++j) {
                nueva_componente[i][j] = 0;
            }
        }
        // Copiar los valores de la matriz original que siguen siendo válidos
        for (unsigned int i = 0; i < std::min(m, nuevo_m); ++i) {
            for (unsigned int j = 0; j < std::min(n, nuevo_n); ++j) {
                nueva_componente[i][j] = componente[i][j];
            }
        }

        // Liberar la memoria de la matriz original
        delete[] componente[0];
        delete[] componente;

        // Asignar la nueva matriz redimensionada
        componente = nueva_componente;
        m = nuevo_m;
        n = nuevo_n;

    } catch (std::bad_alloc &) {
        throw "No es posible construir una Matriz";
    }
}


//***************************************************************************

/* OPERACIONES CON MATRICES */
//***********************************
Matriz Matriz::operator+(const Matriz &v) const
{
    if (m != v.m || n != v.n)
        throw "Dimensiones incompatibles para sumar";

    Matriz s(m, n);

    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            s.componente[i][j] = componente[i][j] + v.componente[i][j];
        }
    }

    return s;
}
//***********************************
Matriz Matriz::operator-(const Matriz &v) const
{
    if (m != v.m || n != v.n)
        throw "Dimensiones incompatibles para sumar";

    Matriz s(m, n);

    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            s.componente[i][j] = componente[i][j] - v.componente[i][j];
        }
    }

    return s;
}
//***********************************
Matriz Matriz::operator*(const Matriz &v) const
{
    if (m != v.m || n != v.n)
        throw "Dimensiones incompatibles para sumar";

    Matriz s(m, n);

    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            s.componente[i][j] = componente[i][j] * v.componente[i][j];
        }
    }

    return s;
}
//***********************************
Matriz Matriz::operator*(double escalar) const
{
    Matriz s(m, n);
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            s.componente[i][j] = componente[i][j] * escalar;
        }
    }

    return s;
}
//******************************************************************************
Matriz Matriz::Transpuesta() const
{
    Matriz s(n, m); // Crear una matriz con dimensiones transpuestas (n, m)
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            s.componente[j][i] = componente[i][j]; // Asignar elementos transpuestos
        }
    }
    return s;
}
//******************************************************************************
tipo Matriz::Determinante() const
{
    if(n!=m) throw "Dimensiones incorrectas para el determinanate";
    if (n == 1) {
        return componente[0][0];
    } else {
        tipo det = 0;
        Matriz submatriz(n - 1, n - 1);

        for (unsigned int i = 0; i < n; ++i) {
            // Obtiene la submatriz eliminando la primera fila y la columna i
            int submatriz_fila = 0;
            for (unsigned int j = 1; j < n; ++j) {
                int submatriz_columna = 0;
                for (unsigned int k = 0; k < n; ++k) {
                    if (k != i) {
                        submatriz.componente[submatriz_fila][submatriz_columna] = componente[j][k];
                        ++submatriz_columna;
                    }
                }
                ++submatriz_fila;
            }

            // Calcula el cofactor como el determinante de la submatriz con signo alternante
            int signo = (i % 2 == 0) ? 1 : -1;
            tipo cofactor = submatriz.Determinante();
            det += signo * componente[0][i] * cofactor;
        }
        return det;
    }

}
//******************************************************************************
Matriz Matriz::Cofactores() const
{
    if(n!=m) throw "Dimensiones incorrectas para el la matriz de cofactores";
    Matriz cofactores(n, n);
    Matriz submatriz(n-1, n-1);
        for (unsigned int i = 0; i < n; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            int submatriz_fila = 0;
            for (unsigned int k = 0; k < n; ++k) {
                if (k != i) {
                    int submatriz_columna = 0;
                    for (unsigned int l = 0; l < n; ++l) {
                        if (l != j) {
                            submatriz.componente[submatriz_fila][submatriz_columna] = componente[k][l];
                            ++submatriz_columna;
                        }
                    }
                    ++submatriz_fila;
                }
            }

            // Calcula el cofactor como el determinante de la submatriz con signo alternante
            int signo = (i + j) % 2 == 0 ? 1 : -1;
            cofactores.componente[i][j] = signo * submatriz.Determinante();
        }
    }
    return cofactores;
}
//******************************************************************************
Matriz Matriz::Inversa() const
{
    if(n!=m) throw "Dimensiones incorrectas para el la matriz inversa";
    Matriz inversa(n, n);
    tipo determinante = this->Determinante();

    if (abs(determinante) < 1e-10) {
        throw "No existe la inversa de esta matriz";
    }

    Matriz cofactores(n, n);
    cofactores = this->Cofactores();

    for (unsigned int i = 0; i < n; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            inversa.componente[i][j] = cofactores.componente[j][i] / determinante;
        }
    }

    return inversa;

}


/* FUNCIONES EXTERNAS*/
//*****************************************************************
std::ostream & operator<<(std::ostream &out,const Matriz &v)
{
    out << left;
    out << char(ESI);
    for(unsigned int j = 0; j < v.n ; ++j) out << "\t";
    out << char(ESD) << endl;

    for(unsigned int i = 0 ; i < v.m ; ++i){
        out << char(BV);
        for(unsigned int j = 0; j < v.n ; ++j) {
            if (v.componente[i][j] - static_cast<int>(v.componente[i][j]) !=0 || v.componente[i][j] - round(v.componente[i][j]) !=0 ) {
                out << fixed << setprecision(2) << v.componente[i][j] << "\t" ;
            } else {
                out << v.componente[i][j] << "\t" ;
            }
        }
        out << char(BV);
        out << endl;
    }

    out  << char(EII);
    for(unsigned int j = 0; j < v.n ; ++j) out << "\t";
    out << char(EID);

    out << endl << endl;

    return out;
}
//**************************************************************
std::istream & operator>>(std::istream &in,Matriz &v)
{
    for(unsigned int i = 0 ; i < v.m ; ++i){
        for(unsigned int j = 0; j<v.n; ++j){
                    in >>v.componente[i][j];
        }
    }
    return in;
}
//*************************************************************
Matriz operator*(double escalar, const Matriz &v)
{
    Matriz s(v.m, v.n);
    for (unsigned int i = 0; i < v.m; i++) {
        for (unsigned int j = 0; j < v.n; j++) {
            s.componente[i][j] = escalar * v.componente[i][j];
        }
    }

    return s;
}

