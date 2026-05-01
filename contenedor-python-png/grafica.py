import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

x = [1, 2, 3, 4, 5]
y = [2, 4, 6, 8, 10]

plt.plot(x, y, marker='o')
plt.title("Grafica generada en contenedor Docker")
plt.xlabel("Eje X")
plt.ylabel("Eje Y")
plt.grid(True)
plt.savefig("grafica.png")

print("Imagen PNG generada correctamente: grafica.png")