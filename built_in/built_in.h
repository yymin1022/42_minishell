/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:57:30 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/22 19:57:53 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H
# include "../pm_shell.h"

typedef struct s_env	t_env;
typedef struct s_token	t_token;

int	cmd_env(t_env *env_list);
int	cmd_export(char **str, t_env *env_list);
int	cmd_pwd(void);
int	is_builtin(char **argv, t_env *env_list);

#endif
