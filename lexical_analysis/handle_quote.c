/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:02:31 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/08 14:46:41 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

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

char	*handle_double_quote_with_env(t_info *info, char *s)
{
	int		dollor_idx;
	char	*dollor_front;
	char	*dollor_back;
	char	*res;

	dollor_idx = ft_strchr(s, '$') - s;
	dollor_front = ft_substr(s, 0, dollor_idx);
	dollor_back = find_value_in_env(info,
			ft_substr(s, dollor_idx + 1, ft_strlen(s) - dollor_idx));
	res = ft_strjoin(dollor_front, dollor_back);
	free(dollor_front);
	free(dollor_back);
	free(s);
	return (res);
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
		free_2d_str_array(strs);
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
