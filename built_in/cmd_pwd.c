/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:28:46 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/21 16:43:55 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	cmd_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd (cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (1);
	}
	else
		return (0);
}
