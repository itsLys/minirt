SRC =				src/ft_char/ft_isalnum.c \
					src/ft_char/ft_isalpha.c \
					src/ft_char/ft_isascii.c \
					src/ft_char/ft_isdigit.c \
					src/ft_char/ft_isprint.c \
					src/ft_char/ft_tolower.c \
					src/ft_char/ft_toupper.c \
					src/ft_conversions/ft_atof.c \
					src/ft_conversions/ft_atoi.c \
					src/ft_conversions/ft_atol.c \
					src/ft_conversions/ft_itoa.c \
					src/ft_io/ft_putchar_fd.c \
					src/ft_io/ft_putendl_fd.c \
					src/ft_io/ft_putnbr_fd.c \
					src/ft_io/ft_putstr_fd.c \
					src/ft_list/ft_lstadd_back.c \
					src/ft_list/ft_lstadd_front.c \
					src/ft_list/ft_lstclear.c \
					src/ft_list/ft_lstdelone.c \
					src/ft_list/ft_lstiter.c \
					src/ft_list/ft_lstlast.c \
					src/ft_list/ft_lstmap.c \
					src/ft_list/ft_lstnew.c \
					src/ft_list/ft_lstpush.c \
					src/ft_list/ft_lstreverse_rotate.c \
					src/ft_list/ft_lstrotate.c \
					src/ft_list/ft_lstsize.c \
					src/ft_list/ft_lstswap.c \
					src/ft_memory/ft_bzero.c \
					src/ft_memory/ft_calloc.c \
					src/ft_memory/ft_memchr.c \
					src/ft_memory/ft_memcmp.c \
					src/ft_memory/ft_memcpy.c \
					src/ft_memory/ft_memmove.c \
					src/ft_memory/ft_memset.c \
					src/ft_printf/ft_printf_bonus.c \
					src/ft_printf/parsing.c \
					src/ft_printf/print_char.c \
					src/ft_printf/print_hex.c \
					src/ft_printf/print_nbr.c \
					src/ft_printf/print_ptr.c \
					src/ft_printf/print_str.c \
					src/ft_printf/print_unsigned.c \
					src/ft_printf/utils.c \
					src/ft_proc/ft_execvpe.c \
					src/ft_proc/ft_getenv.c \
					src/ft_proc/ft_getpath.c \
					src/ft_string/ft_split.c \
					src/ft_string/ft_strchr.c \
					src/ft_string/ft_strcmp.c \
					src/ft_string/ft_strdup.c \
					src/ft_string/ft_strisdecimal.c \
					src/ft_string/ft_strisempty.c \
					src/ft_string/ft_strisnum.c \
					src/ft_string/ft_striteri.c \
					src/ft_string/ft_strjoin.c \
					src/ft_string/ft_strlcat.c \
					src/ft_string/ft_strlcpy.c \
					src/ft_string/ft_strlen.c \
					src/ft_string/ft_strmapi.c \
					src/ft_string/ft_strncmp.c \
					src/ft_string/ft_strnstr.c \
					src/ft_string/ft_strrchr.c \
					src/ft_string/ft_strtrim.c \
					src/ft_string/ft_substr.c \
					src/ft_string/ft_tokenize.c \
					src/ft_utils/ft_free_vector.c \
					src/ft_utils/ft_swap.c 
BOLD		= \033[1m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m
CLEAR		= \033[K\r
NAME		= libft.a
INCLUDES	= -I./headers/
CC			= cc -c -Wall -Wextra -Werror -g3
AR			= ar rcs
OBJ			= $(patsubst src/%.c, obj/%.o, $(SRC))
RM			= rm -rf

all: $(NAME)


$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(CLEAR)$(GREEN)$(BOLD)Libft.a done!$(RESET)"

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $< $(INCLUDES) -o $@
	@echo -n "[$(GREEN)$(BOLD) OK $(RESET)$(BOLD)]$(RESET) inserting $(BOLD)$@...$(RESET)$(CLEAR)"
	@$(AR) $(NAME) $@

clean :
	@echo "$(RED)Cleaning $(OBJ_DIR)...$(RESET)"
	@${RM} obj

fclean : clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@${RM} $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
					src/ft_utils/ft_swap.c 
