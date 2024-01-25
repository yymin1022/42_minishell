/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:32:00 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/26 01:32:55 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

void	print_argument_err(char *str)
{
	char	*tmp;

	tmp = ft_strjoin("Invalid Argument : ", str);
	if (!tmp)
		return ;
	ft_putendl_fd(tmp, 2);
	free(tmp);
}
