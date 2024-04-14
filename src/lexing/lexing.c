/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:02:20 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/14 20:59:58 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexing3(char **splited, t_core *core)
{
	core->first = get_first(splited[core->lex_i], "\'\"", core->lex_x);
	core->substr = get_substring(splited[core->lex_i], \
	core->first, core->lex_x);
	core->lex_join = safe_join(core->lex_join, core->substr, 1, 1);
	core->lex_x += len_by_char(splited[core->lex_i], core->first, core->lex_x);
}

void	join_d_quote(t_core *c)
{
	c->lex_join = safe_join(c->lex_join, c->get_d_quote[c->lex_count2] \
	, 1, 0);
	if (c->get_d_quote[c->lex_count2])
		c->lex_x += ft_strlen(c->get_d_quote[c->lex_count2]) + 1;
	else
		c->lex_x += 2;
}

void	lexing2(char **splited, t_core *c)
{
	while (1)
	{
		lexing3(splited, c);
		if (c->first == 0)
			break ;
		if (c->first == '\'')
		{
			c->lex_join = safe_join(c->lex_join, \
			c->get_quote[c->lex_count], 1, 0);
			if (c->get_quote[c->lex_count])
				c->lex_x += ft_strlen(c->get_quote[c->lex_count]) + 1;
			else
				c->lex_x += 2;
			c->lex_count++;
		}
		if (c->first == '\"')
		{
			join_d_quote(c);
			c->lex_count2++;
		}
	}
}

void	lexing(char **splited, t_core *core)
{
	core->lex_i = -1;
	while (splited[++core->lex_i])
	{
		core->lex_n_quote = get_n_char(splited[core->lex_i], '\'');
		core->lex_n_d_quote = get_n_char(splited[core->lex_i], '\"');
		if (core->lex_n_d_quote == 0 && core->lex_n_quote == 0 && \
		!core->lex_bool[QUOTE] && !core->lex_bool[D_QUOTE])
		{
			if (get_delimiter(splited[core->lex_i]))
				add_block(get_delimiter(splited[core->lex_i]), core, 1);
			else
				add_block(splited[core->lex_i], core, 0);
		}
		else
		{
			core->lex_x = 0;
			lexing2(splited, core);
			add_block(core->lex_join, core, 0);
			free(core->lex_join);
			core->lex_join = NULL;
		}
	}
}
