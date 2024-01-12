/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:35:37 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/12 20:37:48 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

int	syntax_analysis(t_token *token_list)
{
	if (check_pipe_syntax() && check_redirection_syntax())
		return (1);
	return (0);
}
