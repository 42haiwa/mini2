/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:37:49 by cjouenne          #+#    #+#             */
/*   Updated: 2024/04/14 22:52:16 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_tab(char **str_tab)
{
	size_t	i;

	if (str_tab)
	{
		i = 0;
		while (str_tab[i])
			free(str_tab[i++]);
		free(str_tab);
	}
}

void	init(t_core *core, char **envp, char **buf, char **argv)
{
	struct sigaction	new_action;
	size_t				i;

	(void) argv;
	ft_memset(core, 0, sizeof(t_core));
	i = 0;
	while (envp[i])
		i++;
	core->envp = ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (envp[++i])
		core->envp[i] = ft_strdup(envp[i]);
	core->execution_three = 0;
	core->son_pid = -1;
	core->lexer_out = NULL;
	core->folder = "";
	core->err_code = 0;
	new_action.sa_handler = SIG_IGN;
	new_action.sa_flags = 0;
	sigemptyset(&new_action.sa_mask);
	sigaction(SIGQUIT, &new_action, NULL);
	*buf = NULL;
}

void	free_lexing(t_core *core)
{
	if (core->get_d_quote != NULL)
		free_str_tab(core->get_d_quote);
	if (core->get_quote != NULL)
		free_str_tab(core->get_quote);
}

int	start(char *buf, t_core *core)
{
	char	*error;

	add_history(buf);
	error = check_extra(buf);
	if (error)
	{
		core->err_code = 2;
		ft_putendl_fd(error, 2);
		return (0);
	}
	pre_lexing(buf, core);
	if (core->print_lex > 1)
		printf("%s\n", core->lexer_out);
	free_lexing(core);
	core->execution_three = node_init(NULL);
	bill_three(core);
	return (1);
}

	// if (core->print_lex > 1)
	// 	rprint(core->execution_three);
int		g_sig = 0;
int		g_in = -1;

int	main(int argc, char *argv[], char *envp[])
{
	char	*buf;
	t_core	core;

	core.print_lex = argc - argc;
	init(&core, envp, &buf, argv);
	while (1)
	{
		signal(SIGINT, handler);
		buf = readline("\e[35mminishell \e[33m ➤ \e[21m\e[0m ");
		set_err_ctrl(&core);
		signal(SIGINT, handler3);
		if (buf == NULL)
		{
			printf("exit\n");
			ft_exit(1, NULL, &core);
			break ;
		}
		if (start(buf, &core))
		{
			pre_execution(&core);
			execution(&core);
			free_three(&core.execution_three);
		}
	}
}
