/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:27:16 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/06 16:25:33 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					parse_pipe(char *str)
{
	t_command	*com;
	int			p[2];

	com = g_minishell.com_tail->content;
	if (pipe(p) < 0)
	{
		ft_putendl_fd("pipe error", 2);
		exit(1);
	}
	com->out_red = p[1];
	com->pipe[0] = p[0];
	g_minishell.com_tail = ft_lstnew(new_command(p[0], 1, p[1]));
	ft_lstadd_back(&g_minishell.com_head, g_minishell.com_tail);
	str = NULL;
	g_minishell.read_next = "|";
	g_minishell.pos++;
	return (0);
}

static	t_red_file	*red_file(char *file, char type)
{
	t_red_file	*red_file;

	red_file = malloc(sizeof(t_red_file));
	red_file->file = file;
	red_file->type = type;
	return (red_file);
}

int					parse_semi_col(char *str)
{
	t_command *com;

	com = g_minishell.com_tail->content;
	g_minishell.com_tail = ft_lstnew(new_command(0, 1, -1));
	ft_lstadd_back(&g_minishell.com_head, g_minishell.com_tail);
	str = NULL;
	g_minishell.read_next = NULL;
	g_minishell.pos++;
	return (0);
}

int					parse_output_red(char *str, char *app)
{
	if (senko_equal_str(g_minishell.read_next, ">"))
	{
		ft_lstadd_back(&((t_command *)g_minishell.com_tail->content)->red_files,
		ft_lstnew(red_file(str, 1)));
		g_minishell.read_next = NULL;
	}
	else if (senko_equal_str(g_minishell.read_next, ">>"))
	{
		ft_lstadd_back(&((t_command *)g_minishell.com_tail->content)->red_files,
		ft_lstnew(red_file(str, 2)));
		g_minishell.read_next = NULL;
	}
	else
	{
		if (senko_equal_str(app, ">>"))
			g_minishell.pos += 2;
		else
			g_minishell.pos++;
		g_minishell.read_next = app;
	}
	return (0);
}

int					parse_input_red(char *str)
{
	if (senko_equal_str(g_minishell.read_next, "<"))
	{
		ft_lstadd_back(&((t_command *)g_minishell.com_tail->content)->red_files,
		ft_lstnew(red_file(str, 0)));
		g_minishell.read_next = NULL;
	}
	else
	{
		g_minishell.read_next = "<";
		g_minishell.pos++;
	}
	return (0);
}
