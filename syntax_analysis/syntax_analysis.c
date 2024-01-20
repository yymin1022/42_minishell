/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:35:37 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/14 21:07:19 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

int	check_pipe_syntax(t_token *token_list)
{
	t_token	*prev;

	prev = 0;
	while (token_list)
	{
		if (token_list->type == TOKEN_TYPE_PIPELINE
			&& (prev == 0 || token_list->next == 0
				|| token_list->next->type == TOKEN_TYPE_PIPELINE))
			return (0);
		prev = token_list;
		token_list = token_list->next;
	}
	return (1);
}

int	check_redirection_syntax(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == TOKEN_TYPE_REDIRECTION
			&& (token_list->next == 0
				|| token_list->next->type != TOKEN_TYPE_ARGV))
			return (0);
		token_list = token_list->next;
	}
	return (1);
}

int	syntax_analysis(t_token *token_list)
{
	if (check_pipe_syntax(token_list)
		&& check_redirection_syntax(token_list))
		return (1);
	return (0);
}
