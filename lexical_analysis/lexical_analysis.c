/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:44:59 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/11 00:03:01 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

void	print_list(t_token *token_list)
{
	while (token_list)
	{
		printf("%s %d\n", token_list->str, token_list->type);
		token_list = token_list->next;
	}
	printf("-----------------\n");
}

void	lexical_analysis(t_info *info, char *s)
{
	t_token	*token_list;

	token_list = token_createnew(s, TOKEN_TYPE_CHUNK);
	handle_heredoc(info, token_list);
	print_list(token_list);
	handle_quote(info, token_list);
	print_list(token_list);
	handle_env(info, token_list);
	print_list(token_list);
	token_listclear(&token_list);
}
