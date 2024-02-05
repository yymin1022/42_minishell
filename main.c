/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/05 20:28:53 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

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
	info->status_code = 0;
	info->stdin_fd = dup(STDIN_FILENO);
	info->stdout_fd = dup(STDOUT_FILENO);
	init_sig_handler();
	init_termios();
}

int	check_input(char *input, t_info *info, struct termios *term)
{
	char	*tmp;

	info->tmp_cnt = 0;
	if (g_signo == SIGINT)
		info->status_code = 1;
	g_signo = 0;
	if (!input)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		tcsetattr(STDIN_FILENO, TCSANOW, term);
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
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	init_info(&info, argc, argv, env);
	while (!info.is_error)
	{
		input = readline("pmshell> :$ ");
		if (check_input(input, &info, &term))
			continue ;
		token_list = lexical_analysis(&info, input);
		if (!syntax_analysis(token_list))
		{
			ft_putstr_fd("pm_shell: invalid syntax\n", STDERR_FILENO);
			token_listclear(&token_list);
			continue ;
		}
		cmd_list = make_cmdlist(token_list);
		exec_cmd_list(cmd_list, &info);
		token_listclear(&token_list);
		cmd_listclear(&cmd_list);
	}
	env_listclear(&(info.env_list));
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}

	//atexit(check_leak);