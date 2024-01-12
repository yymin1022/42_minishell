/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:35:37 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/12 20:57:59 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

int	check_pipe_syntax(t_token *token_list)
{
	t_token	*prev;
	t_token	*cur;
	t_token	*next;

	cur = token_list->next;
	prev = token_list;
	next = cur->next;
	while (next)
	{
		if (!(cur->type == TOKEN_TYPE_PIPELINE
				&& prev->type != TOKEN_TYPE_PIPELINE
				&& next->type != TOKEN_TYPE_PIPELINE
				&& prev->type != next->type))
			return (0);
		prev = cur;
		cur = next;
		next = cur->next;
	}
	return (1);
}

int	check_redirection_syntax(t_token *token_list)
{
	t_token	*prev;
	t_token	*cur;
	t_token	*next;

	cur = token_list->next;
	prev = token_list;
	next = cur->next;
	while (next)
	{
		if (!(cur->type == TOKEN_TYPE_REDIRECTION
				&& prev->type == TOKEN_TYPE_ARGV
				&& next->type == TOKEN_TYPE_ARGV))
			return (0);
		prev = cur;
		cur = next;
		next = cur->next;
	}
	return (1);
}

int	syntax_analysis(t_token *token_list)
{
	t_token	*tmp;
	int		cnt;

	cnt = 0;
	tmp = token_list;
	while (tmp)
	{
		tmp = tmp->next;
		cnt++;
	}
	if (cnt == 1 && token_list->type == TOKEN_TYPE_ARGV)
		return (1);
	else if (cnt == 2 && token_list->type == TOKEN_TYPE_ARGV
		&& token_list->next->type == TOKEN_TYPE_ARGV)
		return (1);
	else if (cnt >= 3 && check_pipe_syntax(token_list)
		&& check_redirection_syntax(token_list))
		return (1);
	return (0);
}
