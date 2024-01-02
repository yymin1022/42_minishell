/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:04 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/02 17:45:33 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;

	while (1)
	{
		input = readline("pmshell> :$ ");
		printf("Wa Sans %s\n", input);
		add_history(input);
		free(input);
	}
	argc = 0;
	argv = NULL;
	env = NULL;
	return (0);
}
