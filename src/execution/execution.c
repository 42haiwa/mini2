/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:06 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/04 14:25:12 by cjouenne         ###   ########.fr       */
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

int	second_exec(t_core *core, t_exec *s)
{
	if (ft_strcmp(core->execution_three->sons[s->i]->content, "exit") == 0)
		if (core->execution_three->sons_ctr > 1)
			return (1);
	if (check_builtins_no_fork(core->execution_three->sons[s->i]->content,
			s->new_argv, core->execution_three->sons[s->i]->sons_ctr + 1,
			core))
		return (1);
	s->check = ft_get_path(core, core->execution_three->sons[s->i]->content);
	if (!check_builtins_no_exec(core->execution_three->sons[s->i]->content)
		&& s->check)
	{
		s->test = core->execution_three->sons[s->i]->content;
		core->execution_three->sons[s->i]->content = ft_get_path(core, s->test);
		free(s->test);
	}
	if (s->check == NULL)
	{
		ft_putstr_fd(core->execution_three->sons[s->i]->content, 2);
		ft_putendl_fd(": command not found", 2);
		core->err_code = 127;
		free_str_tab(s->new_argv);
		return (1);
	}
	free(s->check);
	return (0);
}

void	three_exec(t_core *core, t_exec *stru)
{
	if ((stru->i + 1) < (size_t) core->execution_three->sons_ctr
		&& core->execution_three->sons[stru->i]->outpipe)
	{
		ft_close(stru->pipe_fd[stru->pipe_ctr][0]);
		dup2(stru->pipe_fd[stru->pipe_ctr][1], STDOUT_FILENO);
		ft_close(stru->pipe_fd[stru->pipe_ctr][1]);
		stru->pipe_fd[stru->pipe_ctr][1] = -1;
	}
	if ((core->execution_three->sons[stru->i]->output) != 0)
	{
		if (core->execution_three->sons[stru->i]->output_mode == 1)
			stru->o_fd = open(core->execution_three->sons[stru->i]->output,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (core->execution_three->sons[stru->i]->output_mode == 2)
			stru->o_fd = open(core->execution_three->sons[stru->i]->output,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (stru->o_fd == -1)
		{
			ft_putchar_fd(' ', 2);
			perror("");
			free_str_tab(core->envp);
			free_str_tab(stru->new_argv);
			free_three(&core->execution_three);
			exit(1);
		}
		dup2(stru->o_fd, STDOUT_FILENO);
		ft_close(stru->o_fd);
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
		ft_close(stu->pipe_fd[stu->pipe_ctr][1]);
		dup2(stu->pipe_fd[stu->pipe_ctr - 1][0], STDIN_FILENO);
		ft_close(stu->pipe_fd[stu->pipe_ctr - 1][0]);
		stu->pipe_fd[stu->pipe_ctr - 1][0] = -1;
	}
	in_four_exec(core, stu);
}

void	execution(t_core *core)
{
	t_exec	stru;

	init_exec(&stru);
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
