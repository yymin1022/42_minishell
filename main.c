/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/04 15:07:35 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

void	check_leak(void)
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
		if (!ft_strcmp(input, "exit"))
			exit (0);
		add_history(input);
		lexical_analysis(input);
		free(input);
	}
	argc = 0;
	argv = NULL;
	env = NULL;
	return (0);
}
