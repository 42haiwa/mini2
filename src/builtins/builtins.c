/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:38:41 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/15 21:38:13 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_builtins_no_fork(char *buf, char **argv)
{
	if (ft_strcmp("env", buf) == 0
		|| ft_strcmp("pwd", buf) == 0
		|| ft_strcmp("echo", buf) == 0
		|| ft_strcmp("export", buf) == 0
		|| ft_strcmp("unset", buf) == 0
		|| ft_strcmp("exit", buf) == 0
		|| ft_strcmp("cd", buf) == 0)
	{
		free_str_tab(argv);
		return (1);
	}
	return (0);
}

int	ft_free_builtins(char *buf, char **argv, t_core *core)
{
	if (ft_strcmp("env", buf) == 0
		|| ft_strcmp("pwd", buf) == 0
		|| ft_strcmp("echo", buf) == 0
		|| ft_strcmp("export", buf) == 0
		|| ft_strcmp("unset", buf) == 0
		|| ft_strcmp("exit", buf) == 0
		|| ft_strcmp("cd", buf) == 0)
	{
		free_str_tab(core->envp);
		free_str_tab(argv);
		free(buf);
		return (1);
	}
	return (0);
}

int	check_builtins(char *buf, char **argv, int argc, t_core *core)
{
	if (ft_strcmp("pwd", buf) == 0)
		pwd(core);
	if (ft_strcmp("env", buf) == 0)
		env(core);
	if (ft_strcmp("echo", buf) == 0)
		echo(argv, argc, core);
	if (ft_strcmp("export", buf) == 0)
		export(argv, argc, core);
	if (ft_strcmp("unset", buf) == 0)
		unset(argv, argc, core);
	if (ft_strcmp("exit", buf) == 0)
		ft_exit(argc, argv, core);
	if (ft_strcmp("cd", buf) == 0)
		cd(argv, argc, core);
	return (ft_free_builtins(buf, argv, core));
}

int	check_builtins_no_fork(char *buf, char **argv, int argc, t_core *core)
{
	if (ft_strcmp("pwd", buf) == 0)
		pwd(core);
	if (ft_strcmp("env", buf) == 0)
		env(core);
	if (ft_strcmp("echo", buf) == 0)
		echo(argv, argc, core);
	if (ft_strcmp("export", buf) == 0)
		export(argv, argc, core);
	if (ft_strcmp("unset", buf) == 0)
		unset(argv, argc, core);
	if (ft_strcmp("exit", buf) == 0)
		ft_exit(argc, argv, core);
	if (ft_strcmp("cd", buf) == 0)
		cd(argv, argc, core);
	return (ft_free_builtins_no_fork(buf, argv));
}
