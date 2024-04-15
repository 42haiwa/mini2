/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 00:39:11 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/15 18:41:34 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins_no_exec(char *buf)
{
	if (ft_strcmp("env", buf) == 0 || ft_strcmp("pwd", buf) == 0
		|| ft_strcmp("cd", buf) == 0 || ft_strcmp("echo", buf) == 0
		|| ft_strcmp("exit", buf) == 0 || ft_strcmp("export", buf) == 0
		|| ft_strcmp("unset", buf) == 0)
		return (1);
	return (0);
}

int	is_token(char const *s)
{
	if (ft_strcmp(s, "\6PIPE\6") == 0)
		return (1);
	if (ft_strcmp(s, "\6GREATGREAT\6") == 0)
		return (1);
	if (ft_strcmp(s, "\6LESSLESS\6") == 0)
		return (1);
	if (ft_strcmp(s, "\6GREAT\6") == 0)
		return (1);
	if (ft_strcmp(s, "\6LESS\6") == 0)
		return (1);
	return (0);
}
