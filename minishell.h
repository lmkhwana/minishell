/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmkhwana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 12:55:37 by lmkhwana          #+#    #+#             */
/*   Updated: 2018/09/18 13:02:00 by lmkhwana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <limits.h>
# include "libft/libft.h"
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <signal.h>

# define SPACES " \t\n\r\a\""

# define R(e) ({return (e);})
# define NOT_EXIST(p, e) ({ft_putstr("cd: no such file or directory.\n");R(e);})
# define NOT_DIR(p, e) ({ft_putstr("cd: not a directory.\n"); return (e);})
# define NO_PERM(p, e) ({ft_putstr("cd: permission denied.\n"); return (e);})
# define NO_PWD(p, e) ({ft_putstr("cd: string not in pwd.\n"); return (e);})

char	*find_env_variable(char *name, char **env);
int		read_arguments(char **args, int j, char **env);
int		check_string(char **args, int j, char **env);
void	set_directory(char **env, char *dirname);
int		check_environ(char *args, int k, char **env);

char	**exec_commands(char **args, char **env);
void	free_env(char **env);

void	signal_handler(int signo);

char	**run(char **args, char **env);
char	**echo_command(char **args, char **env);
void	display_prompt(void);
char	**cd_command(char	**args, char **env);
char	**setenv_command(char	**args, char **env);
char	**unsetenv_command(char **args, char **env);
char	**env_command(char **args);
char	**exit_command(char **env);
char	**pwd_command(char **args, char **env);

#endif
