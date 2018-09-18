/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmkhwana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:40:59 by lmkhwana          #+#    #+#             */
/*   Updated: 2018/09/18 11:43:30 by lmkhwana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

char	*find_env_variable(char *name, char **env)
{
	int i;

	i = -1;
	(ft_strlen(name) == 1 && name[0] == '~') ? name = "$HOME" : 0;
	name += (name[0] == '$');
	while (env[++i])
	{
		if (!ft_strncmp(name, env[i], ft_strlen(name)))
			if (env[i][ft_strlen(name)] == '=')
				return (ft_strchr(env[i], '=') + 1);
	}
	return ("");
}

void	set_directory(char **env, char *dirname)
{
	char **a;

	a = (char**)ft_memalloc(sizeof(char*) * 4);
	a[0] = NULL;
	a[1] = ft_strdup(dirname);
	a[2] = ft_strnew(PATH_MAX);
	getcwd(a[2], PATH_MAX);
	a[3] = 0;
	setenv_command(a, env);
	free(a[1]);
	free(a[2]);
	free(a);
}

int		check_environ(char *args, int k, char **env)
{
	char *s;

	(find_env_variable(args, env)[0] != 0) ?
		s = find_env_variable(args, env) : 0;
	if (find_env_variable(args, env)[0] == 0)
		return (-1);
	ft_putstr(s);
	while (args[k])
		k++;
	return (k);
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		display_prompt();
		signal(SIGINT, signal_handler);
	}
}
