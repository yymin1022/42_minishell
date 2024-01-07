/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/07 22:57:58 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

void	check_leak(void)
{
	system("leaks minishell");
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
	input = readline("pmshell> :$ ");
	if (!ft_strcmp(input, "exit"))
		exit (0);
	add_history(input);
	lexical_analysis(&info, input);
	free(input);
	env_listclear(&(info.env_list));
	return (0);
}

/*
	// while (!info.is_error)
	// {
	// 	input = readline("pmshell> :$ ");
	// 	if (!ft_strcmp(input, "exit"))
	// 		exit (0);
	// 	add_history(input);
	// 	lexical_analysis(&info, input);
	// 	free(input);
	// }
*/