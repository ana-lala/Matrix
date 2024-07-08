/**
 * \file Matriz.hpp
 * \brief Implementaci&oacute;n de una matriz algebraica
 * \author Ana Laura Chenoweth Galaz
 * \date 02/02/2024
 */

#ifndef MATRIZ_HPP_INCLUDED
#define MATRIZ_HPP_INCLUDED

#include <iostream>

/** \class Matriz
 *
 * Permite manipular matrices y realizar diversas operaciones matriciales, incluyendo suma, resta, multiplicación,
 * multiplicación por un escalar, determinante, inversa, cofactores, transposición y redimensionamiento.
 *
 * \note Esta clase se diseñó para manejar matrices de tipo long double.
 *
 * Ejemplo de uso:
 * \code
    #include <iostream>
    #include "Matriz.hpp"

    int main() {
        try {
            cout << "Creando matrices!" << endl;
            Matriz v(3, 3), w(3, 3);

            cout << "\nCapturar las componentes de las matrices ..." << endl;
            cin >> v;
            cout << "Matriz v:" << endl;
            cout << v;
            cout << "Matriz w:" << endl;
            cin >> w;

            cout << "\nOperaciones con matrices:" << endl;
            Matriz suma = v + w;
            cout << v << " + " << w << " = " << suma << endl;
            Matriz resta = v - w;
            cout << v << " - " << w << " = " << resta << endl;
            Matriz multiplicacion = v * w;
            cout << v << " * " << w << " = " << multiplicacion << endl;
            Matriz multiplicacionEscalar = 2.5 * v;
            cout << v << " * " << 2.5 << " = " << multiplicacionEscalar << endl;
            Matriz inversa = v.Inversa();
            cout << "\nInversa de la matriz v:" << endl << inversa;

            cout << "\nRedimensiona la matriz:" << endl;
            int m, n;
            cout << "Renglones (3): ";
            cin >> m;
            cout << "Columnas (3): ";
            cin >> n;
            v.Redimensionar(m, n);
            cout << "\nMatriz v:" << endl << v;
            cout << "\nMatriz v redimensionada:" << v;

            Matriz transpuesta = v.Transpuesta();
            cout << "\nTranspuesta de la matriz v:" << endl << transpuesta;

        } catch (const char *msn) {
            cerr << "Error: " << msn << endl;
        } catch (...) {
            cerr << "Error inesperado " << endl;
        }

        return 0;
    }
 * \endcode
 *
\verbatim
    Salida:
    Creando matrices!

    Capturar las componentes de las matrices ...
    3 2
    7 5
    Matriz v:
    3
    2
    7
    5

    Matriz w:
    1
    0
    0
    1

    Operaciones con matrices:
    |3, 2|
    |7, 5|
    +
    |1, 0|
    |0, 1|
    =
    |4, 2|
    |7, 6|

    |3, 2|
    |7, 5|
    -
    |1, 0|
    |0, 1|
    =
    |2, 2|
    |7, 4|

    |3, 2|
    |7, 5|
    *
    |1, 0|
    |0, 1|
    =
    |3, 0|
    |0, 5|

    |3, 2|
    |7, 5|
    *
    2.5
    =
    |7.5, 5    |
    |17.5, 12.5|

    Inversa de la matriz v:
    |5   -2|
    |-7  3 |

    Redimensiona la matriz:
    Renglones (3): 1
    Columnas (3): 2

    Matriz v:
    |3   2|
    |7   5|

    Matriz v redimensionada:
    |3   2|

    Transpuesta de la matriz v:
    |3|
    |2|
\endverbatim

 *
 */


typedef long double tipo;

    enum{
        ESP =32,
        BV=179,
        ESD=191,
        EII,
        BH=196,
        EID=217,
        ESI};

class Matriz {
    /** \brief Función amiga para la sobrecarga del operador de inserción.
     *
     * Permite imprimir una matriz mediante un flujo de salida.
     *
     * \param out El flujo de salida.
     * \param v La matriz a imprimir.
     * \return El flujo de salida. Permite la aplicación en cascada del operador.
     *
     */
    friend std::ostream &operator<<(std::ostream &out, const Matriz &v);

    /** \brief Función amiga para la sobrecarga del operador de extracción.
     *
     * Permite capturar una matriz mediante un flujo de entrada.
     *
     * \param in El flujo de entrada.
     * \param v La matriz a capturar.
     * \return El flujo de entrada. Permite la aplicación en cascada del operador.
     *
     */
    friend std::istream &operator>>(std::istream &in, Matriz &v);

    /** \brief Función amiga para la sobrecarga del operador de multiplicación por escalar.
     *
     * Permite multiplicar una matriz por un escalar.
     *
     * \param escalar El número por el que se multiplica la matriz.
     * \param v La matriz a multiplicar.
     * \return La matriz resultante de la multiplicación por escalar.
     *
     */
    friend Matriz operator*(double escalar, const Matriz &v);


public:
    /** \brief Constructor.
     *
     *  Versión 1: Constructor de una matriz de 3x3 por omisión.
     *
     *  Versión 2: Constructor de una matriz de las dimensiones indicadas por \b m y \b n.
     *
     * \param m Número de filas de la matriz.
     * \param n Número de columnas de la matriz.
     *
     * \pre \b m y \b n deben ser números positivos.
     *
     * \exception const <b>char *</b> La matriz no puede ser creada o las dimensiones no son positivas.
     */
    explicit Matriz(int m = 3, int n = 3);

    /** \brief Constructor de copias.
     *
     * \param v La matriz a copiar.
     *
     * \exception const <b>char *</b> La matriz copia no puede ser creada.
     */
    Matriz(const Matriz &v);

    /** \brief Operador de asignación. Copia una matriz en otra matriz.
     *
     * \param v La matriz a copiar.
     * \return La matriz copia. Permite la aplicación en cascada del operador.
     *
     * \exception const <b>char *</b> La matriz copia no puede ser creada.
     */
    Matriz &operator=(const Matriz &v);

    /** \brief Destructor.
     *
     */
    ~Matriz();

    /** \brief Captura los elementos de una matriz por teclado.
     *
     */
    void Capturar();

    /** \brief Imprime una matriz en pantalla.
     *
     */
    void Imprimir() const;

    /** \brief Redimensiona una matriz.
     *
     * \param nuevo_m Nuevo número de filas.
     * \param nuevo_n Nuevo número de columnas.
     *
     * \pre \b nuevo_m y \b nuevo_n deben ser números positivos.
     *
     * \exception const <b>char *</b> La matriz no puede ser redimensionada o las dimensiones no son positivas.
     */
    void Redimensionar(unsigned int nuevo_m, unsigned int nuevo_n);

    /** \brief Obtiene el número de filas de una matriz.
     *
     * \return El número de filas de la matriz.
     *
     */
    int ObtenerNumRen() const;

    /** \brief Obtiene el número de columnas de una matriz.
     *
     * \return El número de columnas de la matriz.
     *
     */
    int ObtenerNumCol() const;

    // OPERACIONES

    /** \brief Operador para sumar dos matrices.
     *
     * \param v La matriz a sumar.
     * \return La matriz resultante de la suma.
     *
     * \pre Las matrices a sumar deben tener las mismas dimensiones.
     *
     * \exception const <b>char *</b> Las matrices a sumar tienen dimensiones incompatibles o la matriz resultante no puede ser creada.
     */
    Matriz operator+(const Matriz &v) const;

    /** \brief Operador para restar dos matrices.
     *
     * \param v La matriz a restar.
     * \return La matriz resultante de la resta.
     *
     * \pre Las matrices a restar deben tener las mismas dimensiones.
     *
     * \exception const <b>char *</b> Las matrices a restar tienen dimensiones incompatibles o la matriz resultante no puede ser creada.
     */
    Matriz operator-(const Matriz &v) const;

    /** \brief Operador para multiplicar dos matrices.
     *
     * \param v La matriz a multiplicar.
     * \return La matriz resultante de la multiplicación.
     *
     * \pre Las matrices a multiplicar deben tener las mismas dimensiones.
     *
     * \exception const <b>char *</b> Las matrices a multiplicar tienen dimensiones incompatibles o la matriz resultante no puede ser creada.
     */
    Matriz operator*(const Matriz &v) const;

    /** \brief Operador para multiplicar una matriz por un escalar.
     *
     * \param escalar El número por el que se multiplica la matriz.
     * \return La matriz resultante de la multiplicación por escalar.
     *
     * \exception const <b>char *</b> La matriz resultante no puede ser creada.
     */
    Matriz operator*(double escalar) const;

    /** \brief Calcula la transpuesta de una matriz.
     *
     * \return La matriz transpuesta.
     *
     */
    Matriz Transpuesta() const;

    /** \brief Calcula el determinante de una matriz.
     *
     * \return El determinante de la matriz.
     *
     * \exception const <b>char *</b> La matriz no es cuadrada o el determinante no puede ser calculado.
     */
    tipo Determinante() const;

    /** \brief Calcula la matriz de cofactores de una matriz.
     *
     * \return La matriz de cofactores.
     *
     * \exception const <b>char *</b> La matriz no es cuadrada o la matriz de cofactores no puede ser calculada.
     */
    Matriz Cofactores() const;

    /** \brief Calcula la matriz inversa de una matriz.
     *
     * \return La matriz inversa.
     *
     * \exception const <b>char *</b> La matriz no es cuadrada, singular o la matriz inversa no puede ser calculada.
     */
    Matriz Inversa() const;


private:
    unsigned int m, n;
    tipo **componente = NULL;
    void EstablecerDim(int m, int n);
};

#endif // MATRIZ_HPP_INCLUDED
