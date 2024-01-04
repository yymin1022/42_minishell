/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:44:59 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/04 16:00:07 by sangylee         ###   ########.fr       */
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
}

void	handle_heredoc_with_limiter(t_token *token_list)
{
	int		heredoc_start;
	char	*str;

	str = token_list->str;
	heredoc_start = 0;
	while (str[heredoc_start] && ft_strncmp(str + heredoc_start, "<<", 2))
		heredoc_start++;
	if (str[heredoc_start] == '\0')
		return ;
	print_list(token_list);
	print_list(token_list);
}

void	handle_heredoc(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == TOKEN_TYPE_CHUNK)
			handle_heredoc_with_limiter(token_list);
		token_list = token_list->next;
	}
}

void	lexical_analysis(char *str)
{
	t_token	*token_list;

	token_list = token_createnew(str, TOKEN_TYPE_CHUNK);
	handle_heredoc(token_list);
}
