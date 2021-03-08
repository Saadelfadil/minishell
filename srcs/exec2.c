/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:27:06 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/07 11:32:09 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		iter_path(int i, char **ev_args, char **argv)
{
	char		*s;
	struct stat	sbuff;

	while (g_env.path[++i])
	{
		s = join_path(g_env.path[i], "/", argv[0]);
		if (stat(s, &sbuff) == 0 && sbuff.st_mode & S_IXUSR)
		{
			execve(s, argv, ev_args);
			free(s);
			free(ev_args);
			return (0);
		}
		else if (stat(s, &sbuff) == 0 && !(sbuff.st_mode & S_IXUSR))
		{
			senko_print("SSHELL: ", s, ": ", "Permission Denied\n");
			free(ev_args);
			free(s);
			exit(126);
		}
		free(s);
	}
	return (1);
}

int		try_path(char **argv)
{
	char	**ev_args;

	ev_args = list_to_array(g_env.env_h);
	if (!(g_env.path = ft_split(get_path(), ':')))
		return (1);
	if (!iter_path(-1, ev_args, argv))
		return (0);
	free(ev_args);
	return (1);
}

int		sys_norm_hack(int ret, char **argv)
{
	if (ret && argv[0] && ft_strchr(argv[0], '/'))
	{
		senko_print("SSHELL: ", argv[0], ": ", strerror(errno));
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (!get_path() || *get_path() == 0)
		senko_print("SSHELL: ", argv[0], ": ", "No Such File or Directoy\n");
	else
		senko_print("SSHELL: ", argv[0], ": ", "Command not found\n");
	return (1);
}

int		sys_redirect(char **argv)
{
	char		**ev_args;
	struct stat	sbuff;
	int			ret;

	ev_args = list_to_array(g_env.env_h);
	ret = stat(argv[0], &sbuff);
	if (S_ISLNK(sbuff.st_mode))
		ret = lstat(argv[0], &sbuff);
	check_permissions(ev_args, argv, sbuff, ret);
	free(ev_args);
	if (argv[0] == NULL)
		return (1);
	if (!ft_strchr(argv[0], '/'))
		if (!try_path(argv))
			return (0);
	if (sys_norm_hack(ret, argv) == 1)
		return (1);
	return (1);
}

void	exec_sys_com(t_command *com)
{
	char **argv;

	argv = list_to_array(com->argv);
	open_red_files(com);
	dup2(com->in_red, 0);
	dup2(com->out_red, 1);
	sys_redirect(argv);
	exit(127);
}
