/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:42:18 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/15 13:57:37 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_err_ctrl(t_core *core)
{
	if (g_sig == 1)
		core->err_code = 130;
	g_sig = 0;
}

char	*replace(char *s, char *old, char *new)
{
	char	*find;
	int		old_len;
	int		new_len;
	int		new_size;
	char	*result;

	find = ft_strstr(s, old);
	if (find != NULL)
	{
		old_len = ft_strlen(old);
		new_len = ft_strlen(new);
		new_size = ft_strlen(s) - old_len + new_len;
		result = (char *)ft_calloc(new_size + 1, 1);
		ft_strncpy(result, s, find - s);
		result[find - s] = '\0';
		ft_strcat(result, new);
		ft_strcat(result, find + old_len);
		free(s);
		return (result);
	}
	return (s);
}

char	*replace_with_index(char *s, char *old, char *new, int index)
{
	char	*find;
	int		old_len;
	int		new_len;
	int		new_size;
	char	*result;

	find = ft_strstr(s + index, old);
	if (find != NULL)
	{
		old_len = ft_strlen(old);
		new_len = ft_strlen(new);
		new_size = ft_strlen(s) - old_len + new_len;
		result = (char *)ft_calloc(new_size + 1, 1);
		ft_strncpy(result, s, find - s);
		result[find - s] = '\0';
		ft_strcat(result, new);
		ft_strcat(result, find + old_len);
		free(s);
		return (result);
	}
	return (s);
}
