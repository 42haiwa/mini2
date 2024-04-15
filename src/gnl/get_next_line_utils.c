/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:46:55 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/15 14:24:18 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_line(t_gnl *list)
{
	t_gnl	*current;
	size_t	i;

	if (!list)
		return (0);
	current = get_last_block(list);
	i = 0;
	while (current->data[i])
	{
		if (current->data[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_gnl	*get_last_block(t_gnl *list)
{
	t_gnl	*current;

	current = list;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	alloc_line(t_gnl *list, char **line)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->data[i])
		{
			if (list->data[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		list = list->next;
	}
	*line = malloc(len + 1);
}

void	dealloc_list(t_gnl *list)
{
	t_gnl	*current;
	t_gnl	*next;

	current = list;
	while (current)
	{
		free(current->data);
		next = current->next;
		free(current);
		current = next;
	}
}

void	init_var_gnl(int *read_return, char **line)
{
	*read_return = 1;
	*line = NULL;
}
