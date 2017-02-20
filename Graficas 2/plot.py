import pandas
import numpy as np
import matplotlib.pyplot as plt

def combinar(lr):
    for x in lr:
        c01 = pandas.read_table("x08_{}.txt".format(x),header = 0 , delimiter = " ")
        c01 = c01.dropna()
        plt.plot(c01["Iteracion"], c01["FuncionCosto"], label = "{}".format(x))

    a = plt.gca() 
    a.set_ylabel("Función de Costo")
    a.set_xlabel("Iteraciones")   
    a.set_ylim([0,0.2])
    a.set_xlim([0,20])
    a.set_title("Curvas de Convergencia para Datos sobre Mortalidad con distintas Tasas de Aprendizaje.",fontsize = 10, y = 1.05)
    plt.tight_layout()
    plt.legend()
    plt.savefig("todos.png")

arreglo = [0.1,0.3,0.5,0.7,0.9,1,2]
combinar(arreglo)
