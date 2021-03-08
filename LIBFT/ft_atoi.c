/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:45:06 by mbrija            #+#    #+#             */
/*   Updated: 2019/10/09 16:45:19 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int i;
	int nb;
	int sign;

	sign = 1;
	i = -1;
	nb = 0;
	while (str[++i] != '\0')
	{
		if ((str[i] > '/' && str[i] < ':') || str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				sign = -1;
			if (str[i] == '+' || str[i] == '-')
				i++;
			while (str[i] > '/' && str[i] < ':')
			{
				nb = nb * 10 + str[i++] - 48;
			}
			return (nb * sign);
		}
		else if (str[i] != ' ' && (str[i] < 9 || str[i] > 13))
			return (nb * sign);
	}
	return (nb * sign);
}
