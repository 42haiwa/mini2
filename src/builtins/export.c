/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:54:52 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/04 13:53:55 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pre_export(int argc, t_core *core)
{
	if (argc <= 1)
	{
		env(core);
		return (1);
	}
	return (0);
}

static int	export_getter(t_export *n, t_core *core, char **argv)
{
	n->getter = get_getter(argv[n->i]);
	if (!check_getter(n->getter))
	{
		core->err_code = 1;
		ft_putendl_fd("export: not a valid identifier", 2);
		return (1);
	}
	return (0);
}

void	export_values(char **argv, t_export *n, t_core *core)
{
	n->values = get_value(argv[n->i]);
	if (ft_strlen(get_envp(n->getter, core)) == 0)
	{
		n->tmp = ft_strjoin(n->getter, "=");
		add_envp(n->tmp, n->values, core);
	}
	else
		set_envp(n->getter, n->values, core);
}

void	export(char **argv, int argc, t_core *core)
{
	t_export	n;

	if (pre_export(argc, core))
		return ;
	n.i = 0;
	n.tmp = NULL;
	while (++n.i < argc)
	{
		if (ft_strchr(argv[n.i], '=') == NULL && !check_getter(argv[n.i]))
		{
			core->err_code = 1;
			ft_putendl_fd("export: not a valid identifier", 2);
			continue ;
		}
		if (ft_strchr(argv[n.i], '=') == NULL)
			continue ;
		if (export_getter(&n, core, argv))
		{
			free(n.getter);
			return ;
		}
		export_values(argv, &n, core);
		free_export(n.getter, n.values, n.tmp);
	}
}
