/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/07 21:15:24 by isang-yun        ###   ########.fr       */
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
	info->is_error = 0;
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_info	info;

	atexit(check_leak);
	(void)argc;
	(void)argv;
	init_info(&info, env);
	// while (!info.is_error)
	// {
	// 	input = readline("pmshell> :$ ");
	// 	if (!ft_strcmp(input, "exit"))
	// 		exit (0);
	// 	add_history(input);
	// 	lexical_analysis(&info, input);
	// 	free(input);
	// }
	input = readline("pmshell> :$ ");
	if (!ft_strcmp(input, "exit"))
		exit (0);
	add_history(input);
	lexical_analysis(&info, input);
	free(input);
	env_listclear(&info.env_list);
	return (0);
}
