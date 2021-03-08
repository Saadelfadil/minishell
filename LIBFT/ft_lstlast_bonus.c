/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:44:55 by mbrija            #+#    #+#             */
/*   Updated: 2019/10/19 17:44:58 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *currrent;

	currrent = lst;
	if (currrent == NULL)
		return (NULL);
	while (currrent->next != NULL)
		currrent = currrent->next;
	return (currrent);
}
