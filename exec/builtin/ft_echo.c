/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:08:13 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/03/06 18:45:16 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int		n_skip(char *s)
{
	int i;

	i = 1;
	if (s[0] == '-' && s[1] == '\0')
		return (0);
	if (s[0] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void			ft_echo(char **argv)
{
	int i;
	int n_opt;

	n_opt = 0;
	if (!argv[1])
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	i = 1;
	while (argv[i] && n_skip(argv[i]))
	{
		n_opt = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i])
			ft_putstr_fd(" ", 1);
	}
	if (!n_opt)
		ft_putstr_fd("\n", 1);
}
