# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 16:52:00 by yshimoda          #+#    #+#              #
#    Updated: 2022/12/05 00:11:13 by yshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra
INCLUDE			=	-I include

SRCS			=	src/main.c
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR		=	libft
OBJ_DIR			=	obj

all:			$(NAME)	

$(NAME):		$(OBJS)
				make -C $(LIBFT_DIR)
				$(CC) -o $(NAME) $(OBJS) -L $(LIBFT_DIR) -lft

$(OBJ_DIR)/%.o:%.c
				@mkdir -p $(@D)
				$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

clean:			
				make fclean -C $(LIBFT_DIR)
				$(RM) -r $(OBJ_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
