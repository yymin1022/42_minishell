/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/21 15:51:59 by yonyoo           ###   ########seoul.kr  */
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
		while (cmd_list->argv && cmd_list->argv[i])
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

int	is_builtin(char **argv, t_env *env_list)
{
	if (!(argv[0]))
		return (0);
	else if (!ft_strcmp(argv[0], "cd"))
		return (printf("cd\n"));
	else if (!ft_strcmp(argv[0], "echo"))
		return (printf("echo\n"));
	else if (!ft_strcmp(argv[0], "env"))
		return (cmd_env(env_list));
	else if (!ft_strcmp(argv[0], "exit"))
		exit (0);
	else if (!ft_strcmp(argv[0], "export"))
		return (printf("export\n"));
	else if (!ft_strcmp(argv[0], "pwd"))
		return (cmd_pwd());
	else if (!ft_strcmp(argv[0], "unset"))
		return (printf("unset\n"));
	return (0);
}

void	run_cmd(char **argv, t_env *env_list)
{
	if (!argv || !(argv[0]))
		return ;
	if (!is_builtin(argv, env_list))
	{
		// 환경변수에서 실행
	}
}

void	run_cmd_list(t_cmd *cmd_list, t_env *env_list)
{
	while (cmd_list)
	{
		if (cmd_list->argv)
			run_cmd(cmd_list->argv, env_list);
		cmd_list = cmd_list->next;
	}
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
	struct termios term;

	atexit(check_leak);
	(void)argc;
	(void)argv;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	init_info(&info, env);
	register_sig_handler();
	while (!info.is_error)
	{
		tmp = readline("pmshell> :$ ");
		input = ft_strtrim(tmp, " ");
		if (input[0] == '\0')
		{
			four_times_free(tmp, input, 0, 0);
			info.is_error = 1;
			ft_putstr_fd("pm_shell: invalid syntax\n", STDERR_FILENO);
			env_listclear(&(info.env_list));
			continue ;
		}
		free(tmp);
		add_history(input);
		token_list = lexical_analysis(&info, input);
		free(input);
		if (!syntax_analysis(token_list))
		{
			info.is_error = 1;
			ft_putstr_fd("pm_shell: invalid syntax\n", STDERR_FILENO);
			token_listclear(&token_list);
			env_listclear(&(info.env_list));
			continue ;
		}
		//print_list(token_list);
		cmd_list = make_cmdlist(token_list);
		//print_cmd_list(cmd_list);
		run_cmd_list(cmd_list, info.env_list);
		token_listclear(&token_list);
		cmd_listclear(&cmd_list);
	}
	env_listclear(&(info.env_list));
	return (0);
}

/*
	while (!info.is_error)
	{
		input = readline("pmshell> :$ ");
		if (!ft_strcmp(input, "exit"))
			exit (0);
		add_history(input);
		lexical_analysis(&info, input);
		free(input);
	}
*/
