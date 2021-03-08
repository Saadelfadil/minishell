/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:49:51 by mbrija            #+#    #+#             */
/*   Updated: 2019/10/09 16:49:53 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*csrc;
	char	*cdest;

	csrc = (char*)src;
	cdest = (char*)dest;
	if (!dest && !src)
		return (dest);
	if (cdest < csrc)
		return (ft_memcpy(dest, src, n));
	while (n--)
		cdest[n] = csrc[n];
	return (dest);
}
