/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmkhwana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:38:31 by lmkhwana          #+#    #+#             */
/*   Updated: 2018/09/18 11:38:42 by lmkhwana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg(char **s, int j, char **env)
{
	int			k;

	k = 0;
	while (s[j][k])
	{
		if (s[j][k] == '"' || s[j][k] == '\'' || s[j][k] == '\\')
			k++;
		if (!s[j][k])
			break ;
		if ((s[j][k] == '$' || s[j][k] == '~') &&
				(k = check_environ(s[j], k, env)) == -1)
			return (-1);
		else
			(s[j][k]) ? ft_putchar(s[j][k]) : 0;
		k++;
	}
	return (0);
}

int			read_arguments(char **args, int j, char **env)
{
	while (args[j])
	{
		if (check_arg(args, j, env) == -1)
			return (-1);
		(args[++j]) ? ft_putchar(' ') : 0;
	}
	return (0);
}

int			check_string(char **args, int j, char **env)
{
	if (args[j][0])
	{
		if (read_arguments(args, j, env) == -1)
			return (-1);
	}
	return (0);
}

char		**echo_command(char **a, char **env)
{
	int		j;
	int		new_line;

	j = 0;
	if (!a[1] || !a[1][0])
	{
		ft_putchar('\n');
		return (env);
	}
	new_line = (!ft_strncmp("-n", a[++j], PATH_MAX)) ? 1 : 0;
	(new_line) ? j++ : 0;
	check_string(a, j, env);
	(new_line) ? 0 : ft_putchar('\n');
	return (env);
}
