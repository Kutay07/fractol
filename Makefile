NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3
MLX_PATH = minilibx-linux
LIBRARY = -L $(MLX_PATH) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
MLX = $(MLX_PATH)/libmlx.a
SRCS = main.c \
	hooks.c \
	fractals.c \
	fractal_utils.c \
	pixel_utils.c \
	program_utils.c \
	arg_utils.c

SRCSB = main_bonus.c \
	hooks_bonus.c \
	fractals_bonus.c \
	fractal_utils_bonus.c \
	pixel_utils_bonus.c \
	program_utils_bonus.c \
	arg_utils_bonus.c

OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCSB:.c=.o)

all: $(MLX) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) -o $(NAME)

$(MLX):
	@make -s -C $(MLX_PATH) -j16 2> /dev/null

bonus: $(MLX) $(OBJSB)
	@$(CC) $(CFLAGS) $(OBJSB) $(LIBRARY) -o $(NAME)

clean:
	@$(RM) $(OBJS) $(OBJSB)
	@make -C $(MLX_PATH) clean

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
