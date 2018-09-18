/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmkhwana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:40:20 by lmkhwana          #+#    #+#             */
/*   Updated: 2018/09/18 13:27:33 by lmkhwana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**replace(char **args, char **env)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(args[1]);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], args[1], len) && env[i][len] == '=')
			break ;
	}
	ft_strclr(env[i]);
	ft_strcat(env[i], args[1]);
	ft_strcat(env[i], "=");
	ft_strcat(env[i], args[2]);
	return (env);
}

static char	**create_new(char **args, char **env)
{
	char	***e;
	char	**environ;
	int		i;

	i = -1;
	e = &env;
	while ((*e)[++i])
		NULL;
	environ = (char**)ft_memalloc(sizeof(char*) * (i + 2));
	i = -1;
	while ((*e)[++i])
		environ[i] = ft_strdup((*e)[i]);
	free_env(env);
	environ[i] = (char*)ft_memalloc(PATH_MAX + 1);
	ft_strncat(environ[i], args[1], ft_strlen(args[1]));
	ft_strncat(environ[i], "=", 1);
	ft_strncat(environ[i], args[2], ft_strlen(args[2]));
	e = &environ;
	return (*e);
}

static void	free_ar(char **a)
{
	free(a[1]);
	free(a[2]);
	free(a);
}

static char	**one_arg(char **args, char **env)
{
	int		i;
	int		j;
	char	**a;

	i = (args[1][0] == '"');
	j = 0;
	a = (char**)ft_memalloc(sizeof(char*) * 3);
	a[0] = NULL;
	a[1] = ft_strnew(sizeof(args[1]));
	a[2] = ft_strnew(sizeof(args[1]));
	while (args[1][i] != '=' && args[1][i])
		a[1][j++] = args[1][i++];
	if (!args[1][i])
	{
		free(a);
		return (env);
	}
	j = 0;
	while (args[1][++i] != '"' && args[1][i])
		a[2][j++] = args[1][i];
	env = setenv_command(a, env);
	free_ar(a);
	return (env);
}

char		**setenv_command(char **args, char **env)
{
	if (!args[1])
		return (env);
	if (!args[2])
		return (one_arg(args, env));
	if (find_env_variable(args[1], env)[0] != 0)
		return (replace(args, env));
	return (create_new(args, env));
}
