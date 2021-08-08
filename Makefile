
CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = biquadris
OBJECTS = main.o manager.o block.o iblock.o jblock.o lblock.o oblock.o sblock.o zblock.o tblock.o ablock.o subject.o observer.o cell.o grid.o Operations.o textdisplay.o commandmanager.o laidBlocks.o Level.o ZeroLev.o decorator.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS} 
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}