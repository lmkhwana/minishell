/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmkhwana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 13:07:52 by lmkhwana          #+#    #+#             */
/*   Updated: 2018/09/18 13:08:58 by lmkhwana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_chars(char *s, char *sep)
{
	int i;
	int chars;

	chars = 0;
	while (s[chars])
	{
		i = 0;
		while (sep[i])
		{
			if (s[chars] == sep[i++])
				return (chars);
		}
		chars++;
	}
	return (chars);
}

static int	count_parts(char *s, char *sep)
{
	int i;
	int parts;

	parts = 0;
	while (*s)
	{
		i = 0;
		while (sep[i])
			(*s == sep[i++]) ? parts++ : 0;
		s++;
	}
	return (parts + 1);
}

char		**ft_strtok(char *s, char *sep)
{
	char	**tok;
	int		parts;
	int		chars;
	int		i;
	int		j;

	parts = count_parts(s, sep);
	i = 0;
	tok = (char**)ft_memalloc(sizeof(char*) * parts + 1);
	while (i < parts)
	{
		j = 0;
		(s && !(chars = count_chars(s, sep))) ? s++ : 0;
		(s && chars) ? tok[i] = ft_strnew(chars) : 0;
		while (*s && j < chars && chars > 0)
			tok[i][j++] = *(s++);
		(tok[i] || chars) ? i++ : 0;
		if (!*s)
			break ;
	}
	tok[i] = NULL;
	return (tok);
}
