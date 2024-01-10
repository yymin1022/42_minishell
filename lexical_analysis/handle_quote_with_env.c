/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote_with_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:08:01 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/10 23:16:01 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

extern int	g_status_code;

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
