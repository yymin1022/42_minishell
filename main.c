/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/21 16:37:17 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

int	g_status_code;

void	check_leak(void)
{
	system("leaks minishell");
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
		cmd_list = make_cmdlist(token_list);
		run_cmd_list(cmd_list, info.env_list);
		token_listclear(&token_list);
		cmd_listclear(&cmd_list);
	}
	env_listclear(&(info.env_list));
	return (0);
}
