/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/02 12:13:17 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

int	g_status_code;

void	check_leak(void)
{
	system("leaks minishell");
}

void	init_info(t_info *info, char **env)
{
	info->env_list = make_envlist(env);
	info->is_error = 0;
}

void	init_termios(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
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
	init_sig_handler();
	init_termios();
	while (!info.is_error)
	{
		tmp = readline("pmshell> :$ ");
		if (!tmp)
			exit(0);
		input = ft_strtrim(tmp, " ");
		if (ft_strlen(tmp) == 1 && tmp[0] != ' ')
		{
			free(input);
			input = ft_strdup(tmp);
		}
		if (input[0] == '\0')
		{
			four_times_free(tmp, input, 0, 0);
			continue ;
		}
		token_list = lexical_analysis(&info, input);
		add_history(input);
		four_times_free(tmp, input, 0, 0);
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
