/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:44:59 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/04 17:01:02 by sangylee         ###   ########.fr       */
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

void	handle_heredoc_with_limiter(t_token **token_list)
{
	int		start_idx;
	char	*token_str;
	char	*str;

	token_str = (*token_list)->str;
	start_idx = 0;
	while (token_str[start_idx] && ft_strncmp(token_str + start_idx, "<<", 2))
		start_idx++;
	if (token_str[start_idx] == '\0')
		return ;
	start_idx += 2;
	str = ft_substr(token_str, 0, start_idx);
	token_pushback(token_list, token_createnew(str, TOKEN_TYPE_CHUNK));
	while (token_str[start_idx] && token_str[start_idx] == ' ')
		start_idx++;
	str = ft_substr(token_str, start_idx, ft_strlen(token_str) - start_idx);
	token_pushback(token_list, token_createnew(str, TOKEN_TYPE_CHUNK));
	token_list_delfront(token_list);
}

void	handle_heredoc(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == TOKEN_TYPE_CHUNK)
			handle_heredoc_with_limiter(&token_list);
		print_list(token_list);
		token_list = token_list->next;
	}
}

void	lexical_analysis(char *str)
{
	t_token	*token_list;

	token_list = token_createnew(ft_strdup(str), TOKEN_TYPE_CHUNK);
	handle_heredoc(token_list);
}
