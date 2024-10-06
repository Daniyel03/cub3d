CC=clang
# CFLAGS = -g  -fsanitize=address -Wall -Wextra -Werror -I./includes -I./includes/42get_next_line-master
CFLAGS = -g -gdwarf-4 -Wall -Wextra -Werror -I./includes
RM = rm -rf
#-fsanitize=address,leak,undefined
SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./libft -lft -lmlx -lXext -lX11 -lm


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	make clean -C ./libft
	$(RM) $(OBJ_DIR)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re