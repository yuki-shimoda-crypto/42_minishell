# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 21:44:51 by yshimoda          #+#    #+#              #
#    Updated: 2023/02/18 12:57:29 by yshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# !/bin/bash

cleanup()
{
	rm -f cmp out
}

assert()
{
	# show test case
	printf '%-30s:' "\"$1\""

	# save bash output to cmp
	echo -n -e "$1" | bash >cmp 2>&-
	#save bash exit status to expected
	expected=$?

	# save minishell output to out
	echo -n -e "$1" | ./minishell >out 2>&-
	#save minishell exit status to actual
	actual=$?

	# compare bash, minishell output
	diff cmp out >/dev/null && echo -n '  diff OK' || echo -n '  diff NG'

	# compare bash, minishell exit status
	if [ "$actual" = "$expected" ]; then
		echo -n '  status OK'
	else
		echo -n "  status NG, expected $expected but got $actual"
	fi
	echo
}

# Empty line (EOF)
assert ''

# Absolute path commands without arg
assert "/bin/pwd"
assert "/bin/echo"

cleanup
echo 'all OK'
