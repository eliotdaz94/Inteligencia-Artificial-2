import pandas
import numpy as np
import matplotlib.pyplot as plt

def combinar(lr):
    for x in lr:
        c01 = pandas.read_table("train01.txt",header = 0 , delimiter = " ")
        c01 = c01.dropna()
        plt.plot(c01["Iteracion"], c01["FuncionCosto"], label = "{}".format(x))

    a = plt.gca()   
    a.set_ylabel("Función de Costo")
    a.set_xlabel("Iteraciones")   
    #a.set_ylim([0,0.2])
    #a.set_xlim([0,20])
    a.set_title("Curvas de Convergencia para Datos sobre Precios de Casas con Tasa de Aprendizaje = 0.1.",fontsize = 10, y = 1.05)
    plt.tight_layout()
    plt.legend()
    plt.savefig("todos2.png")

arreglo = [0.1]
combinar(arreglo)
