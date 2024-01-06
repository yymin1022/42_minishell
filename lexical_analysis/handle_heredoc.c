/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 07:19:18 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/07 07:33:58 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

static int	handle_quote(t_token *token_list, char *s, int start)
{
	int		offset;
	char	*str;

	offset = 1;
	while (s[start + offset] && s[start + offset] != s[start])
		offset++;
	if (s[start + offset] == '\0')
		str = ft_strdup(s + start);
	else
		str = ft_substr(s, start + 1, offset - 1);
	token_pushback(&token_list, token_createnew(str, TOKEN_TYPE_ARGV));
	return (start + offset + 1);
}

static int	handle_limiter(t_token *token_list, char *s, int start)
{
	int		offset;
	char	*str;

	while (s[start] && !is_tokenable_sep(s[start]))
	{
		if (s[start] == '\'' || s[start] == '\"')
			start = handle_quote(token_list, s, start);
		else
		{
			offset = 1;
			while (s[start + offset] && !is_tokenable_sep(s[start + offset])
				&& s[start + offset] != '\''
				&& s[start + offset] != '\"')
					offset++;
			str = ft_substr(s, start, offset);
			token_pushback(&token_list, token_createnew(str, TOKEN_TYPE_ARGV));
			start += offset;
		}
	}
	return (start);
}

static void	handle_heredoc_with_limiter(t_token *token_list)
{
	int		start_idx;
	char	*token_str;
	char	*str;

	token_str = ft_strdup(token_list->str);
	start_idx = 0;
	while (token_str[start_idx] && ft_strncmp(token_str + start_idx, "<<", 2))
		start_idx++;
	if (token_str[start_idx] == '\0')
		return ;
	start_idx += 2;
	free(token_list->str);
	token_list->str = ft_substr(token_str, 0, start_idx);
	while (token_str[start_idx] && token_str[start_idx] == ' ')
		start_idx++;
	start_idx = handle_limiter(token_list, token_str, start_idx);
	if (ft_strlen(token_str) - start_idx == 0)
	{
		free(token_str);
		return ;
	}
	str = ft_substr(token_str, start_idx, ft_strlen(token_str) - start_idx);
	token_pushback(&token_list, token_createnew(str, TOKEN_TYPE_CHUNK));
	free(token_str);
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
