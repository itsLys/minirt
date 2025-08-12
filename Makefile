GREEN  		= \033[0;32m
YELLOW 		= \033[0;33m
RED    		= \033[0;31m
RESET  		= \033[0m
BOLD		= \033[1m
CLEAR		= \033[K\r
NAME		= minirt
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
LFLAGS		= -lm
AR			= ar rcs
INCLUDES	= -I./headers/ -I./libft/headers/
LIBFT_DIR	= libft
LIBFT		= $(addprefix $(LIBFT_DIR)/, libft.a)
SRC			= src/main.c \
			  src/error.c \
			  src/gnl/get_next_line.c \
			  src/gnl/get_next_line_utils.c \
			  src/init/get_values.c \
			  src/init/init_objs.c \
			  src/init/init_scene.c \
			  src/init/parse_file.c \
			  src/vec3/vec3_ops.c
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
