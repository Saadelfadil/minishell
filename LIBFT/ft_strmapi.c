/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:23:54 by mbrija            #+#    #+#             */
/*   Updated: 2019/10/14 16:23:56 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*newstr(size_t size)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (!(temp = malloc(sizeof(*temp) * (size + 1))))
		return (NULL);
	if (temp)
	{
		while (i <= size)
		{
			temp[i] = '\0';
			i++;
		}
	}
	return (temp);
}

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*blank;

	if (!s || !f)
		return (NULL);
	if (!(blank = newstr(ft_strlen(s))))
		return (NULL);
	i = 0;
	if (s && f)
	{
		while (s[i] != '\0')
		{
			blank[i] = (*f)(i, s[i]);
			i++;
		}
	}
	blank[i] = '\0';
	return (blank);
}
