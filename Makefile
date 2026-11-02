CC = gcc

TARGET = test
SOURCES = src/renderer.c src/parser.c
FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) $(FLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
