/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_lexing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:02:47 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/15 13:53:14 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_var4(char **buf, t_core *core)
{
	if ((*buf)[core->lex_i] == '<' && !core->lex_bool[2] && !core->lex_bool[1])
	{
		if ((*buf)[core->lex_i + 1] == '<')
		{
			if ((*buf)[core->lex_i + 2] != ' ')
				*buf = add_char(*buf, ' ', core->lex_i + 2);
			if (core->lex_i > 0 && (*buf)[core->lex_i - 1] != ' ')
			{
				*buf = add_char(*buf, ' ', core->lex_i);
				core->lex_i += 1;
			}
			core->lex_i++;
		}
		else
		{
			if ((*buf)[core->lex_i + 1] != ' ')
				*buf = add_char(*buf, ' ', core->lex_i + 1);
			if (core->lex_i > 0 && (*buf)[core->lex_i - 1] != ' ')
				*buf = add_char(*buf, ' ', core->lex_i);
		}
	}
	if ((*buf)[core->lex_i] == '\t' && !core->lex_bool[2] && !core->lex_bool[1])
		(*buf)[core->lex_i] = ' ';
}

static void	replace_var3(char **buf, t_core *core)
{
	if ((*buf)[core->lex_i] == '>' && !core->lex_bool[2] && !core->lex_bool[1])
	{
		if ((*buf)[core->lex_i + 1] == '>')
		{
			if ((*buf)[core->lex_i + 2] != ' ')
				*buf = add_char(*buf, ' ', core->lex_i + 2);
			if (core->lex_i > 0 && (*buf)[core->lex_i - 1] != ' ')
			{
				*buf = add_char(*buf, ' ', core->lex_i);
				core->lex_i++;
			}
			core->lex_i++;
		}
		else
		{
			if ((*buf)[core->lex_i + 1] != ' ')
				*buf = add_char(*buf, ' ', core->lex_i + 1);
			if (core->lex_i > 0 && (*buf)[core->lex_i - 1] != ' ')
				*buf = add_char(*buf, ' ', core->lex_i);
		}
	}
	replace_var4(buf, core);
}

static void	replace_var2(char **buf, t_core *core)
{
	if ((*buf)[core->lex_i] == '\'')
	{
		if (!core->lex_bool[D_QUOTE])
		{
			core->lex_bool[QUOTE] = !core->lex_bool[QUOTE];
			core->lex_bool[BOTH] = !core->lex_bool[BOTH];
		}
	}
	if ((*buf)[core->lex_i] == '\"')
	{
		if (!core->lex_bool[QUOTE])
			core->lex_bool[D_QUOTE] = !core->lex_bool[D_QUOTE];
	}
	if (((*buf)[core->lex_i] == '|') \
			&& !core->lex_bool[BOTH] && !core->lex_bool[D_QUOTE])
	{
		if ((*buf)[core->lex_i + 1] != ' ')
			*buf = add_char(*buf, ' ', core->lex_i + 1);
		if (core->lex_i > 0 && (*buf)[core->lex_i - 1] != ' ')
			*buf = add_char(*buf, ' ', core->lex_i);
	}
	replace_var3(buf, core);
	if ((*buf)[core->lex_i] == ' ' \
	&& (core->lex_bool[BOTH] || core->lex_bool[D_QUOTE]))
		(*buf)[core->lex_i] = '_';
}

static char	*replace_var(char *buf, t_core *core)
{
	char	*save;
	char	*tmp;

	init_var(core);
	while (buf[++core->lex_i])
	{
		replace_var2(&buf, core);
		if (!core->lex_bool[BOTH] \
			&& buf[core->lex_i] == '$' && buf[core->lex_i + 1] == '?')
		{
			tmp = ft_itoa(core->err_code);
			buf = replace(buf, "$?", tmp);
			free(tmp);
		}
		else if (buf[core->lex_i] == '$' && !core->lex_bool[BOTH])
		{
			save = get_string(buf, '$', core->lex_i);
			tmp = get_envp(ft_strchr(save, save[1]), core);
			buf = replace_with_index(buf, save, tmp, core->lex_i);
			core->lex_i += ft_strlen(tmp) - 1;
			free(save);
		}
	}
	return (buf);
}

void	pre_lexing(char *buf, t_core *core)
{
	char	**splited;

	core->get_d_quote = get_double_quote(buf);
	core->get_quote = get_quote(buf);
	replace_main(core);
	buf = replace_var(buf, core);
	core->lex_bool[QUOTE] = 0;
	core->lex_bool[D_QUOTE] = 0;
	core->lex_bool[BOTH] = 0;
	core->lex_join = NULL;
	core->lex_count = 0;
	core->lex_count2 = 0;
	splited = ft_split(buf, ' ');
	lexing(splited, core);
	free_str_tab(splited);
	free(buf);
}
