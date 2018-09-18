/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmkhwana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:38:07 by lmkhwana          #+#    #+#             */
/*   Updated: 2018/09/18 12:51:59 by lmkhwana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cd_command(char **a, char **env)
{
	char		p[PATH_MAX + 1];
	struct stat	s;
	int			i;

	ft_bzero(p, PATH_MAX);
	i = 0;
	while (a[i++])
		NULL;
	(i > 3) ? NO_PWD(a[1], env) : (a)++;
	if (!*a || !ft_strcmp(*a, "~") || ((*a)[0] == '~' && (*a)[1] == '/'))
		ft_strcat(p, find_env_variable("~", env));
	if (*a && (*a)[0] == '~' && (*a)[1] == '/' && ft_strlen(*a) > 2)
		ft_strncat(p, (*a + 1), ft_strlen(*a));
	else if (*a && !ft_strcmp(*a, "-"))
	{
		ft_putstr(ft_strcat(p, find_env_variable("$OLDPWD", env)));
		ft_putstr("\n");
	}
	else if (*a && (*a)[0] != '~' && (*a)[0] != '-')
		ft_strncat(p, *a, PATH_MAX);
	(!(access(p, F_OK) == -1)) ? (lstat(p, &s)) : NOT_EXIST(p, env);
	(!(access(p, R_OK) == -1)) ? 0 : NO_PERM(p, env);
	(!S_ISDIR(s.st_mode)) ? NOT_DIR(p, env) : 0;
	set_directory(env, "OLDPWD");
	chdir(p);
	return (env);
}
