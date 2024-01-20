/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:37:39 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/20 16:32:12 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PM_SHELL_H
# define PM_SHELL_H
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

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
}t_info;

//SECTION - lexical_analysis
/*NOTE 
	TOKEN_TYPE_CHUNK,// 해석될 여지가 아직 존재하는 단계
	TOKEN_TYPE_ARGV,// 더이상 해석할 수 없는 단계
	TOKEN_TYPE_SPACE,// 빈칸
	TOKEN_TYPE_PIPELINE,// 파이프
	TOKEN_TYPE_REDIRECTION// 리다이렉션
*/
typedef enum e_token_type
{
	TOKEN_TYPE_CHUNK,
	TOKEN_TYPE_ARGV,
	TOKEN_TYPE_SPACE,
	TOKEN_TYPE_PIPELINE,
	TOKEN_TYPE_REDIRECTION
}t_token_type;

/*NOTE  
	type: 해당 토큰의 타입
	str: 해당 토큰의 문자열
	next: 다음 토큰을 가리킴
*/
typedef struct s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*next;
}t_token;

t_token		*lexical_analysis(t_info *info, char *s);
void		handle_heredoc(t_info *info, t_token *token_list);

int			is_tokenable_sep(char c);
t_token		*token_createnew(char *token_str, t_token_type token_type);
t_token		*token_pushback(t_token **lst, t_token *new);
void		token_listclear(t_token **lst);
t_token		*token_delete(t_token **lst, t_token *token);

t_env		*make_envlist(char **env);
t_env		*env_createnew(char *s);
void		env_pushback(t_env **lst, t_env *new_node);
void		env_listclear(t_env **lst);

void		handle_quote(t_info *info, t_token *token_list);
char		*handle_double_quote_with_env(t_info *info, char *s);
int			set_dollor_idx(char *s, int *dollor_idx, int *next_idx);
char		*find_value_in_env(t_info *info, char *s);

void		handle_env(t_info *info, t_token *token_list);

void		handle_seperator(t_token *token_list, char *sep);

size_t		ft_strcmp(char *src, char *dst);
void		p_list(t_env *list);
void		free_2d_str_array(char **arr);
void		four_times_free(char *s1, char *s2, char *s3, char *s4);

//!SECTION syntax_analysis
int			syntax_analysis(t_token *token_list);

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

int			cmd_pwd(void);

#endif
