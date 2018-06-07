##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC	=	gcc

RM	=	rm -f

NAME	=	libmy_malloc.so

DZCOLOR	 = \e[0;33m
LSCOLOR	 = \e[0;37m
LICOLOR	 = \e[0;31m
RSCOLOR	 = \e[1;37m

CFLAGS	=	-Wall -Wextra -fPIC

SRC	=	malloc.c		\
		realloc.c		\
		calloc.c		\
		free.c          \
		utils.c         \
		printf.c        \
		printf_utils.c

OBJ	=	$(SRC:.c=.o)

#For testing
T_NAME = program

EXE_TEST = reverse_me_to_improve_your_malloc

$(NAME)	:	$(OBJ)
		@echo -e "$(LICOLOR)# Generation of .o files$(LSCOLOR)"
		@echo -e "$(LICOLOR)# Generation of Library$(RSCOLOR)"
		$(CC) $(CFLAGS) $(OBJ) -shared -o $(NAME)
		@echo -e "$(DZCOLOR)# Compilation Done$(LSCOLOR)"

all	:	$(NAME)

exec_shell :
        LD_LIBRARY_PATH=$(shell pwd) LD_PRELOAD=`realpath libmy_malloc.so` $(shell ls) $(LSCOLOR)

exec_test :
		@echo -e "$(DZCOLOR)# Compiling program and Execution with File$(LSCOLOR)"
		@LD_LIBRARY_PATH=$(shell pwd) LD_PRELOAD=$(shell pwd)/$(NAME) ./$(EXE_TEST)

exec :
		@echo -e "$(LICOLOR)# Compilation for Testing Program$(RSCOLOR)"
		$(CC) main.c -L. -lmy_malloc -ldl -lm -o $(T_NAME)
		@echo -e "$(DZCOLOR)# Compiling program and Execution$(LSCOLOR)"
		@LD_LIBRARY_PATH=$(shell pwd) LD_PRELOAD=$(shell pwd)/$(NAME) ./$(T_NAME)

exec_debug :
		@echo -e "$(LICOLOR)# Compilation for Testing Program$(RSCOLOR)"
		$(CC) main.c -L. -lmy_malloc -ldl -g -o $(T_NAME)
		@echo -e "$(DZCOLOR)# Compiling program and Execution For Debuging$(LSCOLOR)"
		@LD_LIBRARY_PATH=$(shell pwd) LD_PRELOAD=$(shell pwd)/$(NAME) valgrind ./$(T_NAME)

clean	:
		@$(RM) $(OBJ)
		@echo -e "$(LICOLOR)# Deleting .o files$(LSCOLOR)"

fclean	:	clean
		@$(RM) $(NAME)
		@echo -e "$(LICOLOR)# Deleting Library$(RSCOLOR)"
		@echo -e "$(LICOLOR)# Deleting Test Program$(LSCOLOR)"
		@$(RM) $(T_NAME)

re	: fclean all

#for testing

run : re exec

debug : re exec_debug

ls : re exec_shell

test : re exec_test
