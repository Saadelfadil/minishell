/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:50:13 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/03 16:17:12 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int j;

	j = 0;
	if (s == NULL)
		return (NULL);
	while (s[j])
		j++;
	i = 0;
	while (i <= j)
		if (s[i] == (char)c)
			return ((char*)s + i);
		else
			i++;
	return (NULL);
}
