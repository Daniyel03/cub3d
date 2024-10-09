CC=cc
CFLAGS = -Wall -Wextra -Werror -I./includes
RM = rm -rf
SRC_DIR = src
OBJ_DIR = obj

SRCS = src/crop_map.c \
src/draw_line.c \
src/draw_wall_line.c \
src/exit.c \
src/flood_fill.c \
src/hooks.c \
src/init.c \
src/input_handler.c \
src/main.c \
src/parser.c \
src/parser_map.c \
src/parser_map2.c \
src/parser_texture1.c \
src/parser_texture2.c \
src/parser_utils1.c \
src/parser_utils2.c \
src/parser_utils3.c \
src/player_movement.c \
src/ray.c \
src/render.c \
src/util.c \
src/vector_utils.c

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

bonus: all

re: fclean all

.PHONY: all clean fclean re