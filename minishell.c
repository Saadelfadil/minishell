/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:30:15 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/06 11:50:07 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			com_initiate(void)
{
	g_minishell.com_head = ft_lstnew(new_command(0, 1, -1));
	g_minishell.com_tail = g_minishell.com_head;
	g_minishell.status = 1;
	g_minishell.fork_p = 0;
	g_minishell.read_next = NULL;
	g_minishell.pos = 0;
}

char			*read_line(void)
{
	char	buf;
	int		ret;

	g_minishell.input = ft_strdup("");
	while ((ret = read(0, &buf, 1)) != -1)
	{
		if (ret == 0)
		{
			if (ft_strncmp(g_minishell.input, "", 1) == 0)
			{
				if (!senko_equal_str(g_minishell.read_next, "|"))
					senko_exit(NULL);
				err_syntax("\x4");
				break ;
			}
			ft_putstr_fd("  \b\b", 1);
			continue;
		}
		else if (buf == '\n')
			break ;
		g_minishell.input = ft_strappend(g_minishell.input, buf);
	}
	return (g_minishell.input);
}

void			shell_exec(int n)
{
	if (g_minishell.status && g_minishell.read_next != NULL)
		err_syntax("\n");
	if (g_minishell.status && g_minishell.read_next == NULL)
		exec_commands();
	if (!senko_equal_str(g_minishell.read_next, "|"))
		ft_lstclear(&g_minishell.com_head, free_com);
	if (n)
	{
		free(g_minishell.input);
		g_minishell.input = NULL;
	}
}

void			shell_init(char **env)
{
	char	*cwd;

	g_env.env_h = array_to_list(env);
	cwd = getcwd(NULL, 0);
	add_element("PWD", cwd);
	free(cwd);
	add_element("SHLVL", "1");
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_int);
	g_minishell.ret = 0;
}

int				main(int ac, char **av, char **ev)
{
	shell_init(ev);
	av = NULL;
	ac = 0;
	while (1)
	{
		prompt(NULL);
		com_initiate();
		g_minishell.input = read_line();
		shell_parse();
		shell_exec(1);
	}
	return (g_minishell.ret);
}
