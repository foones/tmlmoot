
.PHONY : all clean

all : distancias.txt distancias.pdf

complexity : complexity.cpp
	g++ -o complexity complexity.cpp

distancias.txt : calcular_distancias.py complexity
	python calcular_distancias.py

distancias.pdf : graficar.py distancias.txt 
	python graficar.py

