/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:32:05 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/03 16:22:45 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H
# include <stdlib.h>
# include <unistd.h>
//bonus
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