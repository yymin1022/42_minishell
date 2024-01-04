/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:37:39 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/04 14:42:56 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PM_SHELL_H
# define PM_SHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>

//lexical_analysis
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

t_list		*token_createnew(void *content);
int			token_listsize(t_list *lst);
void		token_pushback(t_list **lst, t_list *new);
void		token_listclear(t_list **lst, void (*del)(void *));

#endif
