/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:36:08 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/22 09:43:33 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

int	scan_alternate_invariant_spaces_quotes(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		// READING ALL INVARIANT QUOTES
		while (str[idx] == '"' || str[idx] == '\'')
		{
			if (str[idx + 1] != str[idx])
				break ;
			idx += 2;
		}
		// READING ALL FINAL SPACES
		while (str[idx])
		{
			if (e_false == ft_isspace(str[idx]))
				break ;
			idx++;
		}
		if (str[idx] != '"' && str[idx] != '\''
			&& e_false == ft_isspace(str[idx]))
			break ;
	}
	return (idx);
}

/**
 * @brief this function adds the given token to the end of the current list of tokens
 * 
 * @param tokens the address of the first element in the list or NULL if the list is not empty
 * @param token the next token to store
 */
void	tok_add_back(t_token **tokens, t_token *token)
{
	static	t_token	*tail;

	if (tokens)
	{
		*tokens = token;
		tail = *tokens;
		tail->prev = NULL;
	}
	else
	{
		tail->next = token;
		tail->next->prev = tail;
		tail = tail->next;
		tail->next = NULL;
	}
	
}
// int	scan_env_var(char *str)
// {
// 	char	*cursor;

// 	if (!str)
// 		return (-1);
// 	cursor = str;
// 	cursor += scan_spaces(cursor);
// 	cursor += scan_invariant_quotes(cursor);
// 	if (!cursor || ft_strncmp(cursor, "export", 6 * sizeof(char)))
// 		return (-1);
// 	return ((ft_strlen(str) - ft_strlen(cursor)) + scan_var(cursor + 6, e_ENV_VAR_ASSIGN));
// }
