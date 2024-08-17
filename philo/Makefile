NAME = philo
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
#CFLAGS = -fsanitize=address -g -I$(LIBFT_DIR)

SRC_PATH = src/

FILES_PATH = ./
FILES_SRC = main.c assign.c init.c log_action.c time_managment_utils.c \
			thread_management.c actions.c initialization_time.c\
			atomic_operations.c destroy_and_free.c monitor.c aux_funcs.c

OBJ_PATH = build/

SRC = $(addprefix $(FILES_PATH), $(FILES_SRC))

OBJ =	$(SRC:.c=.o)
OBJS =	$(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

clean:
	rm -rf $(OBJ_PATH)


fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re