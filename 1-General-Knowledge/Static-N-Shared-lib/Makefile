CUR_DIR := . 
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
LIB_DIR := $(CUR_DIR)/lib
OBJ_DIR := $(CUR_DIR)/obj
SRC_DIR := $(CUR_DIR)/src

STATIC_LIB_DIR := $(LIB_DIR)/static
SHARED_LIB_DIR := $(LIB_DIR)/shared

CC := gcc

#======================= Static library =========================

# created object file
all :
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o -I $(INC_DIR)
	$(CC) -c $(SRC_DIR)/hellothuy.c -o $(OBJ_DIR)/hellothuy.o -I $(INC_DIR)
	$(CC) -c $(SRC_DIR)/helloWorld.c -o $(OBJ_DIR)/helloWorld.o -I $(INC_DIR)
# created static lib
static :
	ar rcs $(STATIC_LIB_DIR)/libhello.a $(OBJ_DIR)/hellothuy.o $(OBJ_DIR)/helloWorld.o
# linker 
link_static :
	$(CC) $(OBJ_DIR)/main.o -L $(STATIC_LIB_DIR) -l hello -o $(BIN_DIR)/exam

#===================== Shared library ==========================

# created object file
obj :
	$(CC) -fPIC -o $(OBJ_DIR)/main.o -c $(CUR_DIR)/main.c -I $(INC_DIR)
	$(CC) -fPIC -o $(OBJ_DIR)/hellothuy.o -c $(SRC_DIR)/hellothuy.c -I $(INC_DIR)
	$(CC) -fPIC -o $(OBJ_DIR)/helloWorld.o -c $(SRC_DIR)/helloWorld.c -I $(INC_DIR)

# created shared library
shared :
	$(CC) -shared -o $(SHARED_LIB_DIR)/libhello.so $(OBJ_DIR)/main.o $(OBJ_DIR)/hellothuy.o $(OBJ_DIR)/helloWorld.o

# linker
link_shared :
	$(CC) $(OBJ_DIR)/main.o -L $(SHARED_LIB_DIR)/ -l hello -o $(BIN_DIR)/exam

clean:
	rm -rf $(OBJ_DIR)/* 
	rm -rf $(LIB_SHARED_DIR)/* 
	rm -rf $(BIN_DIR)/* 



