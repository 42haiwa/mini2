/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:03:06 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/03 14:35:19 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_four_exec(t_core *core, t_exec *stru)
{
	char	*path;

	if ((core->execution_three->sons[stru->i]->input) != 0)
	{
		stru->i_fd = open(core->execution_three->sons[stru->i]->input,
				O_RDONLY);
		if (stru->i_fd == -1)
		{
			ft_putchar_fd(' ', 2);
			perror("");
			exit(1);
		}
		dup2(stru->i_fd, STDIN_FILENO);
		ft_close(stru->i_fd);
	}
	if (core->execution_three->sons[stru->i]->heredoc_id)
	{
		core->n_heredoc++;
		path = ft_strjoin("/tmp/heredoc", ft_itoa(core->n_heredoc));
		stru->i_fd = open(path, O_RDONLY);
		dup2(stru->i_fd, STDIN_FILENO);
		ft_close(stru->i_fd);
		unlink(path);
		free(path);
	}
}
