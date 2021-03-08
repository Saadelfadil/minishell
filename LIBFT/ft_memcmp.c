/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:49:30 by mbrija            #+#    #+#             */
/*   Updated: 2019/10/09 16:49:32 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*cstr1;
	unsigned char	*cstr2;
	size_t			i;

	cstr1 = (unsigned char*)str1;
	cstr2 = (unsigned char*)str2;
	i = 0;
	while (i < n)
	{
		if (cstr1[i] - cstr2[i] == 0)
			i++;
		else
			return (cstr1[i] - cstr2[i]);
	}
	return (0);
}
