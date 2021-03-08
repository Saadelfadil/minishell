/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:45:44 by mbrija            #+#    #+#             */
/*   Updated: 2019/10/09 16:45:50 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	int		j;
	size_t	ldst;
	size_t	lsrc;
	int		free;

	lsrc = ft_strlen(src);
	ldst = ft_strlen(dst);
	free = (int)size - (int)ldst;
	i = 0;
	j = ldst;
	if (free < 0 || size == 0)
		return (size + lsrc);
	if ((size_t)free > lsrc)
	{
		while ((size_t)i < lsrc + 1)
			dst[j++] = src[i++];
		return (ldst + lsrc);
	}
	while (free-- > 1)
		dst[j++] = src[i++];
	dst[j++] = '\0';
	return (ldst + lsrc);
}
