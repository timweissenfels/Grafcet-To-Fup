CFLAGS = -O
CC = g++
INCLUDES= -I./jsoncons/include
SRC = grfctofup.cpp single_statement.cpp transition.cpp expression.cpp node.cpp grafcet.cpp grafcet_timer.cpp
OBJ = $(SRC:.cpp = .o)
grfc_to_fup: $(OBJ)
		$(CC) $(CFLAGS) $(INCLUDES) -o grafcet_to_fup $(OBJ)
clean:
		rm -f core *.o 
