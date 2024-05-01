/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:53:26 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/01 12:19:55 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_path(char *cmd)
{
	int		index;
	char	*path;
	char	*out;
	char	**path_v;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	index = -1;
	path = getenv("PATH");
	(!path) && (perror("PATH not found"), 0);
	path_v = ft_split(path, ":", 0);
	index = -1;
	while (path_v[++index])
	{
		out = ft_strjoin(path_v[index], "/", 0);
		out = ft_strjoin(out, cmd, 0);
		if (!access(out, X_OK))
			return (out);
	}
	return (NULL);
}

static bool	is_builtin(t_node *node)
{
	char *str;

	str = node->cmd[0];
	if (!ft_strcmp(str, "cd"))
		return (_cd_(node), true);
	else if (!ft_strcmp(str, "echo"))
		return (_echo_(node), true);
	else if (!ft_strcmp(str, "env"))
		return (_env_(node), true);
	else if (!ft_strcmp(str, "exit"))
		return (_exit_(node), true);
	else if (!ft_strcmp(str, "export"))
		return (_export_(node), true);
	else if (!ft_strcmp(str, "pwd"))
		return (_pwd_(node), true);
	else if (!ft_strcmp(str, "unset"))
		return (_unset_(node), true);
	return (false);
}

char	**env_p(t_env *env_raw)
{
	int		counter;
	int		index;
	char	**env_pv;
	t_env	*tmp_env;

	counter = 0;
	tmp_env = env_raw;
	while (env_raw)
	{
		counter++;
		env_raw = env_raw->next;
	}
	index = -1;
	env_pv = my_malloc(sizeof(char *) * (counter + 1),1 , 1);
	while (tmp_env)
	{
		env_pv[++index] = tmp_env->env;
		tmp_env = tmp_env->next;
	}
	return (env_pv);
}

void    _exec_(t_node *node)
{
	extern char	**environ;
    int			forked;
	int			fd_out;
	int			fd_in;

	fd_out = dup(STDOUT_FILENO);
	fd_in = dup(STDIN_FILENO);
	_expanding_(&node);
	if (_redirections_(&node) || is_builtin(node))
		return ;
    forked = fork();
    if (forked < 0)
	{
        perror("fork");
		exit(1);
	}
    if (!forked)
    {
		execve(add_path((node)->cmd[0]), (node)->cmd, environ);
		printf("bash: %s: Command not found bitch\n", (node)->cmd[0]);
		exit(1);
    }
	waitpid(forked, NULL, 0);
	if ((node)->fd[0] != 0)
	{
		close((node)->fd[0]);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);	
	}
	if ((node)->fd[1] != 1)
	{
		close((node)->fd[1]);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	_exec_arch_(t_node *node)
{
	t_token	tok;
	int		exit_stat;
	
	if (!node)
		return ;
	exit_stat = 1;
	tok = (node)->tok;
	if (tok == OR)
		_or_(node, exit_stat);
	else if (tok == AND)
		_and_(node, exit_stat);
	else if (tok == PIPE)
		_pipe_(node);
	else if (tok == NOT)
		_exec_(node);
	else
		perror("No token provided");
}