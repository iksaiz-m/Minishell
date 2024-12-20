# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/20 18:52:02 by iksaiz-m          #+#    #+#              #
#    Updated: 2024/12/20 19:11:05 by iksaiz-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR    = libft/
LIBFT        = $(LIBFT_DIR)libft.a
HEADERS      = -I $(LIBFT_DIR)
CFLAGS       = -Wall -Wextra -Werror -g -O3 -g3

NAME         = minishell
RM           = rm -rf
SRC = builtins.c

OBJS = $(SRC:.c=.o)

all: $(MINILIBX) $(LIBFT) $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)  -L$(LIBFT_DIR) -lft -lm -lX11 -lXext

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	@make -C libft clean

fclean: clean
	$(RM) $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re