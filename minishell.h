/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:30:21 by mbrija            #+#    #+#             */
/*   Updated: 2021/03/07 15:13:08 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "LIBFT/libft.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# define SEP " ;|<>"
# define CGRN "\e[1;32m"
# define CRED "\e[1;31m"
# define CBLU "\e[1;3;33m"
# define RESET "\e[0m"

typedef struct	s_env
{
	char		**path;
	char		*home;
	t_list		*env_h;
}				t_env;

typedef struct	s_minishell
{
	int			ret;
	int			status;
	int			export;
	char		*input;
	int			pos;
	int			pipe[2];
	int			fork_p;
	pid_t		last_cmd;
	t_list		*com_head;
	t_list		*com_tail;
	char		*read_next;
	int			expanded;
}				t_minishell;

typedef	struct	s_command
{
	t_list		*argv;
	t_list		*red_files;
	int			out_red;
	int			in_red;
	int			pipe[2];
}				t_command;

typedef	struct	s_red_file
{
	char		*file;
	char		type;
}				t_red_file;

t_minishell		g_minishell;
t_env			g_env;

void			com_initiate();
char			*read_line();
t_command		*new_command(int in, int out, int pipe);
void			free_com(void *com);
int				senko_equal_str(char *s1, char *s2);
int				err_syntax(char *err);
char			*ft_strappend(char *s, char c);
char			*ft_append(char *str, char *res, int *i);
t_list			*array_to_list(char **arr);
t_list			*list_chr(t_list *head, char *s);
int				env_len(char *s);
void			prompt(char *type);
char			*get_var(char *name);
int				is_backslash(const char *str, int i);
int				is_on_char(const char *str, int i, char *c);
int				end_pipe();
int				parse_pipe(char *str);
int				parse_semi_col(char	*str);
int				parse_output_red(char *str, char *app);
int				parse_input_red(char *str);
int				word_len(const char *str, char *c, int separator);
int				parse_command(char *str);
void			shell_parse(void);
void			shell_exec(int n);
void			add_element(char *key, char *value);
void			export_str(char *str);
int				is_command(char *s);
void			senko_print(char *s1, char *s2, char *s3, char *s4);
int				custom_atoi(const char *str, int i, int *error);
int				is_number(char *s);
int				senko_exit(char **argv);
void			exit_value(int ret, char **argv);
int				ptr_strlen(char **dp);
char			*quotes_conv(char *str);
char			*replace_env(char *str, char *res, int *i, int len);
char			*last_com_return(char *res, int *i);
int				open_file(char *file, int flag, char *type);
void			open_red_file(void *file, void *c);
void			open_red_files(t_command *com);
void			free_red_files();
void			lst_add(t_list *lst, t_list *new);
t_list			*lst_remove(t_list **lst, t_list *to_del, void (*del)(void *));
void			split_args(t_list *lst);
void			convert_argv_env(t_list **av, t_list *prev, char *s);
char			**list_to_array(t_list *lst);
void			exec_commands();
char			*conv_env(char *str);
void			delete_node(char *s);
int				custom_len(char *s);
char			*get_from_env(char *s);
void			exec_command(t_env *node);
int				exec_builtin(char **cmd, int ret);
void			ft_echo(char **args);
void			ft_env(char **argv);
int				ft_pwd(void);
int				ft_exit(char **cmd);
int				ft_export(char **argv);
int				ft_cd(char **argv);
int				ft_unset(char **argv);
int				is_valid_id(char *s);
void			exec_sys_com(t_command *com);
void			ft_lstclear_one_if(t_list **list, void *ref,
		int (*f)(), void (*del)(void*));
char			*get_path();
void			free_double_arr(char **arr);
int				check_path(char *s);
void			check_permissions(char **ev_args, char **argv,
		struct stat sbuff, int ret);
char			*join_path(char *s, char *s1, char *s2);
void			is_sigquit(int sig);
void			sig_int(int sig);
char			*env_quotes_conv(char *str);
void			loop_hack(t_list **prev, t_list **tmp);
void			remove_hack(t_list **av, t_list *prev, t_list *tmp);
void			fork_error_hack(void);

#endif
