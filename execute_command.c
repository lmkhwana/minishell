/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmkhwana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:38:49 by lmkhwana          #+#    #+#             */
/*   Updated: 2018/09/18 11:38:57 by lmkhwana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**exec_commands(char **args, char **env)
{
	if (!args || !*args || !**args)
		return (env);
	else if (!ft_strncmp(args[0], "cd", PATH_MAX))
		return (cd_command(args, env));
	else if (!ft_strncmp(args[0], "echo", PATH_MAX))
		return (echo_command(args, env));
	else if (!ft_strncmp(args[0], "env", PATH_MAX))
		return (env_command(env));
	else if (!ft_strncmp(args[0], "setenv", PATH_MAX))
		return (setenv_command(args, env));
	else if (!ft_strncmp(args[0], "unsetenv", PATH_MAX))
		return (unsetenv_command(args, env));
	else if (!ft_strncmp(args[0], "pwd", PATH_MAX))
		return (pwd_command(args, env));
	else if (!ft_strncmp(args[0], "exit", PATH_MAX))
		return (exit_command(env));
	else
		return (run(args, env));
	return (env);
}
