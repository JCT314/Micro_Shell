###########################################################
# Makefile for CS570 Assignment #2
# Jose Toscano(822990578)
###########################################################

EXEC = msh

$(EXEC):
	g++ -std=c++11 -o $(EXEC) msh.cpp Pipes.cpp FileCheck.cpp ProcessString.cpp

clean:
	rm -f *.o $(EXEC)

#######################[ EOF: Makefile ]###################