FROM ubuntu:20.04

ENV user_name=a
ENV user_email=a
ENV TZ=Asia/Tokyo
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update && \
	apt upgrade -y && \
	export LANG=en_US.UTF-8 && \
	export LANGUAGE=en_US.UTF-8 && \
	apt install -y \
	bc \
	clang \
	curl \
	gcc \
	git \
	less \
	make \
	man-db \
	python3 \
	python3-pip \
	python3 \
	sudo \
	tzdata \
	unzip \
	valgrind \
	vim

RUN useradd --create-home --home-dir /home/minishell --shell /bin/bash -p $(perl -e 'print crypt("password", "\$6\$gvndskjfpgafjsdakljgioreio")') -G sudo minishell && \
	python3 -m pip install norminette && \
	python3 -m pip install c-formatter-42 && \
	curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg && \
	sudo chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg && \
	echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null && \
	sudo apt update && \
	sudo apt install gh -y && \
	git config --global user.name $user_name && \
	git config --global user.email $user_email
