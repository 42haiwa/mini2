/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:01:36 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/05 17:32:36 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_get_path(t_core *core, char *cmd)
{
	char	**env_path;
	char	*str;
	char	*path;
	int		i;

	if (check_builtins_no_exec(cmd))
		return (ft_strdup(cmd));
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	if (!get_envp("PATH", core)[0])
		return (NULL);
	env_path = ft_split(get_envp("PATH", core), ':');
	str = ft_strjoin("/", cmd);
	i = -1;
	while (env_path[++i])
	{
		path = ft_strjoin(env_path[i], str);
		if (access(path, F_OK | X_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free_str_tab(env_path);
	free(str);
	return (path);
}
