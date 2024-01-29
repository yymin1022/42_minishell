/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:21:47 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/29 13:32:12 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_handle.h"

static void	sig_int_handle(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	init_sig_handler(void)
{
	signal(SIGINT, sig_int_handle);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		ft_putendl_fd("", STDERR_FILENO);
		exit(1);
	}
}
