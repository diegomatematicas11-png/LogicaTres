#include <iostream>
#include <string>
#include "F1.cpp"

using namespace std;

class PolF2
{
    string nombre;
    int n;
    int *vec;

public:

    PolF2(string nombre)
    {
        this->nombre = nombre;
        n = 1;
        vec = new int[1];
        vec[0] = 0;
    }

    void redimensionar(int x)
    {
        int *aux;

        if(x > 0)
        {
            aux = new int[n + x];

            for(int i = 0; i < vec[0] * 2 + 1; i++)
            {
                aux[i] = vec[i];
            }

            n = n + x;

            delete[] vec;
            vec = aux;
        }
        else
        {
            if(n + x >= vec[0] * 2 + 1)
            {
                aux = new int[n + x];

                for(int i = 0; i < n + x; i++)
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

    void insertarTermino(int coe, int exp)
    {
        int i = 1;

        while(i < vec[0] * 2 + 1 && vec[i] > exp)
        {
            i = i + 2;
        }

        if(i < vec[0] * 2 + 1 && vec[i] == exp)
        {
            int suma = vec[i + 1] + coe;

            if(suma != 0)
            {
                vec[i + 1] = suma;
            }
            else
            {
                for(int j = i + 2; j < vec[0] * 2 + 1; j++)
                {
                    vec[j - 2] = vec[j];
                }

                vec[0] = vec[0] - 1;
                redimensionar(-2);
            }
        }
        else
        {
            redimensionar(2);

            for(int j = vec[0] * 2; j >= i; j--)
            {
                vec[j + 2] = vec[j];
            }

            vec[i] = exp;
            vec[i + 1] = coe;
            vec[0] = vec[0] + 1;
        }
    }

    PolF2 multiplicar(PolF2 b)
    {
        PolF2 respuesta("Multiplicacion");

        for(int i = 1; i < vec[0] * 2 + 1; i = i + 2)
        {
            for(int j = 1; j < b.obtenerGrado() * 2 + 1; j = j + 2)
            {
                int coe = vec[i + 1] * b.obtenerDato(j + 1);
                int exp = vec[i] + b.obtenerDato(j);

                if(coe != 0)
                {
                    respuesta.insertarTermino(coe, exp);
                }
            }
        }

        return respuesta;
    }

    PolF2 dividir(PolF2 b)
    {
        PolF2 respuesta("Division");

        PolF2 resto("Resto");

        for(int i = 1; i < vec[0] * 2 + 1; i = i + 2)
        {
            resto.insertarTermino(vec[i + 1], vec[i]);
        }

        while(resto.obtenerGrado() > 0 &&
              resto.obtenerDato(1) >= b.obtenerDato(1))
        {
            int exp = resto.obtenerDato(1) - b.obtenerDato(1);

            int coe = resto.obtenerDato(2) / b.obtenerDato(2);

            respuesta.insertarTermino(coe, exp);

            for(int i = 1; i < b.obtenerGrado() * 2 + 1; i = i + 2)
            {
                int expB = b.obtenerDato(i);
                int coeB = b.obtenerDato(i + 1);

                resto.insertarTermino(-(coe * coeB), expB + exp);
            }
        }

        return respuesta;
    }

    bool sonIguales(PolF2 b)
    {
        if(vec[0] != b.obtenerGrado())
        {
            return false;
        }

        for(int i = 1; i < vec[0] * 2 + 1; i++)
        {
            if(vec[i] != b.obtenerDato(i))
            {
                return false;
            }
        }

        return true;
    }

    PolF1 multiplicarPolF1(PolF2 b)
    {
        PolF1 resultado("Multiplicacion");

        for(int i = 1; i < vec[0] * 2 + 1; i = i + 2)
        {
            int exp1 = vec[i];
            int coe1 = vec[i + 1];

            for(int j = 1; j < b.vec[0] * 2 + 1; j = j + 2)
            {
                int exp2 = b.vec[j];
                int coe2 = b.vec[j + 1];

                resultado.insertarTermino(coe1 * coe2, exp1 + exp2);
            }
        }

        return resultado;
    }
};