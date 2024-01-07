/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/07 09:35:39 by sangylee         ###   ########.fr       */
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

void	p_list(t_env *list)
{
	while (list)
	{
		printf("%s %s\n", list->key, list->value);
		list = list->next;
	}
	printf("-----------------\n");
}

void	init_info(t_info *info, char **env)
{
	info->env_list = make_envlist(env);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_info	info;

	atexit(check_leak);
	argc = 0;
	argv = NULL;
	init_info(&info, env);
	p_list(info.env_list);
	while (1)
	{
		input = readline("pmshell> :$ ");
		if (!ft_strcmp(input, "exit"))
			exit (0);
		add_history(input);
		lexical_analysis(input);
		free(input);
	}
	return (0);
}
