/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:08:17 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/03/05 14:08:19 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(char **argv)
{
	t_list *cur;

	cur = g_env.env_h;
	argv = NULL;
	while (cur)
	{
		if (ft_strchr(cur->content, '='))
		{
			ft_putstr_fd(cur->content, 1);
			ft_putstr_fd("\n", 1);
		}
		cur = cur->next;
	}
}
