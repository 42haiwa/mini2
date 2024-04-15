/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 07:16:54 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/15 12:57:23 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var(t_core *core)
{
	core->lex_i = -1;
	core->lex_bool[BOTH] = 0;
	core->lex_bool[QUOTE] = 0;
	core->lex_bool[D_QUOTE] = 0;
}

char	*get_delimiter(char *token)
{
	if (ft_strncmp(token, "|", 1) == 0)
		return ("\7\6PIPE\6\7");
	if (ft_strncmp(token, ";", 1) == 0)
		return ("\7SEMICOLON\7");
	if (ft_strncmp(token, ">>", 2) == 0)
		return ("\7\6GREATGREAT\6\7");
	if (ft_strncmp(token, ">", 1) == 0)
		return ("\7\6GREAT\6\7");
	if (ft_strncmp(token, "<<", 2) == 0)
		return ("\7\6LESSLESS\6\7");
	if (ft_strncmp(token, "<", 1) == 0)
		return ("\7\6LESS\6\7");
	return (NULL);
}

void	add_block2(t_core *core, char *result)
{
	char	*save;

	if (core->lexer_out == NULL)
	{
		core->lexer_out = result;
		return ;
	}
	save = core->lexer_out;
	core->lexer_out = ft_strjoin(save, result);
	free(save);
	free(result);
}

void	add_block(const char *s, t_core *core, int delimiter)
{
	size_t	i;
	char	*result;

	if (!s)
		return ;
	if (!delimiter)
	{
		result = ft_calloc(ft_strlen(s) + 3, sizeof(char));
		i = 1;
		result[0] = START;
		while (s[i - 1])
		{
			result[i] = s[i - 1];
			i++;
		}
		result[i] = END;
		result[i + 1] = '\0';
	}
	else
		result = ft_strdup(s);
	add_block2(core, result);
}
