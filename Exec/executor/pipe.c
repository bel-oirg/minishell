/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:57:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/31 23:46:16 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rbuddha(t_node *node, int *piped)
{
	int		forked;

	forked = fork();
	if (forked < 0)
	{
		perror("pipe");
		return (-1);
	}
	if (!forked)
	{
		close(piped[1]);
		if (dup2(piped[0], STDIN_FILENO) < 0)
		{
			close(piped[0]);
			exit(1);
		}
		close(piped[0]);
		_exec_arch_(node);
		exit(ft_atoll(getenv("?"), NULL));
	}
	return (forked);
}

int	lbuddha(t_node *node, int *piped)
{
	int	forked;

	forked = fork();
	if (forked < 0)
	{
		perror("pipe");
		return (-1);
	}
	if (!forked)
	{
		close(piped[0]);
		if (dup2(piped[1], STDOUT_FILENO) < 0)
		{
			close(piped[1]);
			exit(1);
		}
		_exec_arch_(node);
		exit(ft_atoll(getenv("?"), NULL));
	}
	return (forked);
}

void	_pipe_(t_node *node)
{
	pid_t		pid[2];
	int			piped[2];
	int			child_exit;

	if (pipe(piped) < 0)
		return ;
	pid[0] = lbuddha(node->left, piped);
	if (pid[0] < 0)
	{
		(1) && (close(piped[0]), close(piped[1]));
		return ;
	}
	pid[1] = rbuddha(node->right, piped);
	if (pid[1] < 0)
	{
		(1) && (close(piped[0]), close(piped[1]));
		return ;
	}
	close(piped[0]);
	close(piped[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &child_exit, 0);
	_setenv("?", ft_itoa(WEXITSTATUS(child_exit)));
}
