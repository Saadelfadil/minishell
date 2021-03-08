/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:08:24 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/03/05 15:05:23 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void		sort_env(t_list *env)
{
	t_list *tmp;
	t_list *cur;

	tmp = NULL;
	while (env)
	{
		cur = env->next;
		while (cur)
		{
			if (ft_strcmp(env->content, cur->content) > 0)
			{
				tmp = env->content;
				env->content = cur->content;
				cur->content = tmp;
			}
			cur = cur->next;
		}
		env = env->next;
	}
}

static void		export_update(char *str, char *start)
{
	int len;
	int i;

	i = 0;
	len = ft_strlen(start);
	ft_putstr_fd("declare -x ", 1);
	while (str[i])
		if (str[i] != '=')
			ft_putchar_fd(str[i++], 1);
		else
			break ;
	i = 1;
	ft_putstr_fd("=\"", 1);
	while (i < len)
		ft_putchar_fd(start[i++], 1);
	ft_putstr_fd("\"\n", 1);
}

int				another_norm_hack(char *key, char *argv)
{
	char	*s;

	s = "not a valid identifier\n";
	if (!is_valid_id(key) || argv[0] == '=')
	{
		g_minishell.ret = 1;
		senko_print("SSHEL: export: `", argv, "': ", s);
		return (1);
	}
	return (0);
}

int				ft_add_in_env(char *argv)
{
	char	key[200];
	char	*value;
	int		len;
	int		i;

	value = NULL;
	i = 0;
	value = ft_strchr(argv, '=');
	len = custom_len(argv);
	while (i < len)
	{
		key[i] = argv[i];
		i++;
	}
	key[i] = '\0';
	if (value == NULL)
		return (0);
	if (another_norm_hack(key, argv) == 1)
		return (1);
	add_element(key, value + 1);
	return (0);
}

int				ft_export(char **argv)
{
	t_list	*env;
	char	*start;
	int		i;
	int		ret_c;

	i = 1;
	env = g_env.env_h;
	while (argv[i])
		ret_c = ft_add_in_env(argv[i++]);
	if (!argv[1])
	{
		sort_env(env);
		while (env)
		{
			if ((start = ft_strchr(env->content, '=')))
				export_update(env->content, start);
			env = env->next;
		}
	}
	if (ret_c == 1)
		return (1);
	return (0);
}
