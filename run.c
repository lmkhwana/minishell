/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmkhwana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:40:07 by lmkhwana          #+#    #+#             */
/*   Updated: 2018/09/18 11:40:15 by lmkhwana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_error(char *p, char *arg)
{
	int i;
	int slash;

	i = -1;
	slash = 0;
	while (arg[++i])
	{
		if (arg[i] == '/')
			slash++;
	}
	if (slash > 0 && !p)
	{
		ft_putstr("minishell: no such file or directory: ");
		ft_putstr(arg);
		ft_putstr("\n");
	}
	else if (!p)
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr(arg);
		ft_putstr("\n");
	}
}

static void	create_process(char *ex, char **args, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(ex, args, env) == -1)
		{
			ft_putstr("minishell: permission denied: ");
			ft_putstr(ex);
			ft_putstr("\n");
		}
		exit(-1);
	}
	else if (pid < 0)
	{
		ft_putstr("minishell: unable to fork create_process.");
		exit(-1);
	}
	else
		wait(&pid);
}

static void	find_cmd(char **args, char **env)
{
	char	**p;
	char	*path;
	int		i;

	i = -1;
	p = ft_strtok(find_env_variable("$PATH", env), ":");
	path = ft_strnew(PATH_MAX);
	while (p[++i])
	{
		ft_strclr(path);
		ft_strcat(path, p[i]);
		(args[0][0] == '/') ? 0 : ft_strcat(path, "/");
		ft_strcat(path, args[0]);
		if (access(path, F_OK) != -1)
		{
			create_process(path, args, env);
			break ;
		}
	}
	check_error(p[i], args[0]);
	i = -1;
	while (p[++i])
		free(p[i]);
	free(path);
	free(p);
}

char		**run(char **args, char **env)
{
	if (args[0] == NULL)
		return (env);
	(access(args[0], F_OK) != -1) ? create_process(args[0], args, env) :
		find_cmd(args, env);
	return (env);
}
