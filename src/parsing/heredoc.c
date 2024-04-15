/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:57:26 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/15 14:15:33 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_heredoc(int *fd, char **path, char **sep, int id)
{
	char	*tmp;

	tmp = ft_itoa(id);
	*path = ft_strjoin("/tmp/heredoc", tmp);
	free(tmp);
	*fd = open(*path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	*sep = ft_strjoin(*sep, "\n");
	if (!*sep)
	{
		*sep = ft_calloc(2, 1);
		(*sep)[0] = '\n';
		(*sep)[1] = '\0';
	}
}

static void	free_heredoc(int fd, char *path, char *sep, char *line)
{
	g_sig = 0;
	close(fd);
	free(path);
	free(sep);
	free(line);
	get_next_line(INT_MAX);
}

static void	finish_by_ctrl(int fd, char *path, char *sep, char *line)
{
	if (g_sig != 1)
		ft_putendl_fd("here-document error", 2);
	free_heredoc(fd, path, sep, line);
}

int	heredoc(int id, char *sep, t_core *core)
{
	int		fd;
	char	*path;
	char	*line;

	init_heredoc(&fd, &path, &sep, id);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDOUT_FILENO);
		if (!line || g_sig == 1)
		{
			core->err_code = 130;
			finish_by_ctrl(fd, path, sep, line);
			return (-1);
		}
		if (sep == NULL && (line[0] == '\n' || line[0] == '\0'))
			break ;
		if (ft_strcmp(line, sep) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free_heredoc(fd, path, sep, line);
	return (0);
}
