/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:02:31 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/07 20:21:27 by isang-yun        ###   ########.fr       */
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

char	**handle_quote_in_chunk(t_info *info, char *s)
{
	int		start_idx;
	int		end_idx;
	char	**strs;

	strs = (char **)malloc(sizeof(char *) * 4);
	if (set_quote_index(info, s, &start_idx, &end_idx) || !strs)
		return (NULL);
	if (start_idx > 0 && s[start_idx - 1] == '$')
		strs[0] = ft_substr(s, 0, start_idx - 1);
	else
		strs[0] = ft_substr(s, 0, start_idx);
	return (strs);
}

void	handle_quote(t_info *info, t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == TOKEN_TYPE_CHUNK)
			handle_quote_in_chunk(info, token_list->str);
		token_list = token_list->next;
	}
}
