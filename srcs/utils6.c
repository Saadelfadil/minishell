/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:29:56 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/03 18:59:39 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_from_env(char *s)
{
	t_list *cur;

	cur = g_env.env_h;
	while (cur)
	{
		if (ft_strncmp(cur->content, s, ft_strlen(s)))
			return (cur->content + ft_strlen(s) + 1);
		cur = cur->next;
	}
	return (NULL);
}

char	*get_path(void)
{
	t_list	*curr;

	curr = g_env.env_h;
	while (curr)
	{
		if (!ft_strncmp(curr->content, "PATH", 4))
			return (curr->content + 5);
		curr = curr->next;
	}
	return (NULL);
}

void	free_double_arr(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int		check_path(char *s)
{
	char		**sp;
	int			i;
	struct stat	sbuff;

	i = 0;
	sp = ft_split(s, ':');
	if (!sp[0] && ft_strchr(s, ':'))
	{
		free_double_arr(sp);
		return (1);
	}
	while (sp[i])
	{
		if (stat(sp[i], &sbuff) != 0)
		{
			free_double_arr(sp);
			return (0);
		}
		i++;
	}
	free_double_arr(sp);
	return (1);
}

void	check_permissions(char **ev_args, char **argv, struct stat sbuff,
	int ret)
{
	if (ret == 0 && sbuff.st_mode & S_IXUSR && sbuff.st_mode & S_IRUSR &&
	!S_ISDIR(sbuff.st_mode) && check_path(get_path()))
	{
		execve(argv[0], argv, ev_args);
		exit(0);
	}
	else if (ret == 0 && ((!(sbuff.st_mode & S_IXUSR) || !(sbuff.st_mode &
	S_IRUSR)) || S_ISDIR(sbuff.st_mode)) && ft_strchr(argv[0], '/'))
	{
		if (S_ISDIR(sbuff.st_mode))
			senko_print("SSHELL: ", argv[0], ": ", "is a directory\n");
		else if (!(sbuff.st_mode & S_IXUSR) || !(sbuff.st_mode & S_IRUSR))
			senko_print("SSHELL: ", argv[0], ": ", "Permission Denied\n");
		exit(126);
	}
}
