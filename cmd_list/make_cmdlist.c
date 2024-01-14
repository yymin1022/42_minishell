/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmdlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:13:59 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/14 17:39:31 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

t_cmd	*make_cmdlist(t_cmd *cmd_list, t_token *token_list)
{
	token_list = token_list->next;
	cmd_list = cmd_createnew();
	return (0);
}
