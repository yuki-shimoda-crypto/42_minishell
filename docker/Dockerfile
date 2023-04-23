FROM 	ubuntu:20.04

WORKDIR	/app

# Set environment variables that don't need to be changed
ARG		TZ=Asia/Tokyo
ENV		LANG=en_US.UTF-8
ENV		LANGUAGE=en_US.UTF-8
ENV		DISPLAY=:0

# set unminimize
RUN		yes | unminimize

# Set timezone, language
RUN		ln -snf /usr/share/zoneinfo/${TZ} /etc/localtime && echo ${TZ} > /etc/timezone

# Install apt packages
RUN		apt update	&&		\
		apt upgrade -y &&	\
		apt install -y bash-completion build-essential ccache ctags curl git libreadline-dev man-db python3 python3-pip sudo tzdata unzip valgrind vim xsel

# Git clone minishell
RUN		git clone --recurse-submodules https://github.com/yuki-shimoda-crypto/42_minishell.git minishell

# Install Python packages
RUN		python3 -m pip install norminette && \
		python3 -m pip install c-formatter-42

# Install Github-CLI
RUN		curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg \
		&& chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg \
		&& echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
		&& apt update \
		&& apt install gh -y

# # Set ssh-key
# RUN		ssh-keygen -q -f ~/.ssh/id_rsa_github -t rsa -N "" 
# RUN		ssh-keygen -q -f ~/.ssh/id_rsa_42 -t rsa -N ""

# # Create a new user with the same UID and GID as your host user
# ARG USER_ID
# ARG GROUP_ID
# RUN groupadd -g ${GROUP_ID} appuser && \
#     useradd -u ${USER_ID} -g ${GROUP_ID} -m -s /bin/bash appuser && \
# 	echo "appuser ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
# 
# # Set the default user and command to run when starting the container
# USER appuser

CMD ["bash"]
