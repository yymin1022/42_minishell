/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 02:54:31 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/02 03:27:52 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

void	exit_no_path(char *cmd)
{
	int	is_dir;

	is_dir = 0;
	ft_putstr_fd("pmshell: ", 2);
	if (access(cmd, X_OK) == 0 && ++is_dir)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": is a directory", 2);
	}
	else
		perror(cmd);
	if (is_dir)
		exit(126);
	exit(127);
}

void	exit_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Command not found", 2);
	exit(127);
}

void	exit_err(char *cmd, int err)
{
	ft_putstr_fd("pmshell: ", 2);
	perror(cmd);
	exit(err);
}
