#---------------------------------------------
# Target file to be compiled by default
#---------------------------------------------
MAIN = cart
#---------------------------------------------
# CC is the compiler to be used
#---------------------------------------------
CC = gcc
#---------------------------------------------
# CFLAGS are the options passed to the compiler
#---------------------------------------------
CFLAGS = -Wall 
#---------------------------------------------
# OBJS are the object files to be linked
#---------------------------------------------
OBJ1 = cart
OBJ2 = ase_ace
OBJ3 = graphics
OBJS = $(OBJ1).o $(OBJ2).o $(OBJ3).o
#---------------------------------------------
# LIBS are the external libraries to be used
#--------------------------------------------
LIBS = -lrt -lm `allegro-config --libs`
#---------------------------------------------
# Dependencies
#--------------------------------------------
$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

$(OBJ1).o: $(OBJ1).c $(OJJ2).h
	$(CC) $(CFLAGS) -c $(OBJ1).c

$(OBJ2).o: $(OBJ2).c
	$(CC) $(CFLAGS) -c $(OBJ2).c
	
$(OBJ3).o: $(OBJ3).c
	$(CC) $(CFLAGS) -c $(OBJ3).c

#-------------------------------------------
# Command that can be specified inline: make clean
#-------------------------------------------
clean: 
	rm -rf *.o $(MAIN)
