CC = cc

NAME = minishell

SRC_DIR = src
MAIN_DIR = $(SRC_DIR)/main
PARSE_DIR = $(SRC_DIR)/parser
EXEC_DIR = $(SRC_DIR)/execute
BUILT_DIR = $(SRC_DIR)/builtins
UTILS_DIR = $(SRC_DIR)/utils
OBJ_DIR = obj
MAIN_OBJ_DIR = $(OBJ_DIR)/main
PARSE_OBJ_DIR = $(OBJ_DIR)/parser
EXEC_OBJ_DIR = $(OBJ_DIR)/execute
BUILT_OBJ_DIR = $(OBJ_DIR)/builtins
UTILS_OBJ_DIR = $(OBJ_DIR)/utils

MAIN_SRC_FILES = main.c init.c env_utils.c path_env.c
PARSE_SRC_FILES = parser.c signals.c redir_utils.c command_struct.c command_struct_utils.c \
				  split_utils.c arg_parsing.c quote_handling.c quote_handling_utils.c
EXEC_SRC_FILES = execute.c execute_child.c execute_builtin.c redirections.c heredoc.c \
				 env_var.c env_var_expand.c builtin_utils.c path_utils.c
BUILT_SRC_FILES = cd.c cd_utils.c echo.c env.c exit.c export.c export_display.c export_env.c pwd.c unset.c
UTILS_SRC_FILES = utils.c cleanup.c cleanup_utils.c

SRC = $(addprefix $(MAIN_DIR)/, $(MAIN_SRC_FILES)) \
		$(addprefix $(PARSE_DIR)/, $(PARSE_SRC_FILES)) \
		$(addprefix $(EXEC_DIR)/, $(EXEC_SRC_FILES)) \
		$(addprefix $(BUILT_DIR)/, $(BUILT_SRC_FILES)) \
		$(addprefix $(UTILS_DIR)/, $(UTILS_SRC_FILES))
OBJ = $(addprefix $(MAIN_OBJ_DIR)/, $(MAIN_SRC_FILES:.c=.o)) \
		$(addprefix $(PARSE_OBJ_DIR)/, $(PARSE_SRC_FILES:.c=.o)) \
		$(addprefix $(EXEC_OBJ_DIR)/, $(EXEC_SRC_FILES:.c=.o)) \
		$(addprefix $(BUILT_OBJ_DIR)/, $(BUILT_SRC_FILES:.c=.o)) \
		$(addprefix $(UTILS_OBJ_DIR)/, $(UTILS_SRC_FILES:.c=.o))

LIBFT_DIR = ./libft
PRINTF_DIR = ./libft/ft_printf
INCLUDE = -I./include -I$(LIBFT_DIR)

CFLAGS = -Wall -Werror -Wextra $(INCLUDE) -g
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft -lreadline

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -L$(PRINTF_DIR) -lftprintf -o $(NAME) -g

$(MAIN_OBJ_DIR)/%.o: $(MAIN_DIR)/%.c
	@mkdir -p $(MAIN_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(PARSE_OBJ_DIR)/%.o: $(PARSE_DIR)/%.c
	@mkdir -p $(PARSE_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC_OBJ_DIR)/%.o: $(EXEC_DIR)/%.c
	@mkdir -p $(EXEC_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILT_OBJ_DIR)/%.o: $(BUILT_DIR)/%.c
	@mkdir -p $(BUILT_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(UTILS_OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(UTILS_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(MAKE) -C $(LIBFT_DIR) clean
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -f $(NAME)
		$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
