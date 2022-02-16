CC = gcc -Wall -Werror -Wextra -g

NAME = push_swap

SRC = ft_atol.c  ft_lstadd_back.c  ft_lstadd_front.c  ft_lstlast.c  ft_lstsize.c \
ft_lstnew.c ft_lstclear.c ft_strlen.c push_swap.c push_swap_utils.c\
push_swap_utils2.c push_swap_utils3.c push_swap_utils4.c\

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean :
	rm -rf $(OBJ)

fclean: clean
	 rm -f $(NAME)

re: fclean all

.PHONY : all clean bonus fclean re
