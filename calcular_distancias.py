#!/usr/bin/python
import os

tabla = {}

def complejidad(fn):
    if fn in tabla:
        return tabla[fn]
    k = float(os.popen('./complexity {fn}'.format(fn=fn)).read())
    tabla[fn] = k
    return k

def complejidad_conjunta(fn1, fn2):
    if (fn1, fn2) in tabla:
        return tabla[(fn1, fn2)]
    os.system('rm -f TEMP.txt')
    os.system('cat {fn1} SEP.txt {fn2} > TEMP.txt'.format(fn1=fn1, fn2=fn2))
    k = float(os.popen('./complexity TEMP.txt').read())
    tabla[(fn1, fn2)] = k
    tabla[(fn2, fn1)] = k
    os.system('rm -f TEMP.txt')
    return k

def distancia(fn1, fn2):
    return complejidad_conjunta(fn1, fn2) / (complejidad(fn1) + complejidad(fn2))

if __name__ == '__main__':
    fuentes = os.listdir('fuentes')
    fuentes.remove('fuentes/README.txt')
    with open('distancias.txt', 'w') as f:
        for fn1 in fuentes:
            for fn2 in fuentes:
                d = distancia(os.path.join('fuentes', fn1), os.path.join('fuentes', fn2))
                print(fn1, fn2, d)
                f.write('{fn1},{fn2},{d}\n'.format(fn1=fn1, fn2=fn2, d=d))

