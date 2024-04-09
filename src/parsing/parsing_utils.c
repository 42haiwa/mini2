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

void rprint_with_indentation(t_node *node, int depth)
{
	if (node == NULL)
		return;
	for (int i = 0; i < depth; i++)
		printf("\t");
	printf("Contenu : %s\n", (char *) node->content);
	for (int i = 0; i < depth; i++)
		printf("\t");
	printf("Output  : %s\n", (char *) node->output);
	for (int i = 0; i < depth; i++)
		printf("\t");
	printf("Output mode  : %d\n", node->output_mode);
	for (int i = 0; i < depth; i++)
		printf("\t");
	printf("Input  : %s\n", (char *) node->input);
	if (node->sons != NULL)
	{
		for (ssize_t i = 0; i < node->sons_ctr; ++i)
		{
			rprint_with_indentation(node->sons[i], depth + 1);
		}
	}
}

void rprint(t_node *node)
{
	rprint_with_indentation(node, 0);
}
