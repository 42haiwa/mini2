/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:15:41 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/05 18:42:27 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	speciale(t_repl *stru, char **result)
{
	result[stru->val] = (char *)ft_calloc(3, sizeof(char));
	result[stru->val][0] = '$';
	result[stru->val][1] = '?';
	result[stru->val][2] = '\0';
	stru->val++;
	stru->i++;
}

/*
i = i
j = occurence / j
val = result Index
*/

void	extract_env2(t_repl	*stru, const char *s, char **result)
{
	stru->i++;
	stru->j = 0;
	while (!is_ending(s[stru->i]))
	{
		stru->i++;
		stru->j++;
	}
	result[stru->val] = (char *)ft_calloc((stru->j + 2), sizeof(char));
	stru->i -= stru->j;
	stru->j = 1;
	while (!is_ending(s[stru->i]))
	{
		result[stru->val][stru->j] = s[stru->i];
		stru->i++;
		stru->j++;
	}
	result[stru->val][0] = '$';
	result[stru->val][stru->j] = '\0';
	stru->val++;
}

char	**exctract_env(char *s)
{
	t_repl	stru;
	char	**result;

	stru.i = -1;
	stru.occurence = 0;
	while (s[++stru.i] != '\0')
		if (s[stru.i] == '$')
			stru.occurence++;
	if (stru.occurence == 0)
		return (NULL);
	result = (char **)ft_calloc((stru.occurence + 1), sizeof(char *));
	stru.i = 0;
	stru.val = 0;
	while (s[stru.i])
	{
		if (s[stru.i] == '$' && s[stru.i + 1] == '?')
			speciale(&stru, result);
		else if (s[stru.i] == '$' && s[stru.i + 1] \
		!= ' ' && s[stru.i + 1] != '\0')
			extract_env2(&stru, s, result);
		else
			stru.i++;
	}
	return (result);
}

void	replace_main2(t_core *core, char **extract, size_t j, size_t i)
{
	char	*tmp;

	if (ft_strcmp(extract[j], "$?") == 0)
	{
		tmp = ft_itoa(core->err_code);
		core->get_d_quote[i] = replace(core->get_d_quote[i],
				extract[j], tmp);
		free(tmp);
	}
	else
	{
		core->get_d_quote[i] = replace(core->get_d_quote[i],
				extract[j], get_envp(extract[j] + 1, core));
	}
}

void	replace_main(t_core *core)
{
	size_t	i;
	size_t	j;
	char	**extract;

	i = -1;
	extract = NULL;
	if (core->get_d_quote)
	{
		while (core->get_d_quote[++i])
		{
			extract = exctract_env(core->get_d_quote[i]);
			if (extract == NULL)
				continue ;
			j = -1;
			while (extract[++j])
			{
				replace_main2(core, extract, j, i);
			}
			free_str_tab(extract);
		}
	}
}
