/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bill_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:18:51 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/12 12:58:19 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_var_three(t_core *core, t_parsing *pa)
{
	pa->i = -1;
	pa->splited = split_buf(core->lexer_out);
	core->cmd_p = 0;
	core->n_heredoc = 0;
	pa->last_pipe = 0;
	pa->last_cmd = 0;
	pa->father = NULL;
}

static int	first_bill(t_core *core, t_parsing *pa)
{
	if (ft_strcmp(pa->splited[pa->i], "\6PIPE\6") == 0)
	{
		pa->father = NULL;
		node_add_son(core->execution_three, node_init(ft_strdup("\6PIPE\6")));
		core->cmd_p = 0;
		pa->last_pipe = pa->i;
		return (1);
	}
	return (0);
}

static void	inside_three(t_core *core, t_parsing *pa)
{
	if (!check_redirect(pa->splited, pa->i) && !is_token(pa->splited[pa->i]))
	{
		pa->current = node_init(ft_strdup(pa->splited[pa->i]));
		if (!core->cmd_p)
		{
			pa->last_cmd = pa->i;
			parse_io_n(core, pa->last_pipe, pa->current, pa->splited);
		}
		if (pa->father)
			node_add_son(pa->father, pa->current);
		else
		{
			node_add_son(core->execution_three, pa->current);
			pa->father = pa->current;
		}
		core->cmd_p = 1;
	}
}

void	bill_three(t_core *core)
{
	t_parsing	pa;

	if (core->lexer_out == NULL)
		return ;
	init_var_three(core, &pa);
	while (pa.splited[++pa.i])
	{
		if (first_bill(core, &pa))
			continue ;
		if (pa.i == 0 && ft_strcmp(pa.splited[0], "\6LESSLESS\6") == 0 \
		&& pa.splited[pa.i + 1] && !pa.splited[pa.i + 2])
		{
			heredoc(999, pa.splited[pa.i + 1], core);
			unlink("/tmp/heredoc999");
		}
		inside_three(core, &pa);
	}
	free_str_tab(pa.splited);
	core->n_heredoc = 0;
	free(core->lexer_out);
	core->lexer_out = NULL;
}
