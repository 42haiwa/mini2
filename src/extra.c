/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:25:39 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/10 13:38:01 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_extra2(char *buf, size_t i)
{
	size_t	count;
	int		boolean[2];

	boolean[0] = 0;
	boolean[1] = 0;
	count = 0;
	while (buf[++i])
	{
		if (buf[i] == '"' && !boolean[0])
			boolean[1] = !boolean[1];
		if (buf[i] == '\'' && !boolean[1])
			boolean[0] = !boolean[0];
		if (buf[i] == ' ' || boolean[1] || boolean[0])
			continue ;
		if (buf[i] == '<' || buf[i] == '>' || buf[i] == '|' || buf[i] == ';')
		{
			count++;
			if (count >= 3)
				return (1);
		}
		else
			count = 0;
	}
	return (0);
}

static int	check_buf(char *buf, size_t i)
{
	while (buf[++i])
	{
		if (buf[i] == '|' || buf[i] == ';')
			return (1);
		else if (buf[i] == ' ')
			continue ;
		else
		{
			return (0);
		}
	}
	return (0);
}

char	*check_extra(char *buf)
{
	size_t	i;

	if (ft_strcmp(buf, "") == 0)
		return (NULL);
	if (ft_isonly(buf, " "))
		return (NULL);
	if (ft_isonly(buf, "<>|; "))
		return ("minishell: syntax error near unexpected token");
	if (ft_strlen(buf) > 1 && (buf[0] == '|'
			|| buf[0] == ';'))
		return ("minishell: syntax error near unexpected token");
	if (buf[ft_strlen(buf) - 1] == '|')
		return ("minishell: Pipe Error");
	if (buf[ft_strlen(buf) - 1] == '<' || buf[ft_strlen(buf) - 1] == '>')
		return ("minishell: syntax error near unexpected token");
	i = -1;
	if (buf[ft_strlen(buf) - 1] == ';' || check_extra2(buf, i))
		return ("minishell: syntax error near unexpected token");
	while (buf[++i])
	{
		if (buf[i] == '<' && check_buf(buf, i))
			return ("minishell: syntax error near unexpected token");
	}
	return (NULL);
}
