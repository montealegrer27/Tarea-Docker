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