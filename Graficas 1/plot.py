import pandas
import numpy as np
import matplotlib.pyplot as plt

def plotear(lr):
    string = "Curva de Convergencia para Datos sobre Peso con Tasa de Aprendizaje ="
    c01 = pandas.read_table("x01_costo{}.txt".format(lr),header = 0 , delimiter = " ")
    f = c01.plot("Iteracion", "FuncionCosto", legend = False)
    f.set_title("{} {}".format(string,lr), fontsize=10)
    f.set_ylabel("Iteracion")
    f.set_xlabel("Funcion Costo")
    plt.tight_layout()
    plt.savefig("{}.png".format(lr))

for x in [0.1,1,2]:
    plotear(x)
