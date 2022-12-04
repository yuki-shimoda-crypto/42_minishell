FROM ubuntu:20.04

RUN apt update && \
	apt upgrade  -y && \
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
	unzip \
	valgrind \
	vim && \
	useradd --create-home --home-dir /home/minishell --shell /bin/bash -p $(perl -e 'print crypt("password", "\$6\$gvndskjfpgafjsdakljgioreio")') -G sudo minishell && \
	python3 -m pip install norminette && \
	python3 -m pip install c-formatter-42 && \
	curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg && \
	sudo chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg && \
	echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null && \
	sudo apt update && \
	sudo apt install gh -y && \
	git config --global user.name "" && \
	git config --global user.email "" 
