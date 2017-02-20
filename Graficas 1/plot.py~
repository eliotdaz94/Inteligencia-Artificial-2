# -*- coding: utf-8 -*-
import pandas
import numpy as np
import matplotlib.pyplot as plt
INGORAR_LINEAS = 33

def plotear(lr):
    string = "Curva Ajustada para predicción de peso corporal en funcion de peso del cerebro"
    c01 = pandas.read_table("x01_costo{}.txt".format(lr),header = 0 , delimiter = " ")
    f = c01.plot("Iteracion", "FuncionCosto", legend = False)
    f.set_title("{} {}".format(string,lr), fontsize=10)
    f.set_xlabel("Iteraciones")
    f.set_ylabel("Función de Costo")
    plt.tight_layout()
    plt.savefig("{}.png".format(lr))

def leer_input(fichero):
    resultado = []
    with open(fichero,"r") as file:
        for line in file.readlines()[INGORAR_LINEAS:-1]:
            columns = map(float,line.strip().split()[1:])
            resultado.append(list(columns))
    return resultado

def generar_df(in_matrix):
    df = pandas.DataFrame(in_matrix)
    df.columns = ["Peso del Cerebro", "Peso Corporal"]
    return df

def normalizar(data_frame):
    return (data_frame - data_frame.mean())/data_frame.std()
    
tabla = generar_df(leer_input("x01.txt"))
tabla = normalizar(tabla)
tabla.plot.scatter(0,1)
t = plt.gca()
t.set_title("Curva Ajustada a Datos sobre Peso.")

pesos = [8.46415e-006,0.934081]
pf = [-0.4,7]
r = [[1,-0.4],[1,7]]
a = [np.dot(a,pesos) for a in r]
plt.plot(pf,a,'r')
plt.savefig("Regresion.png")
for x in [0.1,1,2]:
    plotear(x)
