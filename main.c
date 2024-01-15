/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/15 13:27:51 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

int	g_status_code;

void	check_leak(void)
{
	system("leaks minishell");
}

void	print_list(t_token *token_list)
{
	while (token_list)
	{
		printf("%s=%d\n", token_list->str, token_list->type);
		token_list = token_list->next;
	}
	printf("-----------------\n");
}

void	print_cmd_list(t_cmd *cmd_list)
{
	int			i;
	t_redirect	*tmp;

	while (cmd_list)
	{
		i = 0;
		tmp = cmd_list->redirect;
		printf("argv\n");
		while (cmd_list->argv[i])
			printf("%s ", cmd_list->argv[i++]);
		printf("\nredirect\n");
		while (tmp)
		{
			printf("file = %s type = %s\n", tmp->file, tmp->type);
			tmp = tmp->next;
		}
		cmd_list = cmd_list->next;
		printf("---------**-------\n");
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
	char	*tmp;
	t_info	info;
	t_token	*token_list;
	t_cmd	*cmd_list;

	atexit(check_leak);
	(void)argc;
	(void)argv;
	init_info(&info, env);
	tmp = readline("pmshell> :$ ");
	input = ft_strtrim(tmp, " ");
	free(tmp);
	if (!ft_strcmp(input, "exit") || !input)
		exit (0);
	add_history(input);
	token_list = lexical_analysis(&info, input);
	free(input);
	if (!syntax_analysis(token_list))
	{
		info.is_error = 1;
		ft_putstr_fd("pm_shell: invalid syntax\n", STDERR_FILENO);
		token_listclear(&token_list);
		env_listclear(&(info.env_list));
		return (0);
	}
	print_list(token_list);
	cmd_list = make_cmdlist(token_list);
	print_cmd_list(cmd_list);
	token_listclear(&token_list);
	env_listclear(&(info.env_list));
	cmd_listclear(&cmd_list);
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