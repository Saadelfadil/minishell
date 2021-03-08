/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:27:47 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/07 15:12:47 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			is_backslash(const char *str, int i)
{
	int	ibsl;

	i--;
	ibsl = 0;
	while (i >= 0 && str[i] == '\\')
	{
		ibsl = !ibsl;
		i--;
	}
	return (ibsl);
}

static int	is_quote(const char *str, int i)
{
	char	quote[2];
	int		j;

	ft_bzero(quote, 2);
	j = 0;
	while (j <= i)
	{
		if (!quote[0] && (str[j] == '"' || str[j] == '\'')
		&& !is_backslash(str, j))
			quote[0] = str[j];
		else if ((quote[0] == '\'' && str[j] == '\'') ||
		(quote[0] == '"' && str[j] == '\"' && !is_backslash(str, j)))
			quote[0] = 0;
		j++;
	}
	if (quote[0] == '\'' && str[i] != '\'')
		return (quote[0]);
	else if (quote[0] == '"' && str[i] != '"')
		return ((str[i] == '$' || str[i] == '\\') ? 0 : quote[0]);
	return (0);
}

int			is_on_char(const char *str, int i, char *c)
{
	int		j;
	char	*quote[2];

	j = 0;
	ft_bzero(quote, 2);
	while (c[j])
	{
		if (str[i] == c[j])
			if (i == 0 || (!is_backslash(str, i) && !is_quote(str, i)))
				return (1);
		j++;
	}
	return (0);
}

char		*quotes_conv(char *str)
{
	int		i;
	char	*res;
	char	quote[2];

	i = 0;
	ft_bzero(quote, 2);
	res = ft_strdup("");
	while (str[i])
	{
		if ((!quote[0] ||
		(quote[0] == '"' && (str[i + 1] == '\\' ||
		str[i + 1] == '$' || str[i + 1] == '"'))) && is_on_char(str, i, "\\")
		&& ++i)
			continue;
		if ((!quote[0] && is_on_char(str, i, "'\"")) ||
		(quote[0] == '\'' && str[i] == '\'') || is_on_char(str, i, quote))
			quote[0] = quote[0] ? 0 : str[i];
		else
			res = ft_strappend(res, str[i]);
		i++;
	}
	free(str);
	return (res);
}

void		convert_argv_env(t_list **av, t_list *prev, char *s)
{
	t_list *tmp;

	if (!(*av))
		return ;
	tmp = *av;
	while (tmp)
	{
		tmp->content = conv_env(tmp->content);
		s = tmp->content;
		split_args(tmp);
		s != tmp->content ? free(s) : NULL;
		if (*((char *)tmp->content) == 0)
			remove_hack(av, prev, tmp);
		else if (g_minishell.expanded == 1)
		{
			tmp->content = env_quotes_conv(tmp->content);
			prev = tmp;
			tmp = tmp->next;
			g_minishell.expanded = 0;
		}
		else
			loop_hack(&prev, &tmp);
	}
}
