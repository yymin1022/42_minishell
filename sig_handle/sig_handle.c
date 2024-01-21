/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:21:47 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/21 15:51:44 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

static void	sig_int_handle(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

void	register_sig_handler()
{
	signal(SIGINT, sig_int_handle);
	signal(SIGQUIT, SIG_IGN);
}
