NAME = pipex

NAME_BONUS = pipex

CC = cc

SRC = mandatory/main.c mandatory/srcs/display/display.c \
	mandatory/srcs/parcing/parcing1.c mandatory/srcs/tools/tools.c \
	mandatory/srcs/free/free.c 

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	@$(CC) ${CFLAGS} -c $< -o $@

all: ${NAME}

$(NAME): $(OBJ) mandatory/header.h
	@$(CC) $(OBJ) ${CFLAGS} -o $(NAME)
	@echo "compiled successfully !"

clean :
	@rm -f ${OBJ}
	@echo "cleaned successfully !"

fclean : clean
	@rm -f ${NAME}
re : fclean all