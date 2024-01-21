/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:38:37 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/21 16:49:09 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXEC_H
# define CMD_EXEC_H
# include "../pm_shell.h"

typedef struct s_cmd	t_cmd;

void	exec_cmd_list(t_cmd *cmd_list, t_env *env_list);

#endif
