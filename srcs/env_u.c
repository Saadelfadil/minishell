/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_u.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:26:41 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/07 15:11:33 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*g_evir_sep = "'\"$\\?=," SEP;

char	*get_var(char *name)
{
	char	*res;
	t_list	*lst;

	lst = list_chr(g_env.env_h, name);
	if (lst == NULL)
		return (ft_strdup(""));
	res = ft_strchr(lst->content, '=');
	if (res == NULL)
		return (ft_strdup(""));
	return (ft_strdup(res + 1));
}

void	export_str(char *str)
{
	t_list	*node;
	char	*pfree;

	if ((node = list_chr(g_env.env_h, str)))
	{
		pfree = node->content;
		node->content = ft_strdup(str);
		free(pfree);
	}
	else
		ft_lstadd_back(&g_env.env_h, ft_lstnew(ft_strdup(str)));
}

void	add_element(char *key, char *value)
{
	char	*pfree;
	char	*temp;

	temp = ft_strjoin(key, "=");
	pfree = temp;
	if (value)
	{
		temp = ft_strjoin(temp, value);
		free(pfree);
	}
	export_str(temp);
	free(temp);
}

char	*conv_env(char *str)
{
	int		i;
	char	*res;
	int		len;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (is_on_char(str, i, "$") &&
		(len = word_len(str + i + 1, g_evir_sep, 1)) > 0)
		{
			i++;
			if (ft_strchr("0123456789", str[i]) && i++)
				continue;
			res = replace_env(str, res, &i, len);
			g_minishell.expanded = 1;
		}
		else if (str[i + 1] == '?')
			res = last_com_return(res, &i);
		else
			res = ft_append(str, res, &i);
	}
	free(str);
	return (res);
}
