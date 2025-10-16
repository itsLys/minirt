GREEN  		= \033[0;32m
YELLOW 		= \033[0;33m
RED    		= \033[0;31m
RESET  		= \033[0m
BOLD		= \033[1m
CLEAR		= \033[K\r
NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -Ofast
LFLAGS		= -lmlx -lX11 -lXext -lm
AR			= ar rcs
INCLUDES	= -I./headers/ -I./libft/headers/
LIBFT_DIR	= libft
LIBFT		= $(addprefix $(LIBFT_DIR)/, libft.a)
SRC         = src/camera.c \
			  src/light/color.c \
			  src/light/bump_map.c \
			  src/light/light.c \
			  src/light/sample.c \
			  src/light/shadow.c \
			  src/light/utils.c \
			  src/light/texture_ratio.c \
			  src/destructors.c \
			  src/main.c \
			  src/events/handlers/handlers.c \
			  src/events/handlers/move_handler.c \
			  src/events/handlers/props_handler.c \
			  src/events/handlers/scene_props_handler.c \
			  src/events/handlers/rotate_handler.c \
			  src/events/handlers/select_handler.c \
			  src/events/keys.c \
			  src/events/loop.c \
			  src/exit.c \
			  src/gnl/get_next_line.c \
			  src/gnl/get_next_line_utils.c \
			  src/hit/hit.c \
			  src/hit/intersect.c \
			  src/hit/check_intersect.c \
			  src/hit/intersect_utils.c \
			  src/hit/quadratic.c \
			  src/hit/trace.c \
			  src/init/init_data.c \
			  src/init/init_mlx.c \
			  src/init/init_pre_calc.c \
			  src/init/init_program.c \
			  src/mlx/events.c \
			  src/mlx/images.c \
			  src/mlx/window.c \
			  src/objects/lst_utils.c \
			  src/objects/obj_sort.c \
			  src/parser/parse_file.c \
			  src/parser/parse_line.c \
			  src/parser/parse_objs.c \
			  src/parser/parse_params/parse_numbers.c \
			  src/parser/parse_params/parse_strings.c \
			  src/parser/parse_params/parse_surface.c \
			  src/parser/parse_params/parse_textures.c \
			  src/parser/parse_params/parse_vectors.c \
			  src/parser/parse_scene.c \
			  src/parser/utils.c \
			  src/draw.c \
			  src/rgb/rgb_conv.c \
			  src/rgb/rgb_ops.c \
			  src/threads/threads.c \
			  src/threads/workers.c \
			  src/comparison.c \
			  src/vec3/vec3_create.c \
			  src/vec3/vec3_math.c \
			  src/vec3/vec3_ops.c \
			  src/vec3/vec3_transform.c \
			  src/vec3/vec3_utils.c \
			  src/print/print.c \
			  src/print/print_obj.c \
			  src/print/print_params.c \
			  src/print/print_scene.c \
			  src/print/print_tx.c

OBJ			= $(patsubst src/%.c, obj/%.o, $(SRC))
all: $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) done!$(RESET)"

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(CLEAR)$(YELLOW)linking $(NAME)...$(RESET)"
	@$(CC) $(OBJ) $(LFLAGS) $(LIBFT) -o $(NAME)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo -n "[$(GREEN)$(BOLD) OK $(RESET)]$(RESET) compiling $(BOLD)$@...$(RESET)$(CLEAR)"
	@$(CC) -c $(CFLAGS) $< $(INCLUDES) -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)/ all

clean:
	@make -C $(LIBFT_DIR)/ clean
	@rm -rf obj

fclean: clean
	@make -C $(LIBFT_DIR)/ fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean

.SECONDARY: $(OBJ)
