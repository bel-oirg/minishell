/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:32:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/15 04:32:04 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	_env_(void)
{
	extern char	**environ;
	char		**tmp;

	tmp = environ;
	while (*tmp)
	{
		if (ft_strchr(*tmp, '=') && **tmp != '?')
			printf("%s\n", *tmp);
		tmp++;
	}
	_setenv("?", ft_itoa(0));
}
