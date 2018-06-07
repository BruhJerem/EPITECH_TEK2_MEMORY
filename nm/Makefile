##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile
##

NAME_OBJ = my_objdump

NAME_NM = my_nm

DZCOLOR	=	\e[0;33m
LSCOLOR	=	\e[0;37m
LICOLOR	=	\e[0;31m
RSCOLOR	=	\e[1;37m

CC	=	gcc

RM	=	rm -f

SRC_OBJ	=	./objdump/main_obj.c			\
		./objdump/check_obj.c   		\
		./objdump/check_ident.c 		\
		./objdump/check_type_machine32.c  	\
		./objdump/check_type_machine64.c  	\
		./objdump/error.c   			\
		./objdump/utils_dump.c  		\
		./objdump/get_objdump32.c   		\
		./objdump/get_objdump64.c

OBJ_OBJ	=	$(SRC_OBJ:.c=.o)

SRC_NM =	./nm/main_nm.c     			\
		./nm/check_nm.c    			\
		./nm/check_ident.c 			\
		./nm/get_nm64.c       			\
		./nm/get_nm32.c      			\
		./nm/error.c        			\
		./nm/print_symbol.c 			\
		./nm/check_type_machine64.c 		\
		./nm/check_type_machine32.c

OBJ_NM =    $(SRC_NM:.c=.o)

CFLAGS = -I
CFLAGS += -W -Wall -Wextra

all: $(NAME_NM) $(NAME_OBJ)

$(NAME_NM):     $(OBJ_NM)
	@echo -e "$(LICOLOR)# Generation of NM$(LSCOLOR)"
	$(CC) $(OBJ_NM) -o $(NAME_NM) $(LDFLAGS)
	@echo -e "$(DZCOLOR)# Compilation accomplished for NM$(LSCOLOR)"

$(NAME_OBJ):    $(OBJ_OBJ)
	@echo -e "$(LICOLOR)# Generation of OBJDUMP$(LSCOLOR)"
	$(CC) $(OBJ_OBJ) -o $(NAME_OBJ) $(LDFLAGS)
	@echo -e "$(DZCOLOR)# Compilation accomplished for OBJDUMP$(LSCOLOR)"

nm : $(NAME_NM)

objdump : $(NAME_OBJ)

clean:
	@$(RM) $(OBJ_OBJ)
	@echo -e "$(LICOLOR)# Deleting OBJDUMP .o$(LSCOLOR)"
	@$(RM) $(OBJ_NM)
	@echo -e "$(LICOLOR)# Deleting NM .o$(LSCOLOR)"

fclean: clean
	@echo -e "$(LICOLOR)# Deleting OBJDUMP Executable$(LSCOLOR)"
	@$(RM) $(NAME_OBJ)
	@echo -e "$(LICOLOR)# Deleting NM Executable$(LSCOLOR)"
	@$(RM) $(NAME_NM)

re: fclean all

.PHONY: all clean fclean re
