/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:46:45 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/15 14:29:14 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_list(t_gnl **list, char *buf, int read_return)
{
	int		i;
	t_gnl	*last;
	t_gnl	*new_block;

	new_block = malloc(sizeof(t_gnl));
	if (!new_block)
		return ;
	new_block->next = NULL;
	new_block->data = malloc(read_return + 1);
	if (!(new_block->data))
		return ;
	i = 0;
	while (buf[i] && i < read_return)
	{
		new_block->data[i] = buf[i];
		i++;
	}
	new_block->data[read_return] = '\0';
	if (!(*list))
	{
		*list = new_block;
		return ;
	}
	last = get_last_block(*list);
	last->next = new_block;
}

void	read_and_stack(t_gnl **list, int *read_return, int fd)
{
	char	*buf;

	while (!is_line(*list) && *read_return != 0)
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		*read_return = read(fd, buf, BUFFER_SIZE);
		if (*read_return == -1)
		{
			free(buf);
			return ;
		}
		buf[*read_return] = '\0';
		add_to_list(list, buf, *read_return);
		free(buf);
	}
}

void	_get_line(t_gnl *list, char **line)
{
	size_t	i;
	size_t	j;

	if (!list)
		return ;
	alloc_line(list, line);
	if (!line)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->data[i])
		{
			if (list->data[i] == '\n')
			{
				(*line)[j++] = list->data[i];
				break ;
			}
			(*line)[j++] = list->data[i++];
		}
		list = list->next;
	}
	(*line)[j] = '\0';
}

void	clear_list(t_gnl **list)
{
	t_gnl	*last;
	t_gnl	*cl_node;
	int		i;
	int		j;

	cl_node = malloc(sizeof(t_gnl));
	if (list == NULL || cl_node == NULL)
		return ;
	cl_node->next = NULL;
	last = get_last_block(*list);
	i = 0;
	while (last->data[i] && last->data[i] != '\n')
		i++;
	if (last->data && last->data[i] == '\n')
		i++;
	cl_node->data = malloc(sizeof(char) * ((ft_strlen(last->data) - i) + 1));
	if (cl_node->data == NULL)
		return ;
	j = 0;
	while (last->data[i])
		cl_node->data[j++] = last->data[i++];
	cl_node->data[j] = '\0';
	dealloc_list(*list);
	*list = cl_node;
}

char	*get_next_line(int fd)
{
	static t_gnl		*list;
	char				*line;
	int					read_return;
	struct sigaction	act;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = handler3;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	init_var_gnl(&read_return, &line);
	read_and_stack(&list, &read_return, fd);
	if (list == NULL)
		return (NULL);
	_get_line(list, &line);
	clear_list(&list);
	if (line[0] == '\0' || read_return == -1)
	{
		dealloc_list(list);
		list = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
