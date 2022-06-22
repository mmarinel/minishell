/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:13:30 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/22 10:06:39 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns.h"

int	scan_inout_file(char *str)
{
	t_token		*token;
	t_token_id	in_out_;
	size_t		len_file_name;
	char		*cursor;

	if (*str == '<')
		in_out_ = e_IN_FILE;
	else if (*str == '>')
		in_out_ = e_OUT_FILE;
	else
		return (-1);
	// REMOVING SPACES
	cursor = str;
	cursor += scan_spaces(cursor);
	cursor += scan_invariant_quotes(cursor);
	if (!(*cursor))
		return (-1);
	// TAKING FILE NAME
	len_file_name = 0;
	while (e_false == bash_control_character(cursor[len_file_name])
		&& cursor[len_file_name])
		len_file_name++;
	if (len_file_name == 0)
		return (-1);
	// TOKEN RECOGNIZED !
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = in_out_;
	token->token_val = ft_strcpy(NULL, cursor, len_file_name);
	lexer(token, e_STORE_NXT_TOK);
	return ((ft_strlen(str) - ft_strlen(cursor)) + len_file_name);
}

/**
 * @brief ASF to recognize &&, ||, | only
 * 
 * @param str 
 * @return int 
 */
int	scan_operator(char *str)
{
	t_token	*token;
	char	*cursor;

	if (!str)
		return (-1);
	cursor = str;
	cursor += scan_spaces(cursor);
	cursor += scan_invariant_quotes(cursor);
	if (*cursor = '|' || *cursor != '&')
		return (-1);
	if (*cursor == '&' && *(cursor + 1) != '&')
		return (-1);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = e_OPERATOR;
	if (*cursor == '&')
		token->token_val = "&&";
	if (*cursor == '|' && *cursor != '|')
		token->token_val = "|";
	else
		token->token_val = "||";
	lexer(token, e_STORE_NXT_TOK);
	return ((ft_strlen(str) - ft_strlen(cursor)) + ft_strlen((char *)token->token_val));
}

int	scan_cmd_name(char *str)
{
	t_token	*token;
	int		len_cmd_name;
	char	*cursor;

	cursor =  str;
	cursor += scan_spaces(cursor);
	cursor += scan_invariant_quotes(cursor);
	if (!(*cursor))
		return (-1);
	len_cmd_name = 0;
	while (e_false == ft_isspace(cursor[len_cmd_name])
		&& e_false == bash_control_character(cursor[len_cmd_name]))
		len_cmd_name++;
	if (len_cmd_name == 0)
		return (-1);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = e_CMD_NAME;
	token->token_val = ft_strcpy(NULL, cursor, len_cmd_name);
	lexer(token, e_STORE_NXT_TOK);
	return ((ft_strlen(str) - ft_strlen(cursor)) + len_cmd_name);
}

int	scan_cmd_arg(char *str)
{
	t_token	*token;
	int		len_cmd_arg;
	char	*cursor;

	cursor = str;
	cursor += scan_spaces(cursor);
	cursor += scan_invariant_quotes(cursor);
	if (!(*cursor))
		return (-1);
	len_cmd_arg = 0;
	while (e_false == bash_control_character(cursor[len_cmd_arg]))
		len_cmd_arg++;
	if (len_cmd_arg == 0)
		return (-1);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = e_CMD_ARG;
	token->token_val = ft_strcpy(NULL, cursor, len_cmd_arg);
	lexer(token, e_STORE_NXT_TOK);
	return ((ft_strlen(str) - ft_strlen(cursor)) + len_cmd_arg);
}

int	scan_parenthesis(char *str)
{
	t_token	*token;
	char	*cursor;

	cursor = str;
	cursor += scan_spaces(cursor);
	if (*cursor != '(' && *cursor != ')')
		return (-1);
	token = (t_token *) malloc(sizeof(t_token));
	if (*cursor == '(')
		token->token_val = "(";
	else
		token->token_val = ")";
	lexer(token, e_STORE_NEXT_TOK);
	return ((ft_strlen(str) - ft_strlen(cursor)) + 1);
}
