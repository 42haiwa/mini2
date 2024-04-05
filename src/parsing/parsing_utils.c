/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:00:50 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/05 17:30:43 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_three(struct s_node **node)
{
	int	i;

	i = 0;
	if (*node == NULL)
		return ;
	while (i < (*node)->sons_ctr)
	{
		free_three(&(*node)->sons[i]);
		i++;
	}
	if ((*node)->sons)
		free((*node)->sons);
	if ((*node)->content)
		free((*node)->content);
	if ((*node)->output)
		free((*node)->output);
	if ((*node)->input)
		free((*node)->input);
	free(*node);
	*node = NULL;
}
