/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:02:34 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/23 22:30:19 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	print_env(char *str)
{
	printf("%s\n", str);
}

int	cmd_env(t_env *env_list)
{
	while (env_list)
	{
		print_env(env_list->str);
		env_list = env_list->next;
	}
	return (1);
}
