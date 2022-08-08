# SRC = testfloat.c
# OBJ = testfloat.o
SRC = ${wildcard *.c}
OBJ = ${SRC:%.c=%.o}
Debug:
	$(CC) -c $(SRC) -o $(OUTPUT_DIR)/$(OBJ)