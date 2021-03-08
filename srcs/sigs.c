/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:28:32 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/07 11:23:44 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_sigquit(int sig)
{
	if (!g_minishell.fork_p)
		ft_putstr_fd("\b\b  \b\b", 1);
	else
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putnbr_fd(sig, 2);
		write(2, "\n", 1);
	}
}

void	sig_int(int sig)
{
	if (sig == SIGINT)
	{
		g_minishell.ret = 1;
		if (!g_minishell.fork_p)
		{
			ft_putendl_fd("\b\b  \b\b", 1);
			free(g_minishell.input);
			g_minishell.input = ft_strdup("");
			prompt(NULL);
		}
		else
		{
			g_minishell.ret = 130;
			write(1, "\n", 1);
		}
	}
	else if (sig == SIGQUIT)
		is_sigquit(sig);
}
