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

# CC				=	clang
# CFLAGS_DEBUG	=	-g -fsanitize=address -fsanitize=alignment -fsanitize=bool -fsanitize=bounds -fsanitize=builtin -fsanitize=enum -fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero -fsanitize=integer-divide-by-zero -fsanitize=leak -fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size -fsanitize=pointer-compare -fsanitize=pointer-overflow -fsanitize=pointer-subtract -fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shadow-call-stack -fsanitize=shift -fsanitize=shift-base -fsanitize=shift-exponent -fsanitize=signed-integer-overflow -fsanitize=undefined -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr

CC				=	cc
CFLAGS_DEBUG	=	-g -fsanitize=address -fsanitize=alignment -fsanitize=bool -fsanitize=bounds -fsanitize=bounds-strict -fsanitize=builtin -fsanitize=enum -fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero -fsanitize=integer-divide-by-zero -fsanitize=leak -fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size -fsanitize=pointer-compare -fsanitize=pointer-overflow -fsanitize=pointer-subtract -fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shift -fsanitize=shift-base -fsanitize=shift-exponent -fsanitize=signed-integer-overflow -fsanitize=undefined -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr

NAME			=	minishell
# CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra
# CFLAGS_DEBUG	=	-g -fsanitize=address -fsanitize=leak -fsanitize=undefined
INCLUDE			=	-I include

# SRCS			=	src/main.c				\
# 					src/lexer.c				\
# 					src/parser.c			\
# 					src/minishell_signal.c

SRCS			=	$(shell find src/ -name "*.c")

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
