import os
import csv
import seaborn as sn
import pandas as pd
import matplotlib.pyplot as plt

d = {}
r = csv.reader(open('distancias.txt'))
for x in r:
    d[(x[0], x[1])] = float(x[2])
claves = list(os.listdir('fuentes/'))
claves.remove('README.txt')

def weight(clave1):
    w = 0
    for clave2 in claves:
        w += d[(clave1, clave2)]
    return w / len(claves)

claves = sorted(claves, key=weight)

for c in sorted(claves):
    print(c, weight(c))


df_cm = pd.DataFrame([[d[(k1, k2)] for k2 in claves] for k1 in claves], claves, claves)
sn.set(font_scale=0.5) # label size
sn.heatmap(df_cm, annot=False) # font size
plt.savefig('distancias.pdf', bbox_inches='tight')

