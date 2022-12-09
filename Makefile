# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 16:52:00 by yshimoda          #+#    #+#              #
#    Updated: 2022/12/10 00:54:40 by yshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra
CFLAGS_DEBUG	=	-g -fsanitize=address -fsanitize=leak -fsanitize=undefined
INCLUDE			=	-I include

SRCS			=	src/main.c
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

OBJ_DIR			=	obj
LIBFT_DIR		=	libft

LIBFT_LIB		=	$(addprefix $(LIBFT_DIR),/libft.a)
LIBS			=	$(LIBFT_LIB) -lreadline 

$(OBJ_DIR)/%.o:%.c
				@mkdir -p $(@D)
				$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@  

$(NAME):		$(OBJS) $(LIBFT_LIB)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(LIBFT_LIB):	
				make -C $(LIBFT_DIR)

PHONY			=	all
all:			$(NAME)	

PHONY			+=	clean
clean:			
				make fclean -C $(LIBFT_DIR)
				$(RM) -r $(OBJ_DIR)

PHONY			+=	fclean
fclean:			clean
				$(RM) $(NAME)

PHONY			+=	re
re:				fclean all

PHONY			+=	debug
debug:			CFLAGS += $(CFLAGS_DEBUG)
debug:			fclean
				make debug -C $(LIBFT_DIR)
debug:			all

.PHONY:			$(PHONY)
