CFLAGS = -std=c++11 -g -O2
OBJECTS = piece.o board.o main.o emptyPiece.o pawn.o
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

chess.out : $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $@ $(LINKER_FLAGS)

board.o : src/board.cpp src/board.h
	$(CXX) $(CFLAGS) -c src/board.cpp

main.o : src/main.cpp
	$(CXX) $(CFLAGS) -c src/main.cpp

%.o : src/%.cpp src/%.h src/piece.cpp src/piece.h
	$(CXX) $(CFLAGS) -c $<