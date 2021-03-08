/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:08:21 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/03/05 14:08:22 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_exit(char **argv)
{
	char	*s;

	s = "argument required\n";
	write(2, "exit\n", 5);
	if (!argv || !argv[1])
		exit(g_minishell.ret);
	if (!is_number(argv[1]))
	{
		senko_print("SSHEL: exit ", argv[1], " ", s);
		exit(255);
	}
	if (ptr_strlen(argv) > 2)
	{
		senko_print("SSHELL: ", "exit: ", NULL, "too many arguments\n");
		exit(1);
	}
	exit_value(0, argv);
	return (0);
}
