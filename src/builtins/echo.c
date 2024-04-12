/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:32:39 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/12 16:10:44 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_error(int argc, t_core *core)
{
	if (argc <= 1)
	{
		write(1, "\n", 1);
		core->err_code = 0;
		return (1);
	}
	return (0);
}

void	echo(char **argv, int argc, t_core *core)
{
	int	i;
	int	is_n;

	i = 1;
	is_n = 0;
	if (check_error(argc, core))
		return ;
	if (argv[1][0] == '-' && argv[1][1] == 'n')
	{
		is_n = 1;
		i++;
	}
	while (i < argc)
	{
		if (i == (argc - 1))
			printf("%s", argv[i]);
		else
			printf("%s ", argv[i]);
		i++;
	}
	if (!is_n)
		printf("\n");
	core->err_code = 0;
}
