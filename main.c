/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmkhwana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:34:57 by lmkhwana          #+#    #+#             */
/*   Updated: 2018/09/18 12:47:47 by lmkhwana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_env(char ***env, char **environ)
{
	int i;
	int j;

	i = -1;
	while (environ[++i])
		NULL;
	(*env) = (char**)ft_memalloc(sizeof(char*) * i);
	i = -1;
	while (environ[++i])
	{
		(*env)[i] = (char*)ft_memalloc(PATH_MAX + 1);
		j = -1;
		while (environ[i][++j])
			(*env)[i][j] = environ[i][j];
		(*env)[i][j] = 0;
	}
	(*env)[i] = NULL;
	i = -1;
}

void		display_prompt(void)
{
	ft_putstr("$> ");
}

static char	**run_commands(char **comands, char **env)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (comands[j])
	{
		args = ft_strtok(comands[j], SPACES);
		env = exec_commands(args, env);
		free(comands[j]);
		j++;
		while (args[i])
			free(args[i++]);
		(args) ? free(args) : 0;
		if (!env)
			return (NULL);
	}
	return (env);
}

static void	get_input(char **input, char **environ)
{
	int		ret;
	char	buf;
	int		i;
	int		count;

	*input = ft_strnew(1);
	count = 1;
	i = 0;
	while ((ret = read(0, &buf, 1)) && buf != '\n')
	{
		*(*input + i++) = buf;
		*input = ft_realloc(*input, count, count + 1);
		count++;
	}
	*(*input + i) = '\0';
	if (!ret)
	{
		free(*input);
		exit_command(environ);
	}
}

int			main(int ac, char **args, char **environ)
{
	char	*line;
	char	**comands;
	char	**env;

	(void)ac;
	(void)args;
	create_env(&env, environ);
	while (env)
	{
		display_prompt();
		signal(SIGINT, signal_handler);
		set_directory(env, "PWD");
		get_input(&line, env);
		if (!line || !*line)
			continue ;
		comands = ft_strtok(line, ";");
		env = run_commands(comands, env);
		free(comands);
		free(line);
	}
	return (0);
}
