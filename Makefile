# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 19:04:11 by ssoeno            #+#    #+#              #
#    Updated: 2024/05/25 15:11:14 by ssoeno           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fract-ol

CC = gcc
CFLAGS = -Wall -Werror -Wextra

PRINTF = ft_printf/libftprintf.a
LIBFT = $(PRINTF)/libft
MLX = minilibx/libmlx.a

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF) $(MLX)
	$(CC) $(OBJS)  -Lft_printf/libft -lft -Lminilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME)


%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

clean:
	make -C $(PRINTF) clean
	${RM} ${OBJS}

fclean: clean
	make -C $(PRINTF) fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re