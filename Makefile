# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 19:04:11 by ssoeno            #+#    #+#              #
#    Updated: 2024/06/16 10:50:16 by ssoeno           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3 -MMD -MP

PRINTF = ft_printf
LIBFT = $(PRINTF)/libft
MLX = minilibx/libmlx.a

SRC_DIR = src/
SRCS = $(SRC_DIR)main.c $(SRC_DIR)events.c $(SRC_DIR)init.c $(SRC_DIR)render.c $(SRC_DIR)render_utils.c
DEPS=$(SRCS:.cpp=.d)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

-include $(OBJS:.o=.d)

$(NAME): $(OBJS) $(PRINTF)/libftprintf.a $(MLX)
	# $(CC) $(OBJS)  -Lft_printf/libft -lft -Lminilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	$(CC) $(OBJS)  -L$(PRINTF) -lftprintf -Lminilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(PRINTF)/libftprintf.a:
	make -C $(PRINTF)

$(MLX):
	make -C minilibx

%.o: %.c
	$(CC) $(CFLAGS) -I$(PRINTF) -I./minilibx -c $< -o $@

clean:
	make -C $(PRINTF) clean
	make -C minilibx clean
	${RM} ${OBJS}

fclean: clean
	make -C $(PRINTF) fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re