/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmkhwana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:39:55 by lmkhwana          #+#    #+#             */
/*   Updated: 2018/09/18 11:40:03 by lmkhwana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pwd_command(char **args, char **env)
{
	char	buf[PATH_MAX + 1];
	int		i;

	i = 0;
	while (args[i])
		i++;
	(i > 1) ? ft_putstr("pwd: too many arguments\n") : 0;
	if (i == 1)
	{
		ft_putstr(getcwd(buf, PATH_MAX));
		ft_putstr("\n");
	}
	return (env);
}
