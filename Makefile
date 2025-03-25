NAME = pipex

CC = cc

SRC = mandatory/main.c mandatory/srcs/display/display.c \
	mandatory/srcs/parcing/parcing1.c mandatory/srcs/parcing/parcing2.c mandatory/srcs/parcing/parcing3.c \
	mandatory/srcs/parcing/paths.c mandatory/srcs/tools/tools.c mandatory/srcs/free/free.c \
	mandatory/srcs/linkedlist/linkedlist.c mandatory/srcs/execution/execution.c

SRC_BONUS = bonus/main_bonus.c bonus/srcs_bonus/display_bonus/display_bonus.c \
	bonus/srcs_bonus/parcing_bonus/parcing1_bonus.c bonus/srcs_bonus/parcing_bonus/parcing2_bonus.c \
	bonus/srcs_bonus/parcing_bonus/parcing3_bonus.c bonus/srcs_bonus/parcing_bonus/paths_bonus.c \
	bonus/srcs_bonus/tools_bonus/tools_bonus.c bonus/srcs_bonus/tools_bonus/tools2_bonus.c \
	bonus/srcs_bonus/free_bonus/free_bonus.c \
	bonus/srcs_bonus/linkedlist_bonus/linkedlist_bonus.c bonus/srcs_bonus/execution_bonus/execution_bonus.c \
	bonus/srcs_bonus/here_doc/here_doc_bonus.c bonus/get_next_line/get_next_line.c \
	bonus/srcs_bonus/execution_bonus/execution2_bonus.c bonus/get_next_line/get_next_line_utils.c

OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

%.o: %.c bonus/header_bonus.h mandatory/header.h
	@$(CC) ${CFLAGS} -c $< -o $@

all: ${NAME}

$(NAME): $(OBJ)
	@$(CC) $(OBJ) ${CFLAGS} -o $(NAME)
	@echo "compiled successfully !"

bonus: $(OBJ_BONUS)
	@$(CC) $(OBJ_BONUS) ${CFLAGS} -o $(NAME)
	@echo "bonus compiled successfully !"

clean :
	@rm -f ${OBJ} ${OBJ_BONUS}
	@echo "cleaned successfully !"

fclean : clean
	@rm -f ${NAME} ${NAME_BONUS}

re : fclean all