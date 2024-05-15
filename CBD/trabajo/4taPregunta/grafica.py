import matplotlib.pyplot as plt
import pandas as pd

df= pd.read_csv("salida.csv")
# Datos
year = df["year"]
cantidad = df["cantidad"]

# Crear la gráfica
plt.plot(year, cantidad, marker='o', linestyle='-')

# Etiquetas y título
plt.xlabel('Eje year')
plt.ylabel('Eje cantidad')
plt.title('Gráfica Lineal')

# Mostrar la gráfica
plt.grid(True)
plt.show()
