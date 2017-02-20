import pandas
import numpy as np
import matplotlib.pyplot as plt

def generar_df(name):
    continuos = ["Order","Lot Frontage","Lot Area","Mas Vnr Area","BsmtFin SF 1","BsmtFin SF 2",\
                 "Bsmt Unf SF", "Total Bsmt SF", "1st Flr SF","2nd Flr SF", "Low Qual Fin SF",\
                 "Gr Liv Area","Garage Area","Wood Deck SF","Open Porch SF","Enclosed Porch",\
                 "3Ssn Porch","Screen Porch","Pool Area","Misc Val","SalePrice"]
    df = pandas.read_table(name, header=0)
    df = df[df["Sale Condition"] == "Normal"]
    df = df[df["Gr Liv Area"] <= 1500]
    df = df.select_dtypes(exclude=[np.object])
    df = df[continuos]
    df = df.dropna()
    
    return df    

def generar_archivo(tab,nombre):
    with open("{}.txt".format(nombre),"w") as file:
        file.write("{} {}\n".format(tab.shape[1],tab.shape[0]))    
    tab.to_csv(r"{}.txt".format(nombre), header = False, sep=' ', mode='a', index = False)

tabla = generar_df("AmesHousing.txt")
entrenamiento = tabla.sample(frac = 0.8, random_state = 25)
validacion = tabla.drop(entrenamiento.index)

generar_archivo(tabla,"filtrado")
generar_archivo(entrenamiento, "entrenamiento")
generar_archivo(validacion, "validacion")
