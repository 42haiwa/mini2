/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:18:51 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/04 14:17:43 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_buf(char const *buf)
{
	char    *buf_sep;
	char    **splited;
	size_t  i;

	i = -1;
	buf_sep = ft_calloc(sizeof(char), ft_strlen(buf) + 1);
	while (buf[++i])
	{
		buf_sep[i] = buf[i];
		if (buf[i] == START || buf[i] == END)
			buf_sep[i] = START;
	}
	splited = ft_split(buf_sep, START);
	free(buf_sep);
	return (splited);
}

static int	check_redirect(char **split, size_t const i)
{
	if (i >= 1 && split[i - 1])
	{
		if (ft_strcmp(split[i - 1], "GREAT") == 0)
			return (1);
		if (ft_strcmp(split[i - 1], "GREATGREAT") == 0)
			return (1);
		if (ft_strcmp(split[i - 1], "LESS") == 0)
			return (1);
		if (ft_strcmp(split[i - 1], "LESSLESS") == 0)
			return (1);
	}
	return (0);
}

static int    heredoc(int id, char *sep)
{
    int        fd;
    char    *path;
    char    *line;
    char    *tmp;

    tmp = ft_itoa(id);
    path = ft_strjoin("/tmp/heredoc", tmp);
    free(tmp);
    fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    sep = ft_strjoin(sep, "\n");
    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (!line || g_sig == 1)
        {
            if (!line)
                ft_putendl_fd("here-document error", 2);
            g_sig = 0;
            close(fd);
            free(path);
            free(sep);
            free(line);
            return (-1);
        }
        if (sep == NULL && (line[0] == '\n' || line[0] == '\0'))
            break ;
        if (ft_strcmp(line, sep) == 0)
            break ;
        ft_putstr_fd(line, fd);
        free(line);
    }
    free(line);
    free(path);
    free(sep);
    close(fd);
    return (0);
}

static void	parse_io_n(t_core *core, size_t lpipe, t_node *current, char ** splited)
{
	ssize_t  i;
	int      fd;
	int			hd_status;

	hd_status = 0;
	i = lpipe + 1;
	if (!lpipe)
		i = 0;
	while (splited[i] && ft_strcmp(splited[i], "\6PIPE\6") != 0)
	{
		if (ft_strcmp(splited[i], "GREATGREAT") == 0)
		{
			current->output = ft_strdup(splited[i + 1]);
			current->output_mode = 2;
			fd = open(current->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				break ;
			close(fd);
		}
		else if (ft_strcmp(splited[i], "GREAT") == 0)
		{
			current->output = ft_strdup(splited[i + 1]);
			current->output_mode = 1;
			fd = open(current->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				break ;
			close(fd);
		}
		i++;
	}
	i = lpipe + 1;
	if (!lpipe)
		i = 0;
	while (splited[i] && ft_strcmp(splited[i], "\6PIPE\6"))
	{
		if (ft_strcmp(splited[i], "LESSLESS") == 0)
		{
			core->n_heredoc++;
			current->heredoc_id = core->n_heredoc;
			if (heredoc(current->heredoc_id, splited[i + 1]) == -1)
				current->heredoc_id = -1;
			if (splited[i + 1])
				i++;
			else
				break ;
		}
		else if (ft_strcmp(splited[i], "LESS") == 0)
		{
			if (current->input)
				free(current->input);
			current->input = ft_strdup(splited[i + 1]);
		}
		i++;
	}
}

void	bill_three(t_core *core)
{
	char    **splited;
	size_t  i;
	t_node  *father;
	t_node  *current;
	size_t  last_pipe;
	size_t  last_cmd;

	if (core->lexer_out == NULL)
		return ;
	i = -1;
	splited = split_buf(core->lexer_out);
	core->cmd_p = 0;
	core->n_heredoc = 0;
	last_pipe = 0;
	last_cmd = 0;
	father = NULL;
	while (splited[++i])
	{
		if (ft_strcmp(splited[i], "\6PIPE\6") == 0)
		{
			father = NULL;
			node_add_son(core->execution_three, node_init(ft_strdup("\6PIPE\6")));
			core->cmd_p = 0;
			last_pipe = i;
			continue ;
		}
		if (i == 0 && ft_strcmp(splited[0], "LESSLESS") == 0)
			if (splited[i + 1])
				heredoc(core->n_heredoc, splited[i + 1]);
		if (!check_redirect(splited, i) && !is_token(splited[i]))
		{
			current = node_init(ft_strdup(splited[i]));
			if (!core->cmd_p)
			{
				last_cmd = i;
				parse_io_n(core, last_pipe, current, splited);
			}
			if (father)
				node_add_son(father, current);
			else
			{
				node_add_son(core->execution_three, current);
				father = current;
			}
			core->cmd_p = 1;
		}
	}
	free_str_tab(splited);
	core->n_heredoc = 0;
	free(core->lexer_out);
	core->lexer_out = NULL;
}
