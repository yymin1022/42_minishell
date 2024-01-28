/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:38:37 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/30 13:45:21 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXEC_H
# define CMD_EXEC_H
# include "../pm_shell.h"

typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;

char	*get_full_path_cmd(char *cmd, char **env_path);
void	cmd_wait_child(pid_t pid_parent, int cmd_cnt);
void	exec_multiple_cmd(t_cmd *cmd, t_env *env_list, int cmd_cnt);
void	exec_single_cmd(t_cmd *cmd, t_env *env_list);
void	exec_cmd_list(t_cmd *cmd_list, t_env *env_list);
void	exec_heredoc(t_cmd *cmd_list, t_env *env_list);
void	unlink_heredoc_tmp(t_cmd *cmd_list);
#endif
