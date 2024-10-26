# Makefile para Windows

PROG = engine.exe
SRC = Main.cpp Bezier.cpp Mesh.cpp World.cpp Camera.cpp InstanciaBZ.cpp ColorListRGB.cpp Object.cpp Point.cpp
OBJECTS = $(SRC:.cpp=.o)
CPPFLAGS = -O3 -g -Iinclude # -Wall -g  # Todas as warnings, infos de debug
# Se estiver usando mingw64, troque lib por lib\x64 abaixo
LDFLAGS = -Llib -lfreeglut -lopengl32 -lglu32 -lm
CC = g++

$(PROG): $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	-@ del $(OBJECTS) $(PROG)
