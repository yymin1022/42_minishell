/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:58:39 by isang-yun         #+#    #+#             */
/*   Updated: 2024/01/23 22:29:06 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

size_t	ft_strcmp(char *src, char *dst)
{
	size_t	i;

	i = 0;
	while (src[i] && dst[i] && src[i] == dst[i])
		i++;
	return (src[i] - dst[i]);
}

void	p_list(t_env *list)
{
	while (list)
	{
		printf("%s\n", list->str);
		list = list->next;
	}
	printf("-----------------\n");
}

void	free_2d_str_array(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	four_times_free(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
}
