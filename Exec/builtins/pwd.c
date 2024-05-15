/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:51:05 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/15 04:32:23 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_pwd_(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
	_setenv("?", ft_itoa(0));
}
