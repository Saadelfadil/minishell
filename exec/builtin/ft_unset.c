/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:08:32 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/03/05 14:08:33 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		is_valid_id(char *s)
{
	int i;

	i = 0;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[i])
	{
		if (!ft_isalpha(s[i]) && s[i] != '_' && !ft_isdigit(s[i]))
			if (!(s[i] == '+' && !s[i + 1]))
				return (0);
		i++;
	}
	return (1);
}

int		ft_unset(char **argv)
{
	int		i;
	int		ret;
	char	*s;

	s = "not a valid identifier\n";
	i = 1;
	ret = 0;
	if (!argv[1])
		return (0);
	while (argv[i])
	{
		if (!is_valid_id(argv[i]))
		{
			senko_print("SSHELL: unset: `", argv[i], "': ", s);
			ret = 1;
			i++;
			continue ;
		}
		ft_lstclear_one_if(&g_env.env_h, argv[i], ft_strncmp, free);
		i++;
	}
	return (ret);
}
