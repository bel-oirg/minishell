/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:29:18 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/12 16:34:27 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_b_expanding_(t_node **node)
{
	char **cmd;
	int	index;

	(*node)->cmd = cmd;
	index = -1;
	while (cmd[++index])
	{
		
	}
}

void	_expanding_(t_node **node, t_env *env)
{
	t_env	*tmp_env;
	int		index;
	
	tmp_env = env;
	while((*node)->cmd)
	{
		index = -1;
		while((*node)->cmd[++index])
		{
			if ((*node)->cmd[index][0] == '$')
			{
				if (!ft_strcmp((*node)->cmd[index], "$?"))
					exit_stat();
				env = tmp_env;
				while (ft_strcmp(&((*node)->cmd[index][1]), env->var))
					env = env->next;
				if (env)
					(*node)->cmd[index] = ft_strdup(env->value);
				else
					(*node)->cmd[index] = ft_strdup("");
			}
		}
		*node = (*node)->rchild;
	}
}
