/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:38:53 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/15 14:14:04 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler2(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) info;
	(void) ucontext;
}

void	handler3(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
