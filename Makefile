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
MAP_SRC_DIR = src/map/
ALGO_SRC_DIR = src/algo/

OBJ_DIR = obj/
MAP_OBJ_DIR = obj/map/
ALGO_OBJ_DIR = obj/algo/

DEP_DIR = dep/
MAP_DEP_DIR = dep/map/
ALGO_DEP_DIR = dep/algo/

MAP_SRC = open_map.c map_check.c map_rules.c map_rules2.c map_dimensions.c \
	get_textures.c get_colors.c

ALGO_SRC = init.c render.c raycast.c dda.c raycast_utils.c movement.c draw.c handle_input.c draw_utils.c

MAIN = main.c

MAP_OBJ = ${MAP_SRC:%.c=%.o}
MAP_DEP = ${MAP_OBJ:%.o=%.d}

ALGO_OBJ = ${ALGO_SRC:%.c=%.o}
ALGO_DEP = ${ALGO_OBJ:%.o=%.d}

MAIN_OBJ = main.o

MAP_SRCF = $(addprefix $(MAP_SRC_DIR), $(MAP_SRC))
MAP_OBJF = $(addprefix $(MAP_OBJ_DIR), $(MAP_OBJ))
MAP_DEPF = $(addprefix $(MAP_DEP_DIR), $(MAP_DEP))

ALGO_SRCF = $(addprefix $(ALGO_SRC_DIR), $(ALGO_SRC))
ALGO_OBJF = $(addprefix $(ALGO_OBJ_DIR), $(ALGO_OBJ))
ALGO_DEPF = $(addprefix $(ALGO_DEP_DIR), $(ALGO_DEP))

SRCF = $(ALGO_SRCF) $(MAP_SRCF) $(MAIN)
OBJF = $(ALGO_OBJF) $(MAP_OBJF) $(MAIN_OBJ)
DEPF = $(ALGO_DEPF) $(MAP_DEPF)

# ------------------------------------------------------------------------------
# 									COMPILING
# ------------------------------------------------------------------------------

.SILENCE : $(CC) $(FLAGS) $(SRC) $(EXEC) $(OBJ) $(OBJF) $(OBJ_DIR) \
	$(DEP_DIR) $(SRC_DIR) $(MLX_LIB)

all: $(MLX_LIB) cub3d

cub3d: $(NAME) $(OBJ_DIR) $(DEP_DIR) $(OBJF)
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

$(MAP_OBJ_DIR)%.o : $(MAP_SRC_DIR)%.c | $(MAP_OBJ_DIR) $(MAP_DEP_DIR)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -MF $(MAP_DEP_DIR)$*.d

$(ALGO_OBJ_DIR)%.o : $(ALGO_SRC_DIR)%.c | $(ALGO_OBJ_DIR) $(ALGO_DEP_DIR)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -MF $(ALGO_DEP_DIR)$*.d

# ------------------------------------------------------------------------------
# 									DIR GENERATION
# ------------------------------------------------------------------------------

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
$(ALGO_OBJ_DIR) :
	@mkdir -p $(ALGO_OBJ_DIR)
$(MAP_OBJ_DIR) :
	@mkdir -p $(MAP_OBJ_DIR)

$(DEP_DIR) :
	@mkdir -p $(DEP_DIR)
$(ALGO_DEP_DIR) :
	@mkdir -p $(ALGO_DEP_DIR)
$(MAP_DEP_DIR) :
	@mkdir -p $(MAP_DEP_DIR)

# ------------------------------------------------------------------------------
# 									CLEANING
# ------------------------------------------------------------------------------

clean:
	@echo "${RED}Cleaning libft && Cub3d..${RESET}"
	@$(MAKE) clean --no-print-directory -C ./libft
	@$(RM) $(OBJ_DIR)
	@$(RM) $(MAIN_OBJ)
	@$(RM) $(DEP_DIR)
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