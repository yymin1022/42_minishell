/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/02 17:42:56 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;

	input = readline("pat_mat_shell> :$ ");
	printf("Wa Sans %s %d\n", input, argc);
	argv = NULL;
	env = NULL;
	free(input);
	return (0);
}
