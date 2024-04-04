/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:06 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/04 13:34:53 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_four_exec(t_core *core, t_exec *stru)
{
	char	*path;
	char	*tmp;

	if ((core->execution_three->sons[stru->i]->input) != 0)
	{
		stru->i_fd = open(core->execution_three->sons[stru->i]->input,
				O_RDONLY);
		if (stru->i_fd == -1)
		{
			ft_putchar_fd(' ', 2);
			perror("");
			free_three(&core->execution_three);
			free_str_tab(stru->new_argv);
			free_str_tab(core->envp);
			exit(1);
		}
		dup2(stru->i_fd, STDIN_FILENO);
		ft_close(stru->i_fd);
	}
	if (core->execution_three->sons[stru->i]->heredoc_id == -1)
	{
		core->n_heredoc++;
		tmp = ft_itoa(core->n_heredoc);
		path = ft_strjoin("/tmp/heredoc", tmp);
		unlink(path);
		free(tmp);
		free(path);
		exit(130);
	}
	if (core->execution_three->sons[stru->i]->heredoc_id)
	{
		core->n_heredoc++;
		tmp = ft_itoa(core->n_heredoc);
		path = ft_strjoin("/tmp/heredoc", tmp);
		free(tmp);
		stru->i_fd = open(path, O_RDONLY);
		dup2(stru->i_fd, STDIN_FILENO);
		ft_close(stru->i_fd);
		unlink(path);
		free(path);
	}
}
