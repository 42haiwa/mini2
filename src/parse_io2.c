/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:41:19 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/05 18:20:37 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inside_part_four(t_parse *stru, t_core *core, char *path)
{
	if (((char *)core->execution_three->sons[stru->i]->content)[0] == '\0')
	{
		if ((ssize_t) stru->i + 2 < core->execution_three->sons_ctr)
		{
			core->execution_three->sons[stru->i + 2]->input = path;
			return ;
		}
		else if ((ssize_t) stru->i + 2 >= core->execution_three->sons_ctr)
			return ;
	}
	core->execution_three->sons[stru->i]->input = path;
}
