/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:03:47 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/10 12:19:05 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	five_exec(t_core *core, t_exec *stru)
{
	char	*cmd;
	int		argc;

	cmd = ft_strdup(core->execution_three->sons[stru->i]->content);
	argc = core->execution_three->sons[stru->i]->sons_ctr + 1;
	free_three(&core->execution_three);
	stru->i = 0;
	while (stru->i < 128)
	{
		ft_close(stru->pipe_fd[stru->i][0]);
		ft_close(stru->pipe_fd[stru->i][1]);
		stru->i++;
	}
	if (check_builtins(cmd, stru->new_argv, argc, core))
		exit(0);
	execve(cmd, stru->new_argv, core->envp);
	free_str_tab(core->envp);
	free_str_tab(stru->new_argv);
	free(cmd);
	perror("minishell");
	exit(1);
}

void	six_exec(t_core *core, t_exec *stu)
{
	size_t	k;

	k = 0;
	if (core->execution_three->sons[stu->i]->heredoc_id == -1)
		core->n_heredoc++;
	else if (core->execution_three->sons[stu->i]->heredoc_id)
		core->n_heredoc++;
	while (stu->i - k > 1)
	{
		if (*((char *)core->execution_three->sons[stu->i - k - 2]->content)
			== '\0')
			k++;
		else
			break ;
	}
	stu->cmd++;
	if ((stu->i + 1) < (size_t) core->execution_three->sons_ctr
		&& core->execution_three->sons[stu->i]->outpipe)
	{
		ft_close(stu->pipe_fd[stu->pipe_ctr][1]);
		stu->pipe_fd[stu->pipe_ctr][1] = -1;
	}
	if (stu->i - k > 1 && core->execution_three->sons[stu->i - k - 2]->outpipe)
	{
		ft_close(stu->pipe_fd[stu->pipe_ctr - 1][0]);
		stu->pipe_fd[stu->pipe_ctr - 1][0] = -1;
	}
}

void	init_exec(t_exec *stru, t_core *core)
{
	stru->cmd = 0;
	stru->pipe_ctr = 0;
	stru->i = 0;
	while (stru->i < 128)
	{
		if (pipe(stru->pipe_fd[stru->i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		stru->i++;
	}
	stru->i = -1;
	core->stru = stru;
}

void	end_exec(t_core *core, t_exec *stru)
{
	int		status;

	stru->i = 0;
	while (stru->i < stru->cmd)
	{
		wait(&status);
		if (WIFEXITED(status))
			core->err_code = WEXITSTATUS(status);
		stru->i++;
	}
	stru->i = 0;
	while (stru->i < 128)
	{
		ft_close(stru->pipe_fd[stru->i][0]);
		ft_close(stru->pipe_fd[stru->i][1]);
		stru->i++;
	}
}
