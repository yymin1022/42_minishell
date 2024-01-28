/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:38:37 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/30 13:41:09 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXEC_H
# define CMD_EXEC_H
# include "../pm_shell.h"

typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;

void	exec_multiple_cmd(t_cmd *cmd, t_env *env_list);
void	exec_single_cmd(t_cmd *cmd, t_env *env_list);
void	exec_cmd_list(t_cmd *cmd_list, t_env *env_list);
void	exec_heredoc(t_cmd *cmd_list, t_env *env_list);
void	unlink_heredoc_tmp(t_cmd *cmd_list);
#endif
