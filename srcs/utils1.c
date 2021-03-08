/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:28:39 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/04 17:20:15 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command		*new_command(int in, int out, int pipe)
{
	t_command *com;

	com = malloc(sizeof(t_command));
	com->argv = NULL;
	com->in_red = in;
	com->out_red = out;
	com->red_files = NULL;
	com->pipe[0] = -1;
	com->pipe[1] = pipe;
	return (com);
}

void			free_com(void *com)
{
	ft_lstclear(&((t_command *)com)->argv, free);
	free(com);
}

int				senko_equal_str(char *s1, char *s2)
{
	int len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1);
	return (ft_strncmp(s1, s2, len + 1) == 0);
}

int				err_syntax(char *err)
{
	if (*err == '\x4')
		senko_print("SSHEL", "syntax error", ": ",
		"Unexpected EOF\n");
	else
	{
		if (*err == '\n')
			err = "newline";
		else if (ft_strncmp(err, ">>", 2) == 0)
			err = ">>";
		else
			err[1] = 0;
		senko_print("SSHELL :", "syntax error near unexpected token `",
		err, "'\n");
	}
	g_minishell.ret = 258;
	g_minishell.status = 0;
	g_minishell.read_next = NULL;
	return (1);
}

char			*ft_strappend(char *s, char c)
{
	char	strchar[2];
	char	*temp;

	temp = s;
	strchar[0] = c;
	strchar[1] = 0;
	s = ft_strjoin(s, strchar);
	free(temp);
	return (s);
}
