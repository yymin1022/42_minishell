/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:39:09 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/27 16:20:00 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

extern int g_status_code;

static void	exec_cmd(char **argv, t_env *env_list)
{
	if (!argv || !(argv[0]))
		return ;
	if (!is_builtin(argv, env_list))
	{
		// 환경변수에서 실행
	}
}

static void	create_tmpfile(char *file_name, char *delimiter, t_env *env_list)
{
	int	fd;

	fd = open("tmpfile", O_RDONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		ft_putstr_fd("open temp file error in heredoc\n", STDERR_FILENO);
	}
}

static void	exec_heredoc(t_cmd *cmd_list, t_env *env_list)
{
	int			file_cnt;
	char		*file_str;
	char		*file_name;
	t_redirect	*cur_redirect;

	file_cnt = 0;
	while (cmd_list)
	{
		cur_redirect = cmd_list->redirect;
		while (cur_redirect)
		{
			if (ft_strncmp(cur_redirect->type, "<<", 2)
				&& ft_strlen(cur_redirect) == 2)
			{
				file_str = ft_itoa(file_cnt);
				file_name = ft_strjoin(file_str, ".tmp");
				create_tmpfile(file_name, cur_redirect->file, env_list);
				four_times_free(file_str, file_name, 0, 0);
			}
			cur_redirect = cur_redirect->next;
		}
		file_cnt++;
		cmd_list = cmd_list->next;
	}
}

void	exec_cmd_list(t_cmd *cmd_list, t_env *env_list)
{
	exec_heredoc(cmd_list, env_list);
	while (cmd_list)
	{
		if (cmd_list->argv)
			exec_cmd(cmd_list->argv, env_list);
		cmd_list = cmd_list->next;
	}
}
