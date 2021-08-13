CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -L/opt/X11/lib -lX11 -I/opt/X11/include
EXEC = biquadris
OBJECTS = main.o manager.o block.o iblock.o jblock.o lblock.o oblock.o sblock.o zblock.o tblock.o ablock.o subject.o observer.o cell.o grid.o Operations.o decorator.o specialaction.o blind.o force.o heavy.o textdisplay.o commandmanager.o laidBlocks.o Level.o ZeroLev.o OneLev.o TwoLev.o ThreeLev.o FourLev.o window.o graphics.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS} 
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}