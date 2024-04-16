/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:53:30 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/15 22:06:02 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exec4(t_core *core, t_exec *stru)
{
	ft_putchar_fd(' ', 2);
	perror("minishell");
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
}
