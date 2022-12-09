# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 16:52:00 by yshimoda          #+#    #+#              #
#    Updated: 2022/12/09 21:53:46 by enogawa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra -lreadline
INCLUDE			=	-I include

SRCS			=	src/main.c
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR		=	libft
OBJ_DIR			=	obj

all:			$(NAME)	

$(NAME):		$(OBJS)
				make -C $(LIBFT_DIR)
				$(CC) -o $(NAME) $(OBJS) -L $(LIBFT_DIR) -lft $(CFLAGS)

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
