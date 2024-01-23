/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote_with_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:08:01 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/23 22:47:02 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexical_analysis.h"

extern int	g_status_code;

char	*find_value_in_env(t_info *info, char *s)
{
	t_env	*cur;
	char	*equal_idx;
	char	*key;
	char	*value;

	cur = info->env_list;
	while (cur)
	{
		equal_idx = ft_strchr(cur->str, '=');
		key = ft_substr(cur->str, 0, equal_idx - cur->str);
		value = ft_strdup(equal_idx + 1);
		if (!ft_strncmp(key, s, ft_strlen(s)) && ft_strlen(key) == ft_strlen(s))
		{
			free(s);
			free(key);
			return (value);
		}
		four_times_free(key, value, NULL, NULL);
		cur = cur->next;
	}
	free(s);
	return (ft_strdup(""));
}

int	set_dollor_idx(char *s, int *dollor_idx, int *next_idx)
{
	if (ft_strlen(s) == 1 && !ft_strncmp(s, "$", 1))
		return (0);
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
		four_times_free(tmp, strs[0], strs[1], strs[2]);
	}
	return (s);
}
