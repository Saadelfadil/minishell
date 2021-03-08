/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:29:41 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/03 18:54:03 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		custom_atoi(const char *str, int i, int *error)
{
	int					sign;
	unsigned long long	result;

	i = 0;
	while (str[0] == '\t' || str[0] == '\n' || str[0] == '\v' ||
			str[0] == '\f' || str[0] == ' ' || str[0] == '\r')
		str++;
	result = 0;
	sign = (str[0] == '-' ? -1 : 1);
	str = (str[0] == '-' || str[0] == '+') ? str + 1 : str;
	while (str[0] == '0')
		str++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i++] - '0');
		if ((result > 9223372036854775808ULL && sign == -1) ||
		(result >= 9223372036854775808ULL && sign == 1))
		{
			*error = 1;
			return (sign == 1 ? -1 : 0);
		}
	}
	return (result * sign);
}

void	exit_value(int ret, char **argv)
{
	int		error;
	char	*s;

	error = 0;
	s = "argument required";
	ret = custom_atoi(argv[1], 0, &error);
	if (error)
	{
		senko_print("SSHELL : exit ", argv[1], " ", s);
		exit(255);
	}
	if (ret > 255)
		exit(ret - 1 - 255);
	else if (ret < 0)
		exit(256 + ret);
	else
		exit(ret);
}

int		ptr_strlen(char **dp)
{
	int i;

	i = 0;
	while (dp[i])
		i++;
	return (i);
}

void	lst_add(t_list *lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = lst->next;
	lst->next = new;
}

t_list	*lst_remove(t_list **lst, t_list *to_del, void (*del)(void *))
{
	t_list *tmp;

	if (!(*lst) || !to_del)
		return (*lst);
	if (*lst == to_del)
	{
		*lst = (*lst)->next;
		if (del)
			ft_lstdelone(to_del, del);
		return (*lst);
	}
	tmp = *lst;
	while (tmp->next)
	{
		if (tmp->next == to_del)
		{
			tmp->next = tmp->next->next;
			if (del)
				ft_lstdelone(to_del, del);
		}
		tmp = tmp->next;
	}
	return (*lst);
}
