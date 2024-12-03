CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -I./includes/
RM = rm -rf
EXEC = cub3d
NAME = cub3d.a
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
LIBS = libft/libft.a mlx/libmlx.a -lX11 -lXext -lm

RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
MAGENTA= \033[35m
CYAN   = \033[36m
RESET  = \033[0m

# ------------------------------------------------------------------------------
# 									FILES
# ------------------------------------------------------------------------------

SRC_DIR = src/
OBJ_DIR = obj/
DEP_DIR = dep/

SRC = main.c init.c render.c raycast.c open_map.c map_check.c map_rules.c \
	map_rules2.c map_dimensions.c flood_fill.c dda.c

OBJ = ${SRC:%.c=%.o}
DEP = ${OBJ:%.o=%.d}

SRCF = $(addprefix $(SRC_DIR), $(SRC))
OBJF = $(addprefix $(OBJ_DIR), $(OBJ))
DEPF = $(addprefix $(DEP_DIR), $(DEP))

# ------------------------------------------------------------------------------
# 									COMPILING
# ------------------------------------------------------------------------------

.SILENCE : $(CC) $(FLAGS) $(SRC) $(EXEC) $(OBJ) $(OBJF) $(OBJ_DIR) \
	$(DEP_DIR) $(SRC_DIR)

all: $(MLX_LIB) cub3d

cub3d: $(NAME) $(OBJF)
	@echo "${CYAN}Compiling cub3d...${RESET}"
	@cc ${SRCF} $(NAME) $(LIBS) -o $(EXEC)
	@echo "${GREEN}Succes!!!${RESET}"

$(NAME): $(OBJF)
	@echo "${CYAN}Compiling libft...${RESET}"
	@$(MAKE) --no-print-directory -C ./libft
	@cp libft/libft.a ../cub3d
	@ar rc $(NAME) $(OBJF)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR) $(DEP_DIR)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -MF $(DEP_DIR)$*.d

# ------------------------------------------------------------------------------
# 									DIR GENERATION
# ------------------------------------------------------------------------------

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(DEP_DIR) :
	@mkdir -p $(DEP_DIR)

# ------------------------------------------------------------------------------
# 									CLEANING
# ------------------------------------------------------------------------------

clean:
	@echo "${RED}Cleaning libft && Cub3d..${RESET}"
	@$(MAKE) clean --no-print-directory -C ./libft
	@$(RM) $(OBJ_DIR) objf
	@$(RM) $(DEP_DIR) depf
	@$(RM) libft.a
	@echo "${GREEN}Succes!!!${RESET}"
fclean: clean
	@$(MAKE) fclean --no-print-directory -C ./libft
	@echo "${RED}Cleaning exucutable files...${RESET}"
	@$(RM) $(NAME) cub3d
	@echo "${GREEN}Succes!!!${RESET}"

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)