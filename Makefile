ifneq (,$(findstring xterm,${TERM}))
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	RESET := $(shell tput -Txterm sgr0)
endif

define GIT =
	git add .
	git status
	read -p "${YELLOW}Commit Message:${RESET}" commit_message
	read -p "${YELLOW}Branch:${RESET}" branch
	git commit -m "$$commit_message"
	git push origin $$branch
endef

NAME = minishell

CC = cc

WFLAGS = -Wall -Werror -Wextra

READ_FLAG = -lreadline

LIBFT = libft.a

SRC =	_minishell_/minishell.c \
		_minishell_/prompt.c \
		environment/clear_utils.c \
		environment/alloc_env_hash.c \
		environment/manage_env_structure.c \
		environment/get_env_var.c \
		environment/set_exec_path.c \
		parser/build_cmd_structure.c \
		parser/build_cmd_structure_utils.c \
		parser/print_structures.c \
		parser/create_structures.c \
		parser/clear_structures.c \
		parser/set_cmd_attributes.c \
		parser/ft_split_but_through_quotes.c \
		parser/parsers.c \
		parser/expansions_call.c \
		parser/expansions_exec.c \
		parser/expansions_utils.c \
		executer/executer.c \
		executer/fd_utils.c \
		executer/processes.c \
		executer/access_utils.c \
		executer/heredoc.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/unset.c \
		builtins/env.c \
		builtins/cd.c \
		builtins/builtins_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
	@make clean

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(YELLOW)creating ./minishell$(RESET)"
	@$(CC) $(WFLAGS) -g3 $(OBJ) $(READ_FLAG) -L ./ -lft -o $(NAME)

%.o: %.c
	@$(CC) -g3 $(WFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

re: fclean all
	@make clean

fclean: clean
	rm -rf $(NAME)

clean:
	@rm -rf _minishell_/*.o
	@rm -rf environment/*.o
	@rm -rf parser/*.o
	@rm -rf executer/*.o
	@rm -rf builtins/*.o

fclean_all: fclean
	make fclean -C libft

check:
	dev_utils/run_pr_check.sh

commit: fclean_all
	@$(GIT)

.PONHY: re fclean clean all

.ONESHELL:
