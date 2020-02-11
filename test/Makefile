NAME = run_test

MALLOC_LIB = -lmalloc -L..
export DYLD_LIBRARY_PATH = ..
export LD_LIBRARY_PATH = ..


CFLAGS   = -Wall -Wextra -Werror

SRC      = main.c

INCLUDES = -I./includes -I../includes

OBJ_DIR = ./objs

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

SRC_DIR = .

lib:
	make -C ..

all: lib $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(MALLOC_LIB) -o $(NAME)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all 
	./run_test
