/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:44:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/20 03:20:40 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool check_pattern(char *str, char *pattern)
{
    if (!*pattern)
        return (!*str);
	if (*pattern == '*')
		return ((check_pattern(str, pattern + 1) ||
		(*str && check_pattern(str + 1, pattern))));
   else if (*str == *pattern)
        return check_pattern(str + 1, pattern + 1);
    return (false);
}

//checking the path .
//check the quotes
int	check_wildcard(char *str)
{
	int		inside_q;
	char	*pattern;
	char	*back_str;
	int		index;
	char	q;

	inside_q = 0;
	index = -1;
	back_str = str;
	pattern = my_malloc(ft_strlen(str), 1);
	while (*str)
	{
		if (*str == '\'' && *(str + 1) == '\'')
			str += 2;
		else if (*str == '"' && *(str + 1) == '"')
			str += 2;
		else
			pattern[++index] = *str++;
	}
	*str = 0;
	str = back_str;
	printf("this is str %s\n", pattern);
	if (find_c(pattern, '"') || find_c(pattern, '\''))
		return (0);
	return (1);
}
// int main()
// {
//     // if (check_pattern("quoe", "*q*ye"))
//     //     printf("YEpA\n");
// 	char pattern[] = "*.c\"das\"";
	
//     printf("%d\n", check_wildcard(pattern));
// }

// char	*_wildcard_(char *pattern)
// {
//     struct dirent   *entry;
//     char            *extracted;
//     DIR             *dir;

//     dir = opendir(".");
//     if (!dir)
//     {
//         perror("opendir");
//         return (NULL);
//     }
//     extracted = NULL;
//     while (1)
//     {
//         entry = readdir(dir);
//         if (!entry)
//             break;
//         if (check_pattern(entry->d_name, pattern))
//         {
//             if (extracted)
//                 extracted = ft_strjoin(extracted, "\t");
//             extracted = ft_strjoin(extracted, entry->d_name);
//         }
//     }
// 	return (extracted);
// }

