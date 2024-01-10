/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:02:31 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/10 10:44:33 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

extern int	g_status_code;

int	set_quote_index(t_info *info, char *s, int *start_idx, int *end_idx)
{
	*start_idx = 0;
	while (s[*start_idx] && s[*start_idx] != '\'' && s[*start_idx] != '\"')
		(*start_idx)++;
	if (s[*start_idx] == '\0')
		return (1);
	*end_idx = *start_idx + 1;
	while (s[*end_idx] && s[*start_idx] != s[*end_idx])
		(*end_idx)++;
	if (s[*end_idx] == '\0')
	{
		ft_putstr_fd("pm_shell: quotes error in argument\n", STDERR_FILENO);
		info->is_error = 1;
		return (1);
	}
	return (0);
}

char	*find_value_in_env(t_info *info, char *s)
{
	t_env	*cur;

	cur = info->env_list;
	while (cur)
	{
		if (!ft_strncmp(cur->key, s, ft_strlen(s))
			&& ft_strlen(cur->key) == ft_strlen(s))
		{
			free(s);
			return (ft_strdup(cur->value));
		}
		cur = cur->next;
	}
	free(s);
	return (ft_strdup(""));
}

int	set_dollor_idx(char *s, int *dollor_idx, int *next_idx)
{
	(*dollor_idx) = 0;
	while (s[*dollor_idx] && s[*dollor_idx] != '$')
		(*dollor_idx)++;
	if (s[*dollor_idx] == '\0')
		return (0);
	(*next_idx) = (*dollor_idx) + 1;
	if (s[*next_idx] == '?' || ft_isdigit(s[*next_idx])
		|| (!ft_isalpha(s[*next_idx]) && s[*next_idx] != '_'))
	{
		(*next_idx)++;
		return (1);
	}
	if (s[*next_idx] == '\0'
		|| (!ft_isalnum(s[*next_idx]) && s[*next_idx] != '_'))
		return (0);
	while (s[*next_idx]
		&& (ft_isalnum(s[*next_idx]) || s[*next_idx] == '_'))
		(*next_idx)++;
	return (1);
}

char	*handle_double_quote_with_env(t_info *info, char *s)
{
	char	*strs[3];
	int		dollor_idx;
	int		next_idx;
	char	*tmp;

	while (set_dollor_idx(s, &dollor_idx, &next_idx))
	{
		strs[0] = ft_substr(s, 0, dollor_idx);
		if (s[dollor_idx + 1] == '?')
		{
			next_idx = dollor_idx + 2;
			strs[1] = ft_itoa(g_status_code);
		}
		else
		{
			strs[1] = ft_substr(s, dollor_idx + 1, next_idx - dollor_idx - 1);
			strs[1] = find_value_in_env(info, strs[1]);
		}
		strs[2] = ft_substr(s, next_idx, ft_strlen(s) - next_idx);
		tmp = ft_strjoin(strs[0], strs[1]);
		free(s);
		s = ft_strjoin(tmp, strs[2]);
		free(tmp);
		free(strs[0]);
		free(strs[1]);
		free(strs[2]);
	}
	return (s);
}

char	**handle_quote_in_chunk(t_info *info, char *s)
{
	int		start_idx;
	int		end_idx;
	char	**strs;

	strs = (char **)malloc(sizeof(char *) * 4);
	if (!strs)
		return (NULL);
	if (set_quote_index(info, s, &start_idx, &end_idx))
	{
		free(strs);
		return (NULL);
	}
	if (start_idx > 0 && s[start_idx - 1] == '$')
		strs[0] = ft_substr(s, 0, start_idx - 1);
	else
		strs[0] = ft_substr(s, 0, start_idx);
	strs[1] = ft_substr(s, start_idx + 1, end_idx - start_idx - 1);
	if (s[start_idx] == '\"')
		strs[1] = handle_double_quote_with_env(info, strs[1]);
	strs[2] = ft_substr(s, end_idx + 1, ft_strlen(s) - end_idx - 1);
	strs[3] = NULL;
	return (strs);
}

void	handle_quote(t_info *info, t_token *token_list)
{
	char	**strs;
	t_token	*tmp;

	while (token_list)
	{
		if (token_list->type == TOKEN_TYPE_CHUNK)
		{
			strs = handle_quote_in_chunk(info, token_list->str);
			if (strs)
			{
				tmp = token_list->next;
				token_list->next = NULL;
				free(token_list->str);
				token_list->str = ft_strdup(strs[0]);
				token_pushback(&token_list,
					token_createnew(strs[1], TOKEN_TYPE_ARGV));
				token_list = token_pushback(&token_list,
						token_createnew(strs[2], TOKEN_TYPE_CHUNK));
				token_list->next = tmp;
				free_2d_str_array(strs);
			}
		}
		token_list = token_list->next;
	}
}
