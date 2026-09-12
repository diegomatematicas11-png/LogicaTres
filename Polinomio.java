```java
import javax.swing.JOptionPane;

class Termino {
    float coeficiente;
    int exponente;
    Termino siguiente;

    public Termino(float coef, int exp) {
        coeficiente = coef;
        exponente = exp;
        siguiente = null;
    }
}

public class Polinomios {

    // Crear un nuevo término
    public static Termino crearNodo(float coef, int exp) {
        Termino nuevo = new Termino(coef, exp);
        return nuevo;
    }

    // Insertar un término
    public static Termino insertarTermino(Termino cabeza, float coef, int exp) {

        if (coef == 0) {
            return cabeza;
        }

        if (cabeza == null || exp > cabeza.exponente) {
            Termino nuevo = crearNodo(coef, exp);
            nuevo.siguiente = cabeza;
            return nuevo;
        }

        if (cabeza.exponente == exp) {
            cabeza.coeficiente = cabeza.coeficiente + coef;

            if (cabeza.coeficiente == 0) {
                return cabeza.siguiente;
            }

            return cabeza;
        }

        Termino actual = cabeza;

        while (actual.siguiente != null &&
               actual.siguiente.exponente > exp) {

            actual = actual.siguiente;
        }

        if (actual.siguiente != null &&
            actual.siguiente.exponente == exp) {

            actual.siguiente.coeficiente =
                    actual.siguiente.coeficiente + coef;

            if (actual.siguiente.coeficiente == 0) {
                actual.siguiente = actual.siguiente.siguiente;
            }

        } else {

            Termino nuevo = crearNodo(coef, exp);

            nuevo.siguiente = actual.siguiente;
            actual.siguiente = nuevo;
        }

        return cabeza;
    }

    // Imprimir polinomio
    public static void imprimirPolinomio(Termino cabeza) {

        if (cabeza == null) {
            System.out.println("0");
            return;
        }

        Termino actual = cabeza;
        boolean primero = true;

        while (actual != null) {

            float coef = actual.coeficiente;
            int exp = actual.exponente;

            if (primero) {

                if (coef < 0) {
                    System.out.print("-");
                }

                primero = false;

            } else {

                if (coef < 0) {
                    System.out.print(" - ");
                } else {
                    System.out.print(" + ");
                }
            }

            float absCoef = coef;

            if (absCoef < 0) {
                absCoef = absCoef * -1;
            }

            if (exp == 0) {
                System.out.print(absCoef);

            } else if (absCoef != 1) {
                System.out.print(absCoef);
            }

            if (exp == 1) {
                System.out.print("x");

            } else if (exp > 1) {
                System.out.print("x^" + exp);
            }

            actual = actual.siguiente;
        }

        System.out.println();
    }

    // Sumar polinomios
    public static Termino sumarPolinomios(Termino p1, Termino p2) {

        Termino resultado = null;

        Termino actual = p1;

        while (actual != null) {

            resultado = insertarTermino(
                    resultado,
                    actual.coeficiente,
                    actual.exponente
            );

            actual = actual.siguiente;
        }

        actual = p2;

        while (actual != null) {

            resultado = insertarTermino(
                    resultado,
                    actual.coeficiente,
                    actual.exponente
            );

            actual = actual.siguiente;
        }

        return resultado;
    }

    // Multiplicar polinomios
    public static Termino multiplicarPolinomios(Termino p1, Termino p2) {

        Termino resultado = null;

        Termino t1 = p1;

        while (t1 != null) {

            Termino t2 = p2;

            while (t2 != null) {

                float nuevoCoef =
                        t1.coeficiente * t2.coeficiente;

                int nuevoExp =
                        t1.exponente + t2.exponente;

                resultado = insertarTermino(
                        resultado,
                        nuevoCoef,
                        nuevoExp
                );

                t2 = t2.siguiente;
            }

            t1 = t1.siguiente;
        }

        return resultado;
    }

    // Evaluar polinomio
    public static float evaluarPolinomio(Termino cabeza, float x) {

        float resultado = 0;

        Termino actual = cabeza;

        while (actual != null) {

            float potencia = 1;

            // Calcular x elevado al exponente
            for (int i = 1; i <= actual.exponente; i++) {
                potencia = potencia * x;
            }

            resultado = resultado +
                    actual.coeficiente * potencia;

            actual = actual.siguiente;
        }

        return resultado;
    }

    // Derivar polinomio
    public static Termino derivarPolinomio(Termino cabeza) {

        Termino resultado = null;

        Termino actual = cabeza;

        while (actual != null) {

            if (actual.exponente != 0) {

                float nuevoCoef =
                        actual.coeficiente * actual.exponente;

                int nuevoExp =
                        actual.exponente - 1;

                resultado = insertarTermino(
                        resultado,
                        nuevoCoef,
                        nuevoExp
                );
            }

            actual = actual.siguiente;
        }

        return resultado;
    }

    // Contar términos
    public static int contarTerminos(Termino cabeza) {

        int contador = 0;

        Termino actual = cabeza;

        while (actual != null) {

            contador++;

            actual = actual.siguiente;
        }

        return contador;
    }

    // Obtener grado
    public static int gradoPolinomio(Termino cabeza) {

        if (cabeza == null) {
            return -1;
        }

        return cabeza.exponente;
    }

    public static void main(String[] args) {

        Termino polinomio1 = null;
        Termino polinomio2 = null;

        // Ejemplo de polinomio 1:
        // 3x^2 + 2x + 5
        polinomio1 = insertarTermino(polinomio1, 3, 2);
        polinomio1 = insertarTermino(polinomio1, 2, 1);
        polinomio1 = insertarTermino(polinomio1, 5, 0);

        // Ejemplo de polinomio 2:
        // 4x^2 + 3x + 1
        polinomio2 = insertarTermino(polinomio2, 4, 2);
        polinomio2 = insertarTermino(polinomio2, 3, 1);
        polinomio2 = insertarTermino(polinomio2, 1, 0);

        System.out.println("POLINOMIO 1:");
        imprimirPolinomio(polinomio1);

        System.out.println("POLINOMIO 2:");
        imprimirPolinomio(polinomio2);

        System.out.println();

        System.out.println("SUMA:");
        Termino suma = sumarPolinomios(polinomio1, polinomio2);
        imprimirPolinomio(suma);

        System.out.println();

        System.out.println("MULTIPLICACION:");
        Termino multiplicacion =
                multiplicarPolinomios(polinomio1, polinomio2);
        imprimirPolinomio(multiplicacion);

        System.out.println();

        float x = 2;

        System.out.println("EVALUACION EN x = " + x + ":");
        System.out.println(evaluarPolinomio(polinomio1, x));

        System.out.println();

        System.out.println("DERIVADA:");
        Termino derivada = derivarPolinomio(polinomio1);
        imprimirPolinomio(derivada);

        System.out.println();

        System.out.println("CANTIDAD DE TERMINOS:");
        System.out.println(contarTerminos(polinomio1));

        System.out.println();

        System.out.println("GRADO DEL POLINOMIO:");
        System.out.println(gradoPolinomio(polinomio1));
    }
}
```
