# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 16:52:00 by yshimoda          #+#    #+#              #
#    Updated: 2022/12/12 02:40: by yshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc

NAME			=	minishell
CFLAGS			=	-Wall -Werror -Wextra
CFLAGS_DEBUG	=	-g -fsanitize=address -fsanitize=leak -fsanitize=undefined
INCLUDE			=	-I include

SRCS			=	src/main.c

OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

OBJ_DIR			=	obj

LIBS			=	-lreadline

$(OBJ_DIR)/%.o:%.c
				@mkdir -p $(@D)
				$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@  

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

PHONY			=	all
all:			$(NAME)	

PHONY			+=	clean
clean:			
				# make fclean -C $(LIBFT_DIR)
				$(RM) -r $(OBJ_DIR)

PHONY			+=	fclean
fclean:			clean
				$(RM) $(NAME)

PHONY			+=	re
re:				fclean all

PHONY			+=	debug
debug:			CFLAGS += $(CFLAGS_DEBUG)
debug:			re

PHONY			+=	valgrind
valgrind:		all
				valgrind --log-file=$(PWD)/log.txt --leak-check=full --tool=memcheck --leak-check=yes --show-reachable=yes ./$(NAME)
				@cat log.txt | grep -A 3 "HEAP SUMMARY"
				@cat log.txt | grep -A 6 "LEAK SUMMARY"

PHONY			+=	leak
leak:			all
				while [ 1 ];			\
				do leaks -q minishell;	\
				sleep 1;				\
				done

PHONY			+=	test
test:			all
				./$(NAME) < test.txt

.PHONY:			$(PHONY)
