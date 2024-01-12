/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:44:59 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/12 17:01:24 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

void	print_list(t_token *token_list)
{
	while (token_list)
	{
		printf("%s=%d\n", token_list->str, token_list->type);
		token_list = token_list->next;
	}
	printf("-----------------\n");
}

void	merge_argv(t_token *cur, t_token *next)
{
	char	*res;

	res = ft_strjoin(cur->str, next->str);
	free(cur->str);
	free(next->str);
	cur->str = res;
	cur->next = next->next;
	free(next);
}

void	handle_arg(t_token *token_list)
{
	t_token	*next;
	t_token	*head;
	char	*res;

	head = token_list;
	if (head->next == 0)
		return ;
	while (token_list)
	{
		next = token_list->next;
		if (next && token_list->type == TOKEN_TYPE_ARGV
			&& next->type == TOKEN_TYPE_ARGV)
		{
			res = ft_strjoin(token_list->str, next->str);
			free(token_list->str);
			free(next->str);
			token_list->str = res;
			token_list->next = next->next;
			free(next);
		}
		else
			token_list = token_list->next;
	}
}

void	handle_chunk(t_token *token_list)
{
	t_token	*head;

	head = token_list;
	while (token_list)
	{
		if (token_list->type == TOKEN_TYPE_CHUNK)
		{
			if (token_list->str[0] != '\0')
				token_list->type = TOKEN_TYPE_ARGV;
			else
				token_list = token_delete(&head, token_list);
		}
		token_list = token_list->next;
	}
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
	handle_seperator(token_list, " ");
	handle_seperator(token_list, "|");
	handle_seperator(token_list, "<<");
	handle_seperator(token_list, ">>");
	handle_seperator(token_list, "<");
	handle_seperator(token_list, ">");
	handle_chunk(token_list);
	print_list(token_list);
	handle_arg(token_list);
	print_list(token_list);
	token_listclear(&token_list);
}
