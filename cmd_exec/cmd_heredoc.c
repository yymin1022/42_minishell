/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:18:17 by isang-yun         #+#    #+#             */
/*   Updated: 2024/01/29 10:29:05 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

extern int	g_status_code;

static void	handle_env_in_heredoc(char *input, int fd, t_env *env)
{
	int		start;
	int		end;
	char	*env_value;

	start = 0;
	end = 0;
	while (input[end])
	{
		if (input[end] == '$')
		{
			write(fd, input + start, end - start);
			start = end;
			// env_value = 
		}
	}
}

static void	create_tmpfile(char *file_name, char *delimiter, t_env *env_list)
{
	int		fd;
	char	*input;

	fd = open(file_name, O_RDONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			ft_putstr_fd("\033[1A\033[2C", STDERR_FILENO);
		if (!input || (ft_strncmp(input, delimiter, ft_strlen(input)) == 0
				&& ft_strlen(input) == ft_strlen(delimiter)))
		{
			close(fd);
			return ;
		}
		handle_env_in_heredoc(input, fd, env_list);
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	free(input);
}

void	exec_heredoc(t_cmd *cmd_list, t_env *env_list)
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
				&& ft_strlen(cur_redirect->type) == 2)
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
