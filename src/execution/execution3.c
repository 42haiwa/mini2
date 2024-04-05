/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:06 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/05 18:57:49 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_three_exec(t_core *core, t_exec *stru)
{
	ft_putchar_fd(' ', 2);
	perror("");
	free_str_tab(core->envp);
	free_str_tab(stru->new_argv);
	free_three(&core->execution_three);
	exit(1);
}

void	in_four_exec3(t_core *core, t_exec *stru)
{
	char	*tmp;
	char	*path;

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

void	in_four_exec2(t_core *core, t_exec *stru)
{
	char	*tmp;
	char	*path;

	if (core->execution_three->sons[stru->i]->heredoc_id == -1)
	{
		core->n_heredoc++;
		tmp = ft_itoa(core->n_heredoc);
		path = ft_strjoin("/tmp/heredoc", tmp);
		unlink(path);
		free(tmp);
		free(path);
		stru->i = 0;
		while (stru->i < 128)
		{
			ft_close(stru->pipe_fd[stru->i][0]);
			ft_close(stru->pipe_fd[stru->i][1]);
			stru->i++;
		}
		free_three(&core->execution_three);
		free_str_tab(stru->new_argv);
		free_str_tab(core->envp);
		exit(130);
	}
}

void	in_four_exec(t_core *core, t_exec *stru)
{
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
	in_four_exec2(core, stru);
	in_four_exec3(core, stru);
}
