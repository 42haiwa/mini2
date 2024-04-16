/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:06 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/15 22:15:51 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_exec(t_core *core, t_exec *stru)
{
	stru->j = 1;
	if (ft_strcmp(core->execution_three->sons[stru->i]->content, "") == '\0')
		return (1);
	stru->new_argv = ft_calloc(core->execution_three->sons[stru->i]->sons_ctr
			+ 2, sizeof(char *));
	while (stru->j <= core->execution_three->sons[stru->i]->sons_ctr)
	{
		stru->new_argv[stru->j] = ft_strdup(
				core->execution_three->sons[stru->i]->sons[stru->j - 1]
				->content);
		stru->j++;
	}
	stru->new_argv[0] = ft_strdup(core->execution_three
			->sons[stru->i]->content);
	if (is_token(core->execution_three->sons[stru->i]->content))
	{
		if (ft_strncmp(core->execution_three->sons[stru->i]->content,
				"\6PIPE\6", 4) == 0)
		{
			stru->pipe_ctr++;
		}
		free_str_tab(stru->new_argv);
		return (1);
	}
	return (0);
}

int	second_exec(t_core *c, t_exec *s)
{
	if (c->THREE->C <= 1 && !(c->THREE->S[s->i]->OU) &&!(c->THREE->S[s->i]->IN))
	{
		if (check_builtins_no_fork(c->execution_three->sons[s->i]->content,
				s->new_argv, c->execution_three->sons[s->i]->sons_ctr + 1,
				c))
			return (1);
	}
	s->check = ft_get_path(c, c->execution_three->sons[s->i]->content);
	if (!check_builtins_no_exec(c->execution_three->sons[s->i]->content)
		&& s->check)
	{
		s->test = c->execution_three->sons[s->i]->content;
		c->execution_three->sons[s->i]->content = ft_get_path(c, s->test);
		free(s->test);
	}
	if (s->check == NULL)
	{
		ft_putstr_fd(c->execution_three->sons[s->i]->content, 2);
		ft_putendl_fd(": command not found", 2);
		c->err_code = 127;
		free_str_tab(s->new_argv);
		return (1);
	}
	free(s->check);
	return (0);
}

void	three_exec(t_core *core, t_exec *stru)
{
	if ((core->execution_three->sons[stru->i]->output) != 0)
	{
		if (core->execution_three->sons[stru->i]->output_mode == 1)
			stru->o_fd = open(core->execution_three->sons[stru->i]->output,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (core->execution_three->sons[stru->i]->output_mode == 2)
			stru->o_fd = open(core->execution_three->sons[stru->i]->output,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (stru->o_fd == -1)
			in_three_exec(core, stru);
		dup2(stru->o_fd, STDOUT_FILENO);
		ft_close(stru->o_fd);
		return ;
	}
	if ((stru->i + 1) < (size_t) core->execution_three->sons_ctr
		&& core->execution_three->sons[stru->i]->outpipe)
	{
		ft_close(stru->pipe_fd[stru->pipe_ctr][0]);
		dup2(stru->pipe_fd[stru->pipe_ctr][1], STDOUT_FILENO);
		ft_close(stru->pipe_fd[stru->pipe_ctr][1]);
		stru->pipe_fd[stru->pipe_ctr][1] = -1;
	}
}

void	four_exec(t_core *core, t_exec *stu)
{
	size_t	k;

	k = 0;
	while (stu->i - k > 1)
	{
		if (*((char *)core->execution_three->sons[stu->i - k - 2]->content) \
			== '\0')
			k++;
		else
			break ;
	}
	if (stu->i - k > 1 && core->execution_three->sons[stu->i - k - 2]->outpipe)
	{
		ft_close(stu->pipe_fd[stu->pipe_ctr - 1][1]);
		dup2(stu->pipe_fd[stu->pipe_ctr - 1][0], STDIN_FILENO);
		ft_close(stu->pipe_fd[stu->pipe_ctr - 1][0]);
		stu->pipe_fd[stu->pipe_ctr - 1][0] = -1;
	}
	in_four_exec(core, stu);
}

void	execution(t_core *core)
{
	t_exec	stru;

	init_exec(&stru, core);
	while (++stru.i < (size_t) core->execution_three->sons_ctr)
	{
		if (first_exec(core, &stru) == 1)
			continue ;
		if (second_exec(core, &stru) == 1)
			continue ;
		stru.c_pid = fork();
		if (stru.c_pid == -1)
			exit(1);
		core->son_pid = stru.c_pid;
		if (stru.c_pid == 0)
		{
			rl_clear_history();
			three_exec(core, &stru);
			four_exec(core, &stru);
			five_exec(core, &stru);
		}
		else
			six_exec(core, &stru);
		free_str_tab(stru.new_argv);
	}
	end_exec(core, &stru);
}
