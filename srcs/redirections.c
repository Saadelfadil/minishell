/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:28:24 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/07 12:09:15 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				open_file(char *file, int flag, char *type)
{
	t_command	*cmd;
	int			fd;
	int			red;
	char		*cfile;

	cfile = ft_strdup(file);
	file = quotes_conv(conv_env(cfile));
	cmd = g_minishell.com_head->content;
	red = senko_equal_str(type, "<") ? cmd->in_red : cmd->out_red;
	if (red == 2)
		close(red);
	if (senko_equal_str(type, "<"))
		fd = open(file, flag);
	else
		fd = open(file, flag, 0664);
	if (fd == -1)
	{
		senko_print("SSHELL: ", file, ": ", strerror(errno));
		ft_putstr_fd("\n", 2);
		g_minishell.ret = 1;
		g_minishell.status = 0;
	}
	free(file);
	return (fd);
}

void			open_red_file(void *file, void *c)
{
	int			fd;
	t_red_file	*red_file;
	t_command	*com;

	red_file = file;
	com = c;
	if (red_file->type == 0)
	{
		fd = open_file(red_file->file, O_RDONLY, "<");
		com->in_red = fd;
	}
	else if (red_file->type == 1)
	{
		fd = open_file(red_file->file, O_WRONLY | O_CREAT |
		O_TRUNC, ">");
		com->out_red = fd;
	}
	else if (red_file->type == 2)
	{
		fd = open_file(red_file->file, O_WRONLY | O_CREAT |
		O_APPEND, ">>");
		com->out_red = fd;
	}
}

void			open_red_files(t_command *com)
{
	g_minishell.export = 0;
	if (com->in_red != 0 || com->out_red != 1)
		g_minishell.export = 1;
	ft_lstiter(com->red_files, open_red_file, com);
}

static	void	free_red_file(void *p)
{
	t_red_file	*red_file;

	red_file = p;
	free(red_file->file);
	free(red_file);
}

void			free_red_files(void)
{
	t_list		*lst;
	t_command	*com;

	lst = g_minishell.com_head;
	while (lst != NULL)
	{
		com = lst->content;
		ft_lstclear(&com->red_files, free_red_file);
		lst = lst->next;
	}
}
