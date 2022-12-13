# ubuntu ubuntu 20.04 amd64
# FROM	ubuntu@sha256:450e066588f42ebe1551f3b1a535034b6aa46cd936fe7f2c6b0d72997ec61dbd
FROM 	ubuntu:20.04

# set env must be changed
ARG		git_user_name=111509163+enogawa@users.noreply.github.com
ARG		git_user_email=enogawa
WORKDIR	/root

# set env not need to be changed
ARG		user_name=minishell
ARG		user_password=password
ARG		TZ=Asia/Tokyo
ENV		LANG=en_US.UTF-8
ENV		LANGUAGE=en_US.UTF-8
# ENV		salt=oJKHGEjbCDrWIWlgi8zSm2lJqizbvGhl
# salt is random strings of characters that make it difficult to break passwords

# set unminimize
RUN		yes | unminimize

# set timezone, language
RUN		ln -snf /usr/share/zoneinfo/${TZ} /etc/localtime \
		&& echo ${TZ} > /etc/timezone

# install apt package
RUN		apt update			\
		&&	apt upgrade -y	\
		&&	apt install -y	\
			bc				\
			bash-completion	\
			clang			\
			curl			\
			gcc				\
			git				\
			less			\
			libreadline-dev	\
			make			\
			man-db			\
			python3			\
			python3-pip		\
			python3			\
			sudo			\
			tzdata			\
			unzip			\
			valgrind		\
			vim				\
			xsel

# install python package
RUN		python3 -m pip install norminette \
		&& python3 -m pip install c-formatter-42

# create user
RUN		useradd --create-home --home-dir /home/${user_name} --shell /bin/bash -p $(perl -e "print crypt(${user_password}, '\$6\$gvndskjfpgafjsdakljgioreio')") -G sudo ${user_name}

# install github-cl
RUN		curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg \
		&& sudo chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg \
		&& echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
		&& sudo apt update \
		&& sudo apt install gh -y

# set gitconfig
COPY	.gitconfig /root/
RUN		git config --global user.name ${git_user_name} \
		&& git config --global user.email ${git_user_email}

# set ssh-key
COPY	config /root/.ssh/
RUN		ssh-keygen -q -f ~/.ssh/id_rsa_github -t rsa -N "" 
RUN		ssh-keygen -q -f ~/.ssh/id_rsa_42 -t rsa -N ""

# copy rsa_key
COPY	id_rsa_42 /root/.ssh/id_rsa_42
COPY	id_rsa_42.pub /root/.ssh/id_rsa_42.pub
COPY	id_rsa_github /root/.ssh/id_rsa_github
COPY	id_rsa_github.pub /root/.ssh/id_rsa_github.pub

# git clone minishell
RUN		git clone --recurse-submodules https://github.com/yuki-shimoda-crypto/42_minishell.git minishell

# set .bashrc
COPY	.bashrc /root/
