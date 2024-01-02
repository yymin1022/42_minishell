/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/02 17:51:45 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

void	check_leak()
{
	system("leaks minishell");
}

size_t	ft_strcmp(char *src, char *dst)
{
	size_t	i;

	i = 0;
	while (src[i] && dst[i] && src[i] == dst[i])
		i++;
	return (src[i] - dst[i]);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;

	atexit(check_leak);
	while (1)
	{
		input = readline("pmshell> :$ ");
		printf("Wa Sans %s\n", input);
		if (!ft_strcmp(input, "exit"))
			exit (0);
		add_history(input);
		free(input);
	}
	argc = 0;
	argv = NULL;
	env = NULL;
	return (0);
}
