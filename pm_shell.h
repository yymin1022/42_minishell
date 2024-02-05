/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:37:39 by sangylee          #+#    #+#             */
/*   Updated: 2024/02/05 19:33:19 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PM_SHELL_H
# define PM_SHELL_H
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "built_in/built_in.h"
# include "cmd_exec/cmd_exec.h"
# include "cmd_list/cmd_list.h"
# include "lexical_analysis/lexical_analysis.h"
# include "libft/libft.h"
# include "sig_handle/sig_handle.h"
# include "syntax_analysis/syntax_analysis.h"

int	g_signo;

typedef struct s_env{
	char			*str;
	struct s_env	*next;
}t_env;

typedef struct s_info
{
	t_env	*env_list;
	int		is_error;
	int		status_code;
	int		stdin_fd;
	int		stdout_fd;
	int		tmp_cnt;
}t_info;

char	**get_env_str_list(t_env *env_list);
char	**get_path_env(t_env *env_list);
void	print_argument_err(char *str);
void	update_env(char **str, char *new);

#endif
