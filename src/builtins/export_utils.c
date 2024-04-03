/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:54:52 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/03 11:53:15 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_getter(char const *s)
{
	size_t	len;
	char	*res;

	if (ft_strlen(s) == 1 && s[0] == '=')
		return (NULL);
	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != '=')
	{
		res[len] = s[len];
		len++;
	}
	res[len] = '\0';
	return (res);
}

char	*get_value(char const *s)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	i++;
	len = 0;
	while (s[len])
		len++;
	j = 0;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[j] = s[i];
		i++;
		j++;
	}
	return (res);
}

void	free_export(char *getter, char *values, char *tmp)
{
	free(getter);
	free(values);
	if (tmp != NULL)
		free(tmp);
}
