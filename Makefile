SRCS = main.c init.c render.c raycast.c dda.c

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -I./includes/
RM = rm -rf
EXEC = cub3d
NAME = cub3d.a
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
MAGENTA= \033[35m
CYAN   = \033[36m
RESET  = \033[0m

all: $(MLX_LIB) cub3d

cub3d: $(NAME) $(OBJS)
	echo "${CYAN}Compiling cub3d...${RESET}"
	cc ${SRCS} cub3d.a libft/libft.a mlx/libmlx.a mlx/libmlx_Linux.a -lX11 -lXext -o cub3d -lm
	echo "${GREEN}Succes!!!${RESET}"
$(NAME): $(OBJS)
	echo "${CYAN}Compiling libft...${RESET}"
	$(MAKE) --no-print-directory -C ./libft
	cp libft/libft.a ../cub3d
	ar rc $(NAME) $(OBJS)
$(MLX_LIB):
	@make -C $(MLX_DIR)
clean:
	echo "${RED}Cleaning libft && Cub3d..${RESET}"
	$(MAKE) clean --no-print-directory -C ./libft
	$(RM) $(OBJS) objs
	$(RM) libft.a
	echo "${GREEN}Succes!!!${RESET}"
fclean: clean
	$(MAKE) fclean --no-print-directory -C ./libft
	echo "${RED}Cleaning exucutable files...${RESET}"
	$(RM) $(NAME) cub3d
	echo "${GREEN}Succes!!!${RESET}"
re: fclean all

.PHONY: all clean fclean re