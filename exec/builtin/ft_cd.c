/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:08:09 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/03/05 14:08:10 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norme_hack(char **argv, char *cur)
{
	char pwdold[1000];
	char *oldcur;

	if (chdir(argv[1]) == 0)
	{
		oldcur = getcwd(pwdold, 200);
		add_element("PWD", oldcur);
		add_element("OLDPWD", cur);
	}
	else
		senko_print("SSHEL :", " cd: ", argv[1], "no such file or directory\n");
}

int		ft_cd(char **argv)
{
	char *cur;
	char pwdcur[1000];
	char *str;

	cur = getcwd(pwdcur, 200);
	str = get_var("HOME");
	if (!argv[1])
	{
		argv[0] = str;
		chdir(argv[0]);
	}
	else if (argv[0] && argv[1] && !argv[2])
	{
		norme_hack(argv, cur);
		return (1);
	}
	return (0);
}
