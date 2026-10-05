#include <iostream>
#include <string>
#include "F2.cpp"

using namespace std;

class PolF1
{
    string nombre;
    int n;
    int *vec;

public:
    PolF1(string nombre)
    {
        this->nombre = nombre;
        n = 1;
        vec = new int[1];
        vec[0] = -1;
    }

    PolF1(int x)
    {
        n = x;
        vec = new int[x];

        for (int i = 0; i < x; i++)
        {
            vec[i] = 0;
        }
    }

    PolF1(string nombre, int x)
    {
        this->nombre = nombre;
        n = x;
        vec = new int[x];

        for (int i = 0; i < x; i++)
        {
            vec[i] = 0;
        }
    }

    PolF1()
    {
        delete[] vec;
    }

    void redimensionar(int x)
    {
        int *aux;

        if (x > 0)
        {
            aux = new int[n + x];

            for (int i = 0; i < vec[0] + 2; i++)
            {
                aux[i] = vec[i];
            }

            n = n + x;

            delete[] vec;
            vec = aux;
        }
        else
        {
            if (n + x >= vec[0] + 2)
            {
                aux = new int[n + x];

                for (int i = 0; i < n + x; i++)
                {
                    aux[i] = vec[i];
                }

                n = n + x;

                delete[] vec;
                vec = aux;
            }
        }
    }

    int obtenerDato(int p)
    {
        return vec[p];
    }

    int obtenerN()
    {
        return n;
    }

    int obtenerGrado()
    {
        return vec[0];
    }

    void asignarDato(int p, int d)
    {
        vec[p] = d;
    }

    string toString()
    {
        string respuesta = nombre + " = ";
        int exp = 0;

        for (int i = 1; i < vec[0] + 2; i++)
        {
            exp = vec[0] + 1 - i;

            if (vec[i] >= 0)
            {
                respuesta = respuesta + "  +  " + to_string(vec[i]) + "X^" + to_string(exp);
            }
            else
            {
                respuesta = respuesta + "  -  " + to_string(vec[i] * (-1)) + "X^" + to_string(exp);
            }
        }

        return respuesta;
    }

    void ajustar()
    {
        int cont = 0;
        int i;

        if (vec[1] == 0)
        {
            i = 1;

            while (i < vec[0] + 2 && vec[i] == 0)
            {
                cont = cont + 1;
                i = i + 1;
            }

            for (int j = i; j < vec[0] + 2; j++)
            {
                vec[j - cont] = vec[j];
            }

            vec[0] = vec[0] - cont;
        }
    }

    void insertarTermino(int coe, int exp)
    {
        if (exp > vec[0])
        {
            int *aux;

            aux = new int[exp + 2];

            for (int i = 0; i < exp + 2; i++)
            {
                aux[i] = 0;
            }

            for (int i = 1; i < vec[0] + 2; i++)
            {
                aux[i + exp - vec[0]] = vec[i];
            }

            aux[0] = exp;
            aux[aux[0] + 1 - exp] = coe;

            delete[] vec;
            vec = aux;

            n = exp + 2;
        }
        else
        {
            int pos = vec[0] + 1 - exp;

            vec[pos] = vec[pos] + coe;

            ajustar();
        }
    }

    PolF1 multiplicar(PolF1 b)
    {
        PolF1 respuesta("Multiplicacion");

        for (int i = 1; i < vec[0] + 2; i++)
        {
            for (int j = 1; j < b.obtenerGrado() + 2; j++)
            {
                int coe = vec[i] * b.obtenerDato(j);

                int exp1 = vec[0] + 1 - i;
                int exp2 = b.obtenerGrado() + 1 - j;

                int exp = exp1 + exp2;

                if (coe != 0)
                {
                    respuesta.insertarTermino(coe, exp);
                }
            }
        }

        return respuesta;
    }

    PolF1 dividir(PolF1 b)
    {
        PolF1 respuesta("Division");

        PolF1 resto("Resto");

        for (int i = 1; i < vec[0] + 2; i++)
        {
            resto.insertarTermino(vec[i], vec[0] + 1 - i);
        }

        while (resto.obtenerGrado() >= b.obtenerGrado() &&
               resto.obtenerGrado() >= 0)
        {
            int exp = resto.obtenerGrado() - b.obtenerGrado();

            int coe = resto.obtenerDato(1) / b.obtenerDato(1);

            respuesta.insertarTermino(coe, exp);

            for (int i = 1; i < b.obtenerGrado() + 2; i++)
            {
                int expB = b.obtenerGrado() + 1 - i;

                int nuevoCoe = b.obtenerDato(i) * coe;

                resto.insertarTermino(-nuevoCoe, expB + exp);
            }
        }

        return respuesta;
    }

    bool sonIguales(PolF2 b)
    {
        if (vec[0] + 1 != b.obtenerGrado())
        {
            return false;
        }

        for (int i = 1; i < vec[0] + 2; i++)
        {
            int exp = vec[0] + 1 - i;
            bool encontro = false;

            for (int j = 1; j < b.obtenerGrado() * 2 + 1; j = j + 2)
            {
                if (exp == b.obtenerDato(j))
                {
                    if (vec[i] == b.obtenerDato(j + 1))
                    {
                        encontro = true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }

            if (encontro == false && vec[i] != 0)
            {
                return false;
            }
        }

        return true;
    }

    void insertar(int exp, int coe)
    {
        insertarTermino(coe, exp);
    }
};