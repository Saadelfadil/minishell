/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:30:48 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/05 14:11:49 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		exec_builtin(char **cmd, int ret)
{
	if (ret == 1)
		ft_echo(cmd);
	else if (ret == 2)
		return (ft_cd(cmd));
	else if (ret == 3)
		ft_pwd();
	else if (ret == 4)
		return (ft_export(cmd));
	else if (ret == 5)
		return (ft_unset(cmd));
	else if (ret == 6)
		ft_env(cmd);
	else if (ret == 7)
		return (ft_exit(cmd));
	return (0);
}
