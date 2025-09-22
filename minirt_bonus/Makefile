GREEN  		= \033[0;32m
YELLOW 		= \033[0;33m
RED    		= \033[0;31m
RESET  		= \033[0m
BOLD		= \033[1m
CLEAR		= \033[K\r
NAME		= minirt
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -Ofast
LFLAGS		= -lmlx -lX11 -lXext -lm
AR			= ar rcs
INCLUDES	= -I./headers/ -I./libft/headers/
LIBFT_DIR	= libft
LIBFT		= $(addprefix $(LIBFT_DIR)/, libft.a)
SRC			= src/main.c \
			  src/error.c \
			  src/testing.c \
			  src/gnl/get_next_line.c \
			  src/gnl/get_next_line_utils.c \
			  src/init/get_values.c \
			  src/init/init_objs.c \
			  src/init/init_rays.c \
			  src/init/init_offsets.c \
			  src/init/parse_scene.c \
			  src/init/parse_file.c \
			  src/init/parse_line.c \
			  src/vec3/vec3_ops.c \
			  src/vec3/vec3_math.c \
			  src/vec3/vec3_create.c \
			  src/vec3/vec3_utils.c \
			  src/vec3/vec3_transform.c \
			  src/objects/lst_utils.c \
              src/objects/obj_sort.c \
			  src/mlx/events.c \
			  src/mlx/window.c \
			  src/camera/cam_setup.c \
			  src/events/keys.c \
			  src/events/loop.c \
			  src/events/mouse.c \
			  src/events/handlers/move_handler.c \
			  src/events/handlers/props_handler.c \
			  src/events/handlers/rotate_handler.c \
			  src/render/draw.c \
			  src/hit/intersect.c \
			  src/hit/quadratic.c \
			  src/hit/trace.c \
			  src/hit/hit.c \
			  src/color/compute.c \
			  src/color/color.c \
			  src/color/rgb_ops.c \
			  src/color/rgb_conv.c \
			  src/threads/threads.c \
			  src/threads/workers.c \
			  src/rays/pixel_map.c \
			  src/utils/utils.c 
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
