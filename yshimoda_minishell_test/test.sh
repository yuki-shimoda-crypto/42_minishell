# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 21:44:51 by yshimoda          #+#    #+#              #
#    Updated: 2023/02/21 12:16:35 by yshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# !/bin/bash

cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int	main(void) { printf("hello from a.out\n"); }
EOF

cat << EOF | gcc -xc -o print_args -
#include <stdio.h>
int main(int argc, char *argv[]) {
	for (int i = 0; argv[i]; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
}
EOF

cleanup()
{
	# rm -f cmp out a.out print_args
	rm -f cmp out a.out
}

assert()
{
	# show test case
	printf '%-50s:' "\"$1\""

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
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

# Search command path without args
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

## no such command
assert 'a.out'
assert 'nosuchfile'

# Tokenize
## unquoterd word
assert 'ls /'
assert 'echo hello    world     '
assert 'nosuchfile\n\n'

## single quote
assert "./print_args 'hello  world' '42Tokyo'"
assert "echo '\"hello  world\"' '42Tokyo'"

## combinatio
assert "echo hello'      world'"

cleanup
echo 'all OK'
