# ubuntu ubuntu 20.04 amd64
FROM	ubuntu@sha256:450e066588f42ebe1551f3b1a535034b6aa46cd936fe7f2c6b0d72997ec61dbd
# FROM 	ubuntu:20.04

# set env must be changed
ARG	git_user_name=yuki-shimoda-crypto
ARG	git_user_email=77478109+yuki-shimoda-crypto@users.noreply.github.com
WORKDIR	/root

# set env not need to be changed
ARG	user_name=minishell
ARG	user_password=password
ARG	TZ=Asia/Tokyo
ENV	LANG=en_US.UTF-8
ENV	LANGUAGE=en_US.UTF-8
# ENV	salt=oJKHGEjbCDrWIWlgi8zSm2lJqizbvGhl
# salt is random strings of characters that make it difficult to break passwords

# set unminimize
RUN	yes | unminimize

# set timezone, language
RUN	ln -snf /usr/share/zoneinfo/${TZ} /etc/localtime \
	&& echo ${TZ} > /etc/timezone

# install apt package
RUN	apt update \
	&&	apt upgrade -y \
	&&	apt install -y \
		bc \
		clang \
		curl \
		gcc \
		git \
		less \
		libreadline-dev \
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

# install python package
RUN	python3 -m pip install norminette \
	&& python3 -m pip install c-formatter-42

# create user
RUN	useradd --create-home --home-dir /home/${user_name} --shell /bin/bash -p $(perl -e "print crypt(${user_password}, '\$6\$gvndskjfpgafjsdakljgioreio')") -G sudo ${user_name}

# install github-cl
RUN	curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg \
	&& sudo chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg \
	&& echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
	&& sudo apt update \
	&& sudo apt install gh -y

# set gitconfig
RUN	git config --global user.name ${git_user_name} \
	&& git config --global user.email ${git_user_email}

COPY	.bashrc /root/
