/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:39:40 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/12 19:39:42 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char **argv, int argc, t_core *core)
{
	int	i;

	i = 1;
	core->err_code = 0;
	if (argc <= 1)
		return ;
	while (i < argc)
	{
		if (!check_getter(argv[i]))
		{
			core->err_code = 1;
			ft_putendl_fd("not a valid identifier", 2);
			return ;
		}
		remove_envp(argv[i], core);
		i++;
	}
}
