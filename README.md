-- tmlmoot v.0.01 --

Uso:

1) Ubicar en la carpeta fuentes/ todos los archivos que se desea evaluar.
Por ejemplo:
  fuentes/01.txt
  fuentes/02.txt
  fuentes/03.txt

2) Compilar complexity.cpp
  $ g++ -o complexity complexity.cpp
Esto implementa el algoritmo que aproxima la complejidad descriptiva de un
archivo usando suffix arrays.

3) Calcular las distancias dos a dos entre archivos:
  $ python calcular_distancias.py
Esto genera un archivo distancias.txt con una estimación de la distancia
entre los archivos fuente. La noción de distancia está basada en la noción
de complejidad anterior.

4) Graficar la matriz de distancias:
  $ python graficar.py

