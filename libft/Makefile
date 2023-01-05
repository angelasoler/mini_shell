NAME = ../libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRC =	ft_itoa.c \
		ft_atoi.c \
		ft_toupper.c \
		ft_strlen.c \
		ft_strjoin.c \
		ft_strdup.c \
		ft_strchr.c \
		ft_split.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_strncmp.c \
		ft_calloc.c \
		ft_bzero.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_printf.c \
		ft_printf_other_convs.c \
		ft_printf_int_convs.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_strlcpy.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstadd_back.c \
		ft_lstnew.c \
		ft_memcpy.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isspace.c \
		ft_isredirect.c \
		ft_memset.c

OBJ=$(SRC:.c=.o)

all: $(NAME)
	@make clean

$(NAME): $(OBJ)
	@ar -r $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

re: fclean all
	@make clean

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf *.o
