CFLAGS = -std=c++11 -g -O2
OBJECTS = piece.o board.o main.o emptyPiece.o pawn.o rook.o bishop.o knight.o king.o queen.o
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

chess.out : $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $@ $(LINKER_FLAGS)

board.o : src/board.cc src/board.h
	$(CXX) $(CFLAGS) -c src/board.cc

main.o : src/main.cc
	$(CXX) $(CFLAGS) -c src/main.cc

%.o : src/%.cc src/%.h src/piece.cc src/piece.h
	$(CXX) $(CFLAGS) -c $<