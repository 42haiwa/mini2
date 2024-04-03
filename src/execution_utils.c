/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 00:39:11 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/03 12:51:15 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins_no_exec(char *buf)
{
	if (ft_strcmp("env", buf) == 0 || ft_strcmp("pwd", buf) == 0
		|| ft_strcmp("cd", buf) == 0 || ft_strcmp("echo", buf) == 0)
		return (1);
	return (0);
}

int	is_token(char const *s)
{
	if (ft_strncmp(s, "\6PIPE\6", 4) == 0)
		return (1);
	if (ft_strncmp(s, "SEMICOLON", 9) == 0)
		return (1);
	if (ft_strncmp(s, "GREATGREAT", 10) == 0)
		return (1);
	if (ft_strncmp(s, "LESSLESS", 8) == 0)
		return (1);
	if (ft_strncmp(s, "GREAT", 5) == 0 && ft_strlen(s) <= 5)
		return (1);
	if (ft_strncmp(s, "LESS", 4) == 0 && ft_strlen(s) <= 4)
		return (1);
	return (0);
}
