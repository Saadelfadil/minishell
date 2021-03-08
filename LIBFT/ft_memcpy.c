/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:49:39 by mbrija            #+#    #+#             */
/*   Updated: 2019/10/09 16:49:40 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int		i;
	char	*cdest;
	char	*csrc;

	if (!dest && !src)
		return (dest);
	cdest = (char*)dest;
	if (src)
		csrc = (char*)src;
	i = 0;
	while ((size_t)i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}
