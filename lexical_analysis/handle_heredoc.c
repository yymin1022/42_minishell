/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 07:19:18 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/07 10:46:47 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

static int	handle_quote(t_info *info, t_token *token_list, char *s, int idx)
{
	int		offset;
	char	*str;

	offset = 1;
	while (s[idx + offset] && s[idx + offset] != s[idx])
		offset++;
	if (s[idx + offset] == '\0')
	{
		ft_putstr_fd("pm_shell: quotes error in heredoc\n", STDERR_FILENO);
		info->is_error = 1;
		return (idx + offset + 1);
	}
	str = ft_substr(s, idx + 1, offset - 1);
	token_pushback(&token_list, token_createnew(str, TOKEN_TYPE_ARGV));
	return (idx + offset + 1);
}

static int	handle_limiter(t_info *info, t_token *token_list, char *s, int idx)
{
	int		offset;
	char	*str;

	while (s[idx] && !is_tokenable_sep(s[idx]))
	{
		if (s[idx] == '\'' || s[idx] == '\"')
			idx = handle_quote(info, token_list, s, idx);
		else
		{
			offset = 1;
			while (s[idx + offset] && !is_tokenable_sep(s[idx + offset])
				&& s[idx + offset] != '\''
				&& s[idx + offset] != '\"')
					offset++;
			str = ft_substr(s, idx, offset);
			token_pushback(&token_list, token_createnew(str, TOKEN_TYPE_ARGV));
			idx += offset;
		}
	}
	return (idx);
}

static void	handle_heredoc_with_limiter(t_info *info, t_token *token_list)
{
	int		start_idx;
	char	*token_str;
	char	*str;

	token_str = ft_strdup(token_list->str);
	start_idx = 0;
	while (token_str[start_idx] && ft_strncmp(token_str + start_idx, "<<", 2))
		start_idx++;
	if (token_str[start_idx] == '\0')
		return (free(token_str));
	start_idx += 2;
	free(token_list->str);
	token_list->str = ft_substr(token_str, 0, start_idx);
	while (token_str[start_idx] && token_str[start_idx] == ' ')
		start_idx++;
	start_idx = handle_limiter(info, token_list, token_str, start_idx);
	if (ft_strlen(token_str) - start_idx == 0)
		return (free(token_str));
	str = ft_substr(token_str, start_idx, ft_strlen(token_str) - start_idx);
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
