/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:44:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/31 00:09:07 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	escape_q_wild(char quote, int *dq, int *sq)
{
	if (quote == '"' && !*sq)
	{
		if (!*dq)
			*dq = 1;
		else
			*dq = 0;
	}
	else if (quote == '\'' && !*dq)
	{
		if (!*sq)
			*sq = 1;
		else
			*sq = 0;
	}
}

bool	check_pattern(char *s, char *p)
{
	char	*s_star;
	char	*p_star;

	(1) && (s_star = NULL, p_star = NULL);
	while (*s)
	{
		if (*p == '*')
			(1) && (p_star = p++, s_star = s);
		else if (*p == *s || (*p == '\f' && *s == '*'))
			(1) && (s++, p++);
		else if (p_star)
			(1) && (p = p_star + 1, s = ++s_star);
		else
			return (false);
	}
	while (*p == '*')
		p++;
	return (*p == '\0');
}

char	*prep_w(char *pattern)
{
	int		dq;
	int		sq;
	char	*out;

	dq = 0;
	sq = 0;
	out = NULL;
	while (pattern && *pattern)
	{
		if (*pattern == '\'' || *pattern == '"')
			escape_q_wild(*pattern, &dq, &sq);
		else if ((*pattern == '*') && (sq || dq))
			out = add_c(out, '\f', 0);
		else
			out = add_c(out, *pattern, 0);
		pattern++;
	}
	return (out);
}

char	*_wildcard_(char *pattern)
{
	struct dirent	*entry;
	char			*extracted;
	DIR				*dir;

	if (!pattern || !*pattern)
		return (NULL);
	(1) && (dir = opendir("."), extracted = NULL);
	if (!dir)
		return (perror("opendir"), NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (check_pattern(entry->d_name, pattern))
		{
			if (*(entry->d_name) == '.' && *pattern != '.')
				continue ;
			(extracted) && (extracted = ft_strjoin(extracted, "\a", 0), 0);
			extracted = ft_strjoin(extracted, entry->d_name, 0);
		}
	}
	(dir) && (closedir(dir));
	return (extracted);
}

//TODO cd ../current/*.c 