/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:37:39 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/21 16:33:39 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PM_SHELL_H
# define PM_SHELL_H
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "built_in/built_in.h"
# include "lexical_analysis/lexical_analysis.h"
# include "libft/libft.h"
# include "sig_handle/sig_handle.h"
# include "syntax_analysis/syntax_analysis.h"

//SECTION - main.c

typedef struct s_env{
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_info
{
	t_env	*env_list;
	int		is_error;
}t_info;\

//!SECTION make cmd list
typedef struct s_redirect
{
	char					*type;
	char					*file;
	struct s_redirect		*next;
}	t_redirect;

typedef struct s_cmd
{
	char			**argv;
	t_redirect		*redirect;
	int				pipe[2];
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

t_cmd		*make_cmdlist(t_token *token_list);

void		cmd_listclear(t_cmd **lst);
t_cmd		*cmd_createnew(void);
t_cmd		*cmd_pushback(t_cmd **lst, t_cmd *new_node);

t_redirect	*redirect_createnew(char *file, char *type);
void		redirect_pushback(t_redirect **lst, t_redirect *new_node);
void		redirect_listclear(t_redirect **lst);

#endif
