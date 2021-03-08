/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:49:17 by mbrija            #+#    #+#             */
/*   Updated: 2019/10/09 16:49:19 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*cstr;
	int				i;

	cstr = (unsigned char*)str;
	i = -1;
	while ((size_t)++i < n)
		if (cstr[i] == (unsigned char)c)
			return (cstr + i);
	return (NULL);
}
