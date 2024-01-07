/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:44:59 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/07 11:03:39 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

void	print_list(t_token *token_list)
{
	while (token_list)
	{
		printf("%s\n", token_list->str);
		token_list = token_list->next;
	}
	printf("-----------------\n");
}

void	lexical_analysis(t_info *info, char *s)
{
	t_token	*token_list;

	token_list = token_createnew(ft_strdup(s), TOKEN_TYPE_CHUNK);
	handle_heredoc(info, token_list);
	print_list(token_list);
	handle_quote(info, token_list);
	token_listclear(&token_list);
}
