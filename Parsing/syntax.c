/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:50:12 by abennar           #+#    #+#             */
/*   Updated: 2024/05/31 00:16:54 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	get_next_token(char *cmd, int i)
{
	skip_space(cmd, &i);
	if ((cmd[i] == '"') || (cmd[i] == '\''))
		i += skip_quotes((cmd + i + 1), cmd[i]);
	return (get_token(cmd[i], cmd[i + 1]));
}

static bool	is_redir(t_token tok)
{
	return (tok == IN || tok == OUT || tok == HEREDOC || tok == APPEND);
}

static bool	par_check(char *cmd, t_token tok, int i)
{
	t_token	t_tok;
	int		j;

	j = i;
	t_tok = get_next_token(cmd, i);
	if (tok == RPR)
	{
		if (t_tok == NOT || is_redir(t_tok) || i < 2)
			return (put_tok_err(tok));
		return (true);
	}
	if (!(t_tok == NOT || t_tok == LPR || is_redir(t_tok)))
		return (put_tok_err(t_tok));
	while (cmd[i])
	{
		t_tok = get_token(cmd[i], cmd[i + 1]);
		if (t_tok == RPR)
			return (true);
		i++;
	}
	t_tok = get_next_token(cmd, j);
	return (put_tok_err(t_tok));
}

static bool	redir_check(char *cmd, int i)
{
	t_token	n;

	n = get_next_token(cmd, i);
	if (n != NOT)
		return (put_tok_err(n));
	return (true);
}

bool	check_syntax(t_token tok, char *cmd, int i)
{
	t_token	n;

	(cmd[i] != '"' && cmd[i] != '\'') && (++i);
	(tok == HEREDOC || tok == OR || tok == APPEND || tok == AND) && (i++);
	if (tok == LPR || tok == RPR)
		return (par_check(cmd, tok, i));
	else if (tok == AND || tok == OR || tok == PIPE)
	{
		n = get_next_token(cmd, i);
		if (!(n == NOT || is_redir(n) || n == LPR) || (tok == PIPE
				&& (i < 2 || n == LPR)) || (tok != PIPE && i < 3) || n == END)
		{
			if ((tok == PIPE && i < 2) || (tok != PIPE && i < 3))
				return (put_tok_err(tok));
			else
				return (put_tok_err(n));
		}
	}
	else if (tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
		return (redir_check(cmd, i));
	else if (tok == NOT)
		if (get_next_token(cmd, i) == LPR)
			return (put_tok_err(LPR));
	return (true);
}
