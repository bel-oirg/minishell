/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:42:10 by abennar           #+#    #+#             */
/*   Updated: 2024/05/04 18:33:08 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_tree(t_node *root, int level)
// {
//     if (root != NULL) {
//         print_tree(root->right, level + 1);
//         for (int i = 0; i < level; i++) {
//             printf("   ");
//         }
// 		if (root->tok == NOT)
//         	printf("%s\n", root->cmd[0]);
// 		else
// 			print_tok(root->tok);
//         print_tree(root->left, level + 1);
//     }
// }

t_node	*parsing(char *line)
{
	t_node	*node;
	char	*cmd;
	
	node = NULL;
	cmd = ft_strtrim(line, SEP, 0);
	free(line);
	if (!cmd || !cmd[0])
		return (NULL);
	node = lexer(cmd);
	if (!node)
		return (NULL);
	lst_iter(node, get_args);
	node = infix_to_postfix(&node);
	node = postfix_to_prefix(node);
	node = tree(node);
	return (node);
}