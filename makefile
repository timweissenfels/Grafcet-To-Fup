CFLAGS = -O -std=c++2a
CC = g++
INCLUDES= -I./jsoncons/include
SRC = grfctofup.cpp
OBJ = $(SRC:.cpp = .o)
grfc_to_fup: $(OBJ)
		$(CC) $(CFLAGS) $(INCLUDES) -o grafcet_to_fup $(OBJ) -std=c++2a
clean:
		rm -f core *.o 
