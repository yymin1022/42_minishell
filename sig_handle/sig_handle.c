/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:21:47 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/08 20:27:09 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "sig_handle.h"

static void	sig_handle(int sig)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	if (sig == SIGINT)
	{
		printf("Ctrl + C (SIGINT)\n");
	}
	else if (sig == SIGTERM)
	{
		printf("Ctrl + D (SIGTERM)\n");
	}
	else if (sig == SIGQUIT)
	{
		printf("Ctrl + \\ (SIGQUIT)\n");
	}
}

void	register_sig_handler()
{
	signal(SIGINT, sig_handle);
	signal(SIGTERM, sig_handle);
	signal(SIGQUIT, sig_handle);
}
