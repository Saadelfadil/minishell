/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:49:08 by mbrija            #+#    #+#             */
/*   Updated: 2019/10/09 16:49:09 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*cdest;
	unsigned char	*csrc;
	int				i;

	cdest = (unsigned char*)dest;
	csrc = (unsigned char*)src;
	i = 0;
	while ((size_t)i < n)
	{
		if (csrc[i] != (unsigned char)c)
		{
			cdest[i] = csrc[i];
			i++;
		}
		else
		{
			cdest[i] = csrc[i];
			return (&dest[i + 1]);
		}
	}
	return (NULL);
}
