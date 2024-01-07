/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 07:19:18 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/07 11:01:12 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

static int	handle_quote_in_limiter(
	t_info *info, t_token *token_list, char *s, int start)
{
	int		offset;
	char	*str;

	offset = 1;
	while (s[start + offset] && s[start + offset] != s[start])
		offset++;
	if (s[start + offset] == '\0')
	{
		ft_putstr_fd("pm_shell: quotes error in heredoc\n", STDERR_FILENO);
		info->is_error = 1;
		return (start + offset + 1);
	}
	str = ft_substr(s, start + 1, offset - 1);
	token_pushback(&token_list, token_createnew(str, TOKEN_TYPE_ARGV));
	return (start + offset + 1);
}

static int	handle_limiter(
	t_info *info, t_token *token_list, char *s, int start)
{
	int		offset;
	char	*str;

	while (s[start] && !is_tokenable_sep(s[start]))
	{
		if (s[start] == '\'' || s[start] == '\"')
			start = handle_quote_in_limiter(info, token_list, s, start);
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

static void	handle_heredoc_with_limiter(t_info *info, t_token *token_list)
{
	int		start;
	char	*token_str;
	char	*str;

	token_str = ft_strdup(token_list->str);
	start = 0;
	while (token_str[start] && ft_strncmp(token_str + start, "<<", 2))
		start++;
	if (token_str[start] == '\0')
		return (free(token_str));
	start += 2;
	free(token_list->str);
	token_list->str = ft_substr(token_str, 0, start);
	while (token_str[start] && token_str[start] == ' ')
		start++;
	start = handle_limiter(info, token_list, token_str, start);
	if (ft_strlen(token_str) - start == 0)
		return (free(token_str));
	str = ft_substr(token_str, start, ft_strlen(token_str) - start);
	token_pushback(&token_list, token_createnew(str, TOKEN_TYPE_CHUNK));
	free(token_str);
}

void	handle_heredoc(t_info *info, t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == TOKEN_TYPE_CHUNK)
			handle_heredoc_with_limiter(info, token_list);
		token_list = token_list->next;
	}
}
