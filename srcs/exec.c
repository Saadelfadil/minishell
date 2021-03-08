/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:27:00 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/07 15:11:28 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int		senko_wait(void)
{
	int ret;
	int	pid;

	pid = wait(&ret);
	if (WIFEXITED(ret))
		if (g_minishell.last_cmd == pid)
			g_minishell.ret = WEXITSTATUS(ret);
	g_minishell.fork_p = 0;
	return (pid);
}

static	int		init_exec(t_command *com, int *n, char ***av)
{
	if (!com || !com->argv || com->in_red == -1 || com->out_red == -1)
		return (1);
	if (com->in_red == 0)
	{
		while ((*n)--)
			senko_wait();
		*n = 0;
	}
	convert_argv_env(&com->argv, NULL, NULL);
	*av = list_to_array(com->argv);
	return (0);
}

static	void	builtin_coms(t_command *com, char **argv, int ret)
{
	int in;
	int out;

	g_minishell.last_cmd = ret;
	in = dup(0);
	out = dup(1);
	dup2(com->in_red, 0);
	dup2(com->out_red, 1);
	g_minishell.ret = exec_builtin(argv, ret);
	dup2(in, 0);
	dup2(out, 1);
	if (com->in_red != 0)
		close(com->in_red);
	if (com->out_red != 1)
		close(com->out_red);
	free(argv);
}

static void		system_coms(t_command *com, int ret, int *n)
{
	if ((ret = fork()) == 0)
	{
		if (com->pipe[0] != -1)
			close(com->pipe[0]);
		if (com->pipe[1] != -1)
			close(com->pipe[1]);
		signal(SIGINT, SIG_DFL);
		exec_sys_com(com);
	}
	else if (ret < 0)
		fork_error_hack();
	else
	{
		g_minishell.last_cmd = ret;
		if (com->pipe[1] != -1)
			close(com->pipe[1]);
		if (com->in_red != 0)
			close(com->in_red);
		if (com->out_red != 1)
			close(com->out_red);
		g_minishell.fork_p = 1;
		(*n)++;
	}
}

void			exec_commands(void)
{
	t_list		*lst;
	t_command	*com;
	int			ret;
	char		**argv;
	int			n;

	lst = g_minishell.com_head;
	n = 0;
	while (lst != NULL)
	{
		open_red_files(com = lst->content);
		if (init_exec(com, &n, &argv) && ((lst = lst->next) || 1))
			continue;
		if ((ret = is_command(argv[0])))
			builtin_coms(com, argv, ret);
		else
		{
			free(argv);
			system_coms(com, ret, &n);
		}
		lst = lst->next;
	}
	while (n--)
		senko_wait();
	free_red_files();
}
