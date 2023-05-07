# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 16:52:00 by yshimoda          #+#    #+#              #
#    Updated: 2023/05/07 15:53:02 by yshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra
CFLAGS_DEBUG	=	-g -fsanitize=address -fsanitize=undefined
INCLUDE			=	-I include
LIBS			=	-L$(LIBFT_DIR) -lft
LIBFT_DIR		=	libft

SRCS			=	src/main.c						\
					src/free.c						\
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
					src/exec/argv_utils.c			\
					src/exec/builtin_utils.c		\
					src/exec/env_utils.c			\
					src/exec/exec.c					\
					src/exec/handle_process.c		\
					src/exec/init_free.c			\
					src/exec/is.c					\
          			src/exec/is2.c					\
					src/exec/pipe_count.c			\
					src/exec/waitpid.c				\
					src/exec/make_path.c			\
					src/exec/make_path_2.c			\
					src/redirect/redirect.c			\
					src/redirect/heredoc.c			\
					src/redirect/open_file.c		\
					src/pipe/pipe.c					\
					src/pipe/pipe2.c				\
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
					src/expand/expand2.c			\
					src/expand/expand3.c			\
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
					src/builtin/cd2.c				\
					src/builtin/env.c				\
					src/builtin/unset.c				\
					src/builtin/exit.c

OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR			=	obj

# Determine OS specific settings
ifeq ($(shell uname -s), Linux)
CFLAGS_DEBUG	+=	-fsanitize=leak
SHELL			=	/bin/bash
LIBS			+=	-lreadline
else
RLDIR   		= $(shell brew --prefix readline)
LIBS			+=	-L$(RLDIR)/lib -lreadline
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
				make -C $(LIBFT_DIR)
				$(CCACHE) $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

.PHONY: all clean fclean re debug valgrind leak test build up down down-clean exec logs ps logs-compose start stop restart

# Default rule
all:			$(NAME)	

# Clean rules
clean:			
				make fclean -C $(LIBFT_DIR)
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

# norminette
norm:
	norminette include src libft

nm:
	nm -u $(NAME) | grep -v -w -E "_(access|add_history|chdir|close|closedir|dup|dup2|execve|exit|fork|free|fstat|getcwd|getenv|ioctl|isatty|kill|lstat|malloc|open|opendir|perror|pipe|printf|read|readdir|readline|rl_clear_history|rl_on_new_line|rl_redi    splay|rl_replace_line|sigaction|sigaddset|sigemptyset|signal|stat|strerror|tcgetattr|tcsetattr|tgetent|tgetflag|tgetnum|tgetstr|tgoto|tputs|ttyname|ttyslot|unlink|wait|wait3|wait4|waitpid|write)"


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

