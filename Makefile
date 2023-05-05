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

NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra
CFLAGS_DEBUG	=	-g -fsanitize=address -fsanitize=undefined
INCLUDE			=	-I include
LIBS			=

SRCS			=	src/main.c						\
					src/signal/signal.c				\
					src/debug_func.c				\
					src/error/error.c				\
					src/error/error2.c				\
					src/lexer/into_list.c			\
					src/lexer/is_01.c				\
					src/lexer/is_02.c				\
					src/lexer/tokenize.c			\
					src/parse/parse.c				\
					src/parse/parse2.c				\
					src/exec/exec.c					\
					src/exec/is.c					\
					src/exec/make_path.c			\
					src/redirect/redirect.c			\
					src/redirect/heredoc.c			\
					src/redirect/open_file.c		\
					src/pipe/pipe.c					\
					src/wrap/close.c				\
					src/wrap/dup2.c					\
					src/wrap/dup.c					\
					src/wrap/fork.c					\
					src/wrap/pipe.c					\
					src/wrap/read.c					\
					src/wrap/write.c				\
					src/wrap/getcwd.c				\
					src/wrap/chdir.c				\
					src/expand/expand.c				\
					src/expand/is_01.c				\
					src/expand/is_02.c				\
					src/builtin/recognize_builtin.c	\
					src/builtin/echo.c				\
					src/builtin/export.c			\
					src/builtin/export2.c			\
					src/env/env.c					\
					src/env/env2.c					\
					src/builtin/pwd.c				\
					src/builtin/cd.c				\
					src/builtin/env.c				\
					src/builtin/unset.c				\
					src/builtin/exit.c
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR			=	obj

# Determine OS specific settings
ifeq ($(shell uname -s), Linux)
CFLAGS_DEBUG	+=	-fsanitize=leak
SHELL			=	/bin/bash
LIBS			=	-lreadline
else
RLDIR   		= $(shell brew --prefix readline)
LIBS			=	-L$(RLDIR)/lib -lreadline
INCLUDE			+=	-I $(RLDIR)/include
endif

# Check if ccache is available
ifneq ($(shell command -v ccache), )
CCACHE			=	ccache
endif

DOCKER_IMAGE_NAME = minishell

# Object file rule
$(OBJ_DIR)/%.o:%.c
				@mkdir -p $(@D)
				$(CCACHE) $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@  

# Main build rule
$(NAME):		$(OBJS)
				$(CCACHE) $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

.PHONY: all clean fclean re debug valgrind leak test build up down down-clean exec logs ps logs-compose start stop restart

# Default rule
all:			$(NAME)	

# Clean rules
clean:			
				# make fclean -C $(LIBFT_DIR)
				$(RM) -r $(OBJ_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

# Debug rules
debug:			CFLAGS += $(CFLAGS_DEBUG)
debug:			re
				./$(NAME)

# Valgrind rule
valgrind:		all
				valgrind --log-file=$(PWD)/log.txt --leak-check=full --tool=memcheck --leak-check=yes ./$(NAME)
				@cat log.txt | grep -A 3 "HEAP SUMMARY"
				@cat log.txt | grep -A 6 "LEAK SUMMARY"

# Leak rule
leak:			all
				while [ 1 ]; do leaks -q minishell;	sleep 1; done

# Test rule
test:			CFLAGS += $(CFLAGS_DEBUG)
test:			re
				./test.sh

# Docker rules
build:
	docker compose build --build-arg HOST_HOME=${HOME}

up:
	docker compose up -d

down:
	docker compose down

down-clean:
	docker compose down --rmi all --volumes --remove-orphans

exec:
	docker exec -it $(DOCKER_IMAGE_NAME) bash

logs:
	docker logs $(DOCKER_IMAGE_NAME)

ps:
	docker ps -f "ancestor=$(DOCKER_IMAGE_NAME)"

logs-compose:
	docker compose logs

start:
	docker compose start

stop:
	docker compose stop

restart:
	docker compose restart

