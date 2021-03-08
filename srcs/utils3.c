/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:28:53 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/03 18:57:26 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		word_len(const char *str, char *c, int separator)
{
	int		i;
	char	quote[2];

	i = 0;
	ft_bzero(quote, 2);
	while (str[i])
	{
		if (!quote[0] || is_on_char(str, i, quote))
		{
			if (is_on_char(str, i, "'\""))
				quote[0] = quote[0] ? 0 : str[i];
			if (separator && !ft_isalnum(str[i]) && str[i] != '_')
				break ;
			if (is_on_char(str, i, c))
				break ;
		}
		i++;
	}
	return (i);
}

int		parse_command(char *str)
{
	int			len;
	char		*args;
	t_command	*com;

	len = word_len(str, SEP, 0);
	str = ft_substr(str, 0, len);
	args = str;
	if (senko_equal_str(g_minishell.read_next, "<"))
		parse_input_red(str);
	else if (senko_equal_str(g_minishell.read_next, ">") ||
	senko_equal_str(g_minishell.read_next, ">>"))
		parse_output_red(args, g_minishell.read_next);
	else if (args)
	{
		com = g_minishell.com_tail->content;
		ft_lstadd_back(&com->argv, ft_lstnew(args));
	}
	g_minishell.read_next = NULL;
	return (0);
}

void	senko_print(char *s1, char *s2, char *s3, char *s4)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
	ft_putstr_fd(s4, 2);
}

int		is_number(char *s)
{
	int i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && (s[i] == '\t' || s[i] == '\f' || s[i] == '\r'))
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	i = 0;
	while (*s == '-' || *s == '+' || *s == '0')
		s++;
	while (s[i])
		i++;
	if (i > 19)
		return (0);
	return (1);
}

int		senko_exit(char **argv)
{
	char	*s;

	s = "argument required\n";
	write(2, "exit\n", 5);
	if (!argv || !argv[1])
		exit(g_minishell.ret);
	if (!is_number(argv[1]))
	{
		senko_print("SSHEL: exit ", argv[1], " ", s);
		exit(255);
	}
	if (ptr_strlen(argv) > 2)
	{
		senko_print("SSHELL: ", "exit: ", NULL, "too many arguments\n");
		exit(1);
	}
	exit_value(0, argv);
	return (0);
}
