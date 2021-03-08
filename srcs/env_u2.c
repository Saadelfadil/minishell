/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_u2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:26:53 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/07 15:12:42 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			*replace_env(char *str, char *res, int *i, int len)
{
	char	*tmp;
	char	*var;

	tmp = ft_substr(str, *i, len);
	(*i) += len;
	var = get_var(tmp);
	free(tmp);
	tmp = res;
	res = ft_strjoin(res, var);
	free(var);
	free(tmp);
	return (res);
}

char			*ft_append(char *str, char *res, int *i)
{
	res = ft_strappend(res, str[*i]);
	(*i)++;
	return (res);
}

int				custom_len(char *s)
{
	int len;

	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	return (len);
}

char			*env_quotes_conv(char *str)
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
		(quote[0] == '"' && (str[i + 1] == '"'))) && is_on_char(str, i, " ")
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
