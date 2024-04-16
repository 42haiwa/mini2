/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:03:47 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/15 22:13:30 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_ft_free_exec5(t_core *core, t_exec *stru, char *cmd)
{
	free_str_tab(core->envp);
	free_str_tab(stru->new_argv);
	free(cmd);
	perror("minishell");
}

void	five_exec(t_core *core, t_exec *stru)
{
	char	*cmd;
	int		argc;
	int		n;

	cmd = ft_strdup(core->execution_three->sons[stru->i]->content);
	argc = core->execution_three->sons[stru->i]->sons_ctr + 1;
	n = stru->i;
	stru->i = 0;
	while (stru->i < 128)
	{
		ft_close(stru->pipe_fd[stru->i][0]);
		ft_close(stru->pipe_fd[stru->i][1]);
		stru->i++;
	}
	if (core->execution_three->sons_ctr > 1 || core->THREE->sons[n]->input
		|| core->THREE->sons[n]->output || core->THREE->sons[n]->heredoc_id)
	{
		free_three(&core->execution_three);
		if (check_builtins(cmd, stru->new_argv, argc, core))
			exit(0);
	}
	free_three(&core->execution_three);
	execve(cmd, stru->new_argv, core->envp);
	_ft_free_exec5(core, stru, cmd);
	exit(1);
}

void	six_exec(t_core *co, t_exec *s)
{
	s->k = 0;
	if (co->execution_three->sons[s->i]->heredoc_id == -1)
		co->n_heredoc++;
	else if (co->execution_three->sons[s->i]->heredoc_id)
		co->n_heredoc++;
	while (s->i - s->k > 1)
	{
		if (*((char *)co->execution_three->sons[s->i - s->k - 2]->content)
			== '\0')
			s->k++;
		else
			break ;
	}
	s->cmd++;
	if ((s->i + 1) < (size_t) co->execution_three->sons_ctr
		&& co->execution_three->sons[s->i]->outpipe)
	{
		ft_close(s->pipe_fd[s->pipe_ctr][1]);
		s->pipe_fd[s->pipe_ctr][1] = -1;
	}
	if (s->i - s->k > 1 && co->execution_three->sons[s->i - s->k - 2]->outpipe)
	{
		ft_close(s->pipe_fd[s->pipe_ctr - 1][0]);
		s->pipe_fd[s->pipe_ctr - 1][0] = -1;
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
	core->stru = NULL;
}
