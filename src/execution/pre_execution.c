/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:32:05 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/03 14:35:26 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pre_execution2(t_core *core, size_t i, size_t k)
{
	if (((size_t) i + k + 2 < (size_t) core->THREE->sons_ctr) \
		&& ft_strcmp(core->THREE->sons[i + k + 2]->content, \
		"\6PIPE\6") == 0)
	{
		core->execution_three->sons[i]->outpipe = 1;
		return (1);
	}
	return (0);
}

void	pre_execution(t_core *core)
{
	size_t	i;
	size_t	k;

	i = -1;
	while (++i < (size_t) core->execution_three->sons_ctr)
	{
		if (i < (size_t) core->execution_three->sons_ctr - 1)
		{
			if (*((char *) core->execution_three->sons[i]->content) == '\0')
				continue ;
			k = 1;
			if (ft_strcmp(core->THREE->sons[i + 1]->content, "\6PIPE\6") == 0)
				core->execution_three->sons[i]->outpipe = 1;
			while (((size_t) i + k + 2 < (size_t) core->THREE->sons_ctr) \
				&& *((char *)core->THREE->sons[i + k]->content) == '\0')
			{
				if (pre_execution2(core, i, k))
					break ;
				k++;
			}
		}
	}
}
