/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/05 03:02:39 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

int	g_status_code;

void	check_leak(void)
{
	system("leaks minishell");
}

void	init_termios(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	init_info(t_info *info, int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	info->env_list = make_envlist(env);
	info->is_error = 0;
	init_sig_handler();
	init_termios();
}

int	check_input(char *input)
{
	char	*tmp;

	if (!input)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(1);
	}
	tmp = ft_strtrim(input, " ");
	if (ft_strlen(input) == 1 && input[0] != ' ')
	{
		free(tmp);
		return (0);
	}
	if (tmp[0] == '\0')
	{
		four_times_free(tmp, input, 0, 0);
		return (1);
	}
	free(tmp);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_info	info;
	t_token	*token_list;
	t_cmd	*cmd_list;

	//atexit(check_leak);
	init_info(&info, argc, argv, env);
	while (!info.is_error)
	{
		input = readline("pmshell> :$ ");
		if (check_input(input))
			continue ;
		token_list = lexical_analysis(&info, input);
		if (!syntax_analysis(token_list))
		{
			ft_putstr_fd("pm_shell: invalid syntax\n", STDERR_FILENO);
			token_listclear(&token_list);
			continue ;
		}
		cmd_list = make_cmdlist(token_list);
		exec_cmd_list(cmd_list, info.env_list);
		token_listclear(&token_list);
		cmd_listclear(&cmd_list);
	}
	env_listclear(&(info.env_list));
	return (0);
}
