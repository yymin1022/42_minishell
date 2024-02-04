/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:58:11 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/05 05:53:14 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

static int	redirect_input(t_redirect *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		exit_err(redir->file, 1);
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("dup2(stdin)");
	close(fd);
	return (1);
}

static int	redirect_output(t_redirect *redir)
{
	int	fd;

	if (ft_strcmp(redir->type, ">>") == 0)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_err(redir->file, 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("dup2(stdout)");
	close(fd);
	return (1);
}

int	redirect_io(t_cmd *cmd)
{
	int			res;
	t_redirect	*redir;

	if (cmd->redirect == NULL)
		return (1);
	redir = cmd->redirect;
	res = 1;
	while (redir && res)
	{
		if (ft_strcmp(redir->type, ">>") == 0
			|| ft_strcmp(redir->type, ">") == 0)
			res = redirect_output(redir);
		else
			res = redirect_input(redir);
		redir = cmd->next->redirect;
	}
	return (res);
}
