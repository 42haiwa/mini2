/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 23:52:25 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/12 12:57:28 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	init(size_t lpipe)
{
	ssize_t	i;

	i = lpipe + 1;
	if (!lpipe)
		i = 0;
	return (i);
}

static void	parse_while(t_core *co, size_t lpipe, t_node *curr, char **splited)
{
	ssize_t	i;

	i = init(lpipe);
	while (splited[i] && ft_strcmp(splited[i], "\6PIPE\6"))
	{
		if (ft_strcmp(splited[i], "\6LESSLESS\6") == 0)
		{
			co->n_heredoc++;
			curr->heredoc_id = co->n_heredoc;
			if (heredoc(curr->heredoc_id, splited[i + 1], co) == -1)
				curr->heredoc_id = -1;
			if (splited[i + 1])
				i++;
			else
				break ;
		}
		else if (ft_strcmp(splited[i], "\6LESS\6") == 0)
		{
			if (curr->input)
				free(curr->input);
			curr->input = ft_strdup(splited[i + 1]);
		}
		i++;
	}
}

static int	inside_parse(char ***splited, t_node **curr, ssize_t *i)
{
	int		fd;

	if (ft_strcmp((*splited)[(*i)], "\6GREATGREAT\6") == 0)
	{
		if ((*curr)->output)
			free((*curr)->output);
		(*curr)->output = ft_strdup((*splited)[(*i) + 1]);
		(*curr)->output_mode = 2;
		fd = open((*curr)->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (1);
		close(fd);
	}
	else if (ft_strcmp((*splited)[(*i)], "\6GREAT\6") == 0)
	{
		if ((*curr)->output)
			free((*curr)->output);
		(*curr)->output = ft_strdup((*splited)[(*i) + 1]);
		(*curr)->output_mode = 1;
		fd = open((*curr)->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (1);
		close(fd);
	}
	return (0);
}

void	parse_io_n(t_core *core, size_t lpipe, t_node *curr, char **splited)
{
	ssize_t	i;

	i = lpipe + 1;
	if (!lpipe)
		i = 0;
	while (splited[i] && ft_strcmp(splited[i], "\6PIPE\6") != 0)
	{
		if (inside_parse(&splited, &curr, &i))
			break ;
		i++;
	}
	parse_while(core, lpipe, curr, splited);
}
