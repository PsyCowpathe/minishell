# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agirona <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 18:29:21 by agirona           #+#    #+#              #
#    Updated: 2021/11/25 16:41:15 by agirona          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = debug.c instruction.c lst_cmd_utils.c lst_inst_utils.c main.c utility.c \
	   command.c

SRCS_DIR = src

OBJS = $(SRCS:.c=.o)

OBJS_DIR = obj

OBJS_PATH = $(addprefix $(OBJS_DIR)/, $(OBJS))

INC	= include

LIBRARY = libft/libft.a

CFLAGS	= -Wall -Wextra -Werror -I $(INC)

RLIB	= -L/usr/lib/ -lreadline

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INC)/minishell.h $(LIBRARY)
	gcc $(CFLAGS) -c $< -o $@

all: create_obj_dir lib $(NAME)

lib:
			make -C ./libft/

$(NAME) :	$(OBJS_PATH)
			gcc $(FRAMEWORK) $(OBJS_PATH) $(LIBRARY) $(RLIB) -o $(NAME)

create_obj_dir :
			rm -f obj || true
			mkdir -p obj

clean:
			rm -f $(OBJS_PATH)
			make -C ./libft clean

fclean:
			rm -f $(OBJS_PATH)
			rm -f $(NAME)
			rm -rf obj
			make -C ./libft fclean

re:			fclean all

.PHONY:		all lib create_obj_dir clean fclean re
