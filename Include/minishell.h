/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:16:16 by abennar           #+#    #+#             */
/*   Updated: 2024/04/23 20:22:43 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // printf
#include <unistd.h> //write - close - fork - dup2 - chdir
#include <stdlib.h> //malloc 
#include <stdbool.h> //true && false
#include <limits.h> //INT_MAX
#include <fcntl.h> //open
#include <dirent.h> //opendir
#include <readline/readline.h> // readline
#include <readline/history.h> // readline history
#include "prottypes.h"

//quotes
char	*d_q(char *raw, int *index);
char	*s_q(char *raw, int *index);
char	*add_c(char *str, char c);

//builtins -> env
int		find_c(char *str, char c);

//utils ---------
char	**ft_split(char *s, char *delim, int group);
char	*ft_strtrim(const char *s1, const char *set, int group);
char	*ft_strjoin(char *s1, char *s2, int group);
char 	*get_next_word(char *str, int *i, t_token tok);
void	get_args(t_node *node);
void	*my_malloc(size_t size, int mode, int group);
void	add_env(t_node *node, t_env *env);

//utils ->mng_cmd
t_token	get_token(const char c1, const char c2);
int		skip_quotes(char *s, char c);
int		get_cmd_area(char *s, int start);

//utils ->ft_is
int is_it_in(t_env *raw_env, char *new_var);
int	is_alphanum(char c);

//utils -> ft_str
char	*ft_strdup(char *s, int group);
int		ft_strlen(const char *s);
char	*ft_substr( char *str, unsigned int start, size_t len, int group);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

//utils -> link_lst
t_redir	*new_redir(char *file, t_token tok);
t_node	*new_node(char *cmd, t_redir *redir, t_token tok, int pre);
void	add_redir_back(t_redir *node, t_redir **list);
void	add_node_back(t_node *node, t_node **list);
void	add_redir_back(t_redir *node, t_redir **list);

void	print_tok(t_token tok); //just tmp
//--------------

//parsing
void	Parsing(char *line, t_env *env);
bool	low_pre(t_token tok);
void	lst_iter(t_node	*lst, void (*f)(t_node *));

// env init
t_env	*env_init(char **envp);


//algo
t_node	*infix_to_postfix(t_node **lst);
t_node	*postfix_to_prefix(t_node *node);

//algo_utils
void	top_push(t_node **src, t_node **dest);
void	back_push(t_node **src, t_node **dest);

//tree
t_node	*tree(t_node	*node);

//lexer
t_node	*lexer(char *cmd);
