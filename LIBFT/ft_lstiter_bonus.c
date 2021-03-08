/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:44:43 by mbrija            #+#    #+#             */
/*   Updated: 2019/10/19 17:44:44 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void*, void*), void *para)
{
	t_list	*element;

	element = lst;
	if (element)
	{
		while (element != NULL)
		{
			f(element->content, para);
			element = element->next;
		}
	}
}
