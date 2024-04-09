/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:46:55 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/05 14:48:39 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_line(t_list *list)
{
	t_list	*current;
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

t_list	*get_last_block(t_list *list)
{
	t_list	*current;

	current = list;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	alloc_line(t_list *list, char **line)
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

void	dealloc_list(t_list *list)
{
	t_list	*current;
	t_list	*next;

	current = list;
	while (current)
	{
		free(current->data);
		next = current->next;
		free(current);
		current = next;
	}
}

size_t	_ft_strlen(const char *s)
{
	size_t	len;

	len = -1;
	while (s[++len])
		;
	return (len);
}
