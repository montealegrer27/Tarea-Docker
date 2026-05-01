# Creación y documentación de contenedores Docker

## Descripción

Este proyecto tiene como objetivo demostrar el uso de Docker para crear, ejecutar y documentar contenedores. La práctica consiste en construir un contenedor inicial que ejecuta un programa en lenguaje C capaz de generar una imagen en formato JPG.

Además, se propone un segundo contenedor diferente, desarrollado en Python, que genera una gráfica en formato PNG. Con esto se busca comprender cómo Docker permite crear entornos aislados y reproducibles para ejecutar aplicaciones con sus dependencias.

---

## Objetivos

- Comprender el funcionamiento básico de Docker.
- Crear un contenedor Docker funcional.
- Ejecutar un programa en lenguaje C dentro de un contenedor.
- Generar una imagen en formato JPG desde un programa en C.
- Proponer y desarrollar un contenedor adicional.
- Documentar el proceso de construcción y ejecución.
- Organizar correctamente un repositorio de GitHub.

---

## ¿Qué es Docker?

Docker es una plataforma que permite crear, distribuir y ejecutar aplicaciones dentro de contenedores. Un contenedor es un entorno aislado que incluye el programa, sus dependencias y las herramientas necesarias para ejecutarlo.

Esto permite que una aplicación funcione de la misma manera en diferentes computadoras, evitando problemas de configuración o compatibilidad.

---

## Conceptos básicos de Docker

### Imagen

Una imagen es una plantilla que contiene todo lo necesario para crear un contenedor. Se construye a partir de un archivo llamado `Dockerfile`.

### Contenedor

Un contenedor es una instancia en ejecución de una imagen. Es decir, cuando una imagen se ejecuta, se crea un contenedor.

### Dockerfile

El `Dockerfile` es un archivo donde se escriben las instrucciones necesarias para construir una imagen Docker. En este archivo se define la imagen base, las dependencias, los archivos que se copian y el comando que se ejecutará.

### Volumen

Un volumen permite compartir archivos entre la computadora local y el contenedor. En esta práctica se utilizó para que las imágenes generadas dentro del contenedor aparecieran también en la carpeta del proyecto.

---

## Estructura del repositorio

```text
Tarea-Docker/
│
├── contenedor-c-jpg/
│   ├── Dockerfile
│   ├── Makefile
│   ├── main.c
│   └── salida.jpg
│
├── contenedor-python-png/
│   ├── Dockerfile
│   ├── grafica.py
│   └── grafica.png
│
├── evidencias/
│   ├── 01_comunicacion_docker.png
│   ├── 02_construccion_docker_C.png
│   ├── 03_ejecucion_contenedor_C.png
│   ├── 04_salida_jpg_generada.png
│   ├── 05_construccion_docker_python.png
│   ├── 06_ejecucion_contenedor_python.png
│   └── 07_grafica_png_generada.png
│
├── README.md
└── .gitignore
```

---

# 1. Contenedor inicial: programa en C que genera JPG

## Descripción

El primer contenedor cumple con el requisito principal de la tarea. Este contenedor utiliza un programa escrito en lenguaje C que genera una imagen en formato JPG llamada `salida.jpg`.

Para lograrlo, se utiliza la librería `libjpeg`, la cual permite crear y guardar imágenes en formato JPG desde un programa en C.

---

## Archivos del contenedor

Dentro de la carpeta `contenedor-c-jpg/` se encuentran los siguientes archivos:

```text
contenedor-c-jpg/
│
├── Dockerfile
├── Makefile
├── main.c
└── salida.jpg
```

### main.c

Contiene el programa en lenguaje C encargado de generar una imagen JPG. El programa crea una imagen de 800x600 píxeles y asigna colores a cada píxel para formar un degradado.

### Makefile

Automatiza la compilación y ejecución del programa en C.

### Dockerfile

Define el entorno del contenedor. Instala las herramientas necesarias para compilar el programa, incluyendo `gcc`, `make` y la librería `libjpeg`.

---

## Código del Dockerfile del contenedor en C

```dockerfile
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    libjpeg-dev \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

CMD ["make", "run"]
```

---

## Explicación del Dockerfile del contenedor en C

```dockerfile
FROM ubuntu:22.04
```

Indica que la imagen base será Ubuntu 22.04.

```dockerfile
RUN apt-get update && apt-get install -y \
    build-essential \
    libjpeg-dev \
    make \
    && rm -rf /var/lib/apt/lists/*
```

Actualiza los paquetes e instala las herramientas necesarias:

- `build-essential`: herramientas para compilar programas en C.
- `libjpeg-dev`: librería necesaria para generar archivos JPG.
- `make`: herramienta para ejecutar el Makefile.

```dockerfile
WORKDIR /app
```

Define la carpeta de trabajo dentro del contenedor.

```dockerfile
COPY . .
```

Copia los archivos del proyecto al contenedor.

```dockerfile
CMD ["make", "run"]
```

Indica que al ejecutar el contenedor se debe compilar y ejecutar el programa usando el Makefile.

---

## Código del Makefile del contenedor en C

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = generador_jpg
SRC = main.c
LIBS = -ljpeg

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) salida.jpg
```

---

## Explicación del Makefile

```makefile
CC = gcc
```

Define el compilador que se utilizará.

```makefile
CFLAGS = -Wall -Wextra -O2
```

Define las opciones de compilación. Estas opciones permiten mostrar advertencias y optimizar el programa.

```makefile
TARGET = generador_jpg
```

Define el nombre del ejecutable.

```makefile
SRC = main.c
```

Indica el archivo fuente que se va a compilar.

```makefile
LIBS = -ljpeg
```

Indica que se debe enlazar la librería JPEG.

```makefile
all: $(TARGET)
```

Regla principal para compilar el programa.

```makefile
run: all
	./$(TARGET)
```

Compila y ejecuta el programa.

```makefile
clean:
	rm -f $(TARGET) salida.jpg
```

Elimina el ejecutable y la imagen generada.

---

## Construcción de la imagen Docker

Para construir la imagen Docker del contenedor en C, se entra a la carpeta:

```bash
cd contenedor-c-jpg
```

Después se ejecuta:

```bash
docker build -t contenedor-c-jpg .
```

Este comando construye una imagen llamada `contenedor-c-jpg` usando el `Dockerfile` de la carpeta actual.

---

## Ejecución del contenedor

Para ejecutar el contenedor se utiliza:

```bash
docker run --rm -v "%cd%":/app contenedor-c-jpg
```

---

## Explicación del comando de ejecución

```bash
docker run
```

Ejecuta un contenedor a partir de una imagen.

```bash
--rm
```

Elimina el contenedor automáticamente cuando termina su ejecución.

```bash
-v "%cd%":/app
```

Monta la carpeta actual de la computadora dentro de la carpeta `/app` del contenedor. Esto permite que el archivo `salida.jpg` generado dentro del contenedor aparezca en la carpeta local del proyecto.

```bash
contenedor-c-jpg
```

Es el nombre de la imagen que se va a ejecutar.

---

## Resultado esperado

Al ejecutar el contenedor, se obtiene una salida similar a:

```text
Imagen JPG generada correctamente: salida.jpg
```

Después de ejecutar el contenedor, dentro de la carpeta `contenedor-c-jpg/` se genera el archivo:

```text
salida.jpg
```

---

# 2. Contenedor adicional: programa en Python que genera PNG

## Descripción

Como contenedor adicional, se desarrolló un contenedor diferente al inicial. Este segundo contenedor utiliza Python para generar una gráfica en formato PNG.

El programa utiliza la librería `matplotlib` para crear una gráfica sencilla y guardarla como `grafica.png`.

---

## Archivos del contenedor adicional

Dentro de la carpeta `contenedor-python-png/` se encuentran los siguientes archivos:

```text
contenedor-python-png/
│
├── Dockerfile
├── grafica.py
└── grafica.png
```

### grafica.py

Es el script de Python que genera una gráfica y la guarda como imagen PNG.

### Dockerfile

Define el entorno del contenedor de Python e instala la librería `matplotlib`.

---

## Código del Dockerfile del contenedor adicional

```dockerfile
FROM python:3.11-slim

WORKDIR /app

RUN pip install matplotlib

COPY . .

CMD ["python", "grafica.py"]
```

---

## Explicación del Dockerfile del contenedor adicional

```dockerfile
FROM python:3.11-slim
```

Indica que la imagen base será Python 3.11 en una versión ligera.

```dockerfile
WORKDIR /app
```

Define la carpeta de trabajo dentro del contenedor.

```dockerfile
RUN pip install matplotlib
```

Instala la librería `matplotlib`, necesaria para generar la gráfica.

```dockerfile
COPY . .
```

Copia los archivos del proyecto al contenedor.

```dockerfile
CMD ["python", "grafica.py"]
```

Ejecuta el script de Python cuando inicia el contenedor.

---

## Construcción de la imagen Docker del contenedor adicional

Para construir la imagen, se entra a la carpeta:

```bash
cd contenedor-python-png
```

Después se ejecuta:

```bash
docker build -t contenedor-python-png .
```

---

## Ejecución del contenedor adicional

Para ejecutar el contenedor se utiliza:

```bash
docker run --rm -v "%cd%":/app contenedor-python-png
```

---

## Resultado esperado

Al ejecutar el contenedor, se obtiene una salida similar a:

```text
Imagen PNG generada correctamente: grafica.png
```

Después de ejecutar el contenedor, dentro de la carpeta `contenedor-python-png/` se genera el archivo:

```text
grafica.png
```

---

# 3. Evidencias de ejecución

Para comprobar el funcionamiento del proyecto, se agregaron capturas de pantalla dentro de la carpeta `evidencias/`.

Las evidencias incluidas son:

```text
01_comunicacion_docker.png
```

Muestra la ejecución de `docker run hello-world`, verificando que Docker está instalado y funcionando correctamente.

```text
02_construccion_docker_C.png
```

Muestra la construcción de la imagen Docker del contenedor en C.

```text
03_ejecucion_contenedor_C.png
```

Muestra la ejecución del contenedor en C y la generación de `salida.jpg`.

```text
04_salida_jpg_generada.png
```

Muestra la carpeta donde se generó el archivo `salida.jpg`.

```text
05_construccion_docker_python.png
```

Muestra la construcción de la imagen Docker del contenedor adicional en Python.

```text
06_ejecucion_contenedor_python.png
```

Muestra la ejecución del contenedor en Python y la generación de `grafica.png`.

```text
07_grafica_png_generada.png
```

Muestra la carpeta donde se generó el archivo `grafica.png`.

---

# 4. Comandos utilizados

## Verificar Docker

```bash
docker --version
```

```bash
docker run hello-world
```

---

## Contenedor en C

Entrar a la carpeta:

```bash
cd contenedor-c-jpg
```

Construir la imagen:

```bash
docker build -t contenedor-c-jpg .
```

Ejecutar el contenedor:

```bash
docker run --rm -v "%cd%":/app contenedor-c-jpg
```

---

## Contenedor en Python

Entrar a la carpeta:

```bash
cd contenedor-python-png
```

Construir la imagen:

```bash
docker build -t contenedor-python-png .
```

Ejecutar el contenedor:

```bash
docker run --rm -v "%cd%":/app contenedor-python-png
```

---

# 5. Archivo .gitignore

Se agregó un archivo `.gitignore` para evitar subir archivos innecesarios o temporales al repositorio.

El archivo `.gitignore` utilizado es:

```gitignore
# Archivos compilados y ejecutables
*.o
*.out
*.exe
generador_jpg

# Archivos temporales y del sistema
.DS_Store
Thumbs.db

# Configuración del editor
.vscode/
```

Este archivo ayuda a mantener el repositorio limpio y organizado.

---

# 6. Importancia de Docker en el desarrollo

Docker permite crear entornos controlados para ejecutar aplicaciones sin depender directamente de la configuración de la computadora local.

Esto es útil porque permite que un programa funcione de la misma manera en diferentes equipos, ya que todas las dependencias se instalan dentro del contenedor. Además, Docker facilita la distribución de proyectos, mejora la organización y reduce problemas relacionados con versiones de programas o librerías.

---

# 7. Conclusión

En esta práctica se logró comprender el funcionamiento básico de Docker mediante la construcción de dos contenedores funcionales.

El primer contenedor permitió compilar y ejecutar un programa en lenguaje C capaz de generar una imagen en formato JPG. El segundo contenedor, propuesto como adicional, utilizó Python para generar una gráfica en formato PNG.

Con esta actividad se comprobó que Docker es una herramienta útil para crear entornos reproducibles, organizar proyectos y ejecutar aplicaciones de forma aislada y eficiente.
