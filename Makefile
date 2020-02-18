# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhugh-be <bhugh-be@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 18:21:10 by bhugh-be          #+#    #+#              #
#    Updated: 2020/02/08 19:08:56 by bwerewol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmalloc.so

CFLAGS   =  -Wall -Wextra -fPIC -O0 -g3 -ggdb

SRC      = malloc.c\
           free.c\
           realloc.c\
           zone.c\
           zone_tree.c\
           common.c

INC      = malloc.h\
           zone_tree.h\
           common.h

INCLUDES = -I./includes

OBJ_DIR = ./objs

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

SRC_DIR = ./src

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) -shared $(CFLAGS) $(OBJ) -o $(NAME) $(INCLUDES)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	make -C test fclean

re: fclean all

test: all
	make -C test
