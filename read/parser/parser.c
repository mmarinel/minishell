/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:26:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/01 16:16:59 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void			parser_initialize(t_parser_status *parser_status);

static t_tree_node	*parse_atomic_exp(t_parser_status *parser_status);
static t_tree_node	*parse_cmd_list(t_tree_node *current,
						t_parser_status *parser_status);
static t_tree_node	*parse_statement(t_token *token);

// * end of declarations //


t_tree_node	*parse(void)
{
	static t_parser_status	parser_status = (t_parser_status){
		OK, (t_groupings){0,0,0}, NULL
		};
	t_tree_node				*tree;

	tree = parse_cmd_list(parse_atomic_exp(&parser_status), &parser_status);
	if (parser_status.status == ERROR)
	{
		if (parser_status.last_read_token)
			printf("parser: parse error near"
				RED " %s " RESET " token at pos %d\n",
				tok_to_string(parser_status.last_read_token));
		free_tree(tree); // TODO esporre una funzionare di clean nel tokenizer per freeare la lista di token
		tree = NULL; // TODO mettere DENTRO free_tree
		parser_initialize(&parser_status);
	}
	tree_to_string(tree);
	printf ("\n");
	return (tree);
}

static t_tree_node	*parse_atomic_exp(t_parser_status *parser_status)
{
	t_token			*token;
	t_tree_node		*parenthesised;

	if (parser_status->status == ERROR)
		return (NULL);
	token = take_next_token(parser_status);//next_token();
	if (!token)
		return (NULL);
	if (
		token->token_id == e_OPERATOR
		||
		(
			token->token_id == e_PARENTHESIS
			&& *((char *)token->token_val) != '('
		)
	)
	{
		set_error(&(parser_status->status));
		return (NULL);
	}
	if (token->token_id == e_PARENTHESIS && *((char *)token->token_val) == '(')
	{
		parser_status->open.parenthesis += 1;
		parenthesised = parse_cmd_list(parse_atomic_exp(parser_status), parser_status);
		parenthesised->launch_subshell = e_true;
		return (parenthesised);
	}
	else
		return (parse_statement(token));
}

t_token	*take_next_token(t_parser_status *parser_status)
{
	t_token	*new_token;

	new_token = next_token();
	if (new_token)
		parser_status->last_read_token = new_token;
	return (new_token);
}

static t_tree_node	*parse_cmd_list(t_tree_node *current,
	t_parser_status *parser_status)
{
	t_token		*token;
	t_tree_node	*new_subtree;

	if (parser_status->status == ERROR)
		return (current);
	token = next_token();
	if (!token)
		return (current);
	if (token->token_id == e_PARENTHESIS && *((char *)token->token_val) == ')')
	{
		if (parser_status->open.parenthesis == 0)
			set_error(&(parser_status->status));
		else
			parser_status->open.parenthesis -= 1;
		return (current);
	}
	else if (token->token_id == e_OPERATOR)
	{
		new_subtree = parse_cmd_list(new_tree_node(current, parse_operator(token), e_false, parse_atomic_exp(parser_status)), parser_status);
		if (*((char *)token->token_val) == '|' && *((char *)token->token_val + 1) != '|')
			new_subtree->launch_subshell = e_true;
		else
			new_subtree->launch_subshell = e_false;
		return (new_subtree);
	}
	else
	{
		set_error(&(parser_status->status));
		return (current);
	}
}

static t_tree_node	*parse_statement(t_token *token)
{
	t_node_content	*node_content;

	node_content =  (t_node_content *) malloc(sizeof(t_node_content));
	node_content->in_redir.file_name = NULL;
	node_content->out_redir.file_name = NULL;
	while (token->token_id == e_IN_FILE_TRUNC || token->token_id == e_HERE_DOC
		|| token->token_id == e_OUT_FILE_TRUNC || token->token_id == e_OUT_FILE_APPEND)
	{
		parse_redir(node_content, token->token_val, token->token_id);
		token = next_token();
		if (!token)
		{
			node_content->content_type = REDIR;
			return (new_tree_node(NULL, node_content, e_false, NULL));
		}
	}
	if (token->token_id == e_CMD_NAME || token->token_id == e_CMD_ARG)
		return (new_tree_node(NULL, parse_simple_command(token, node_content), e_false, NULL));
	else if (token->token_id == e_ENV_VAR_DECL || token->token_id == e_ENV_VAR_UNSET)
		return (new_tree_node(NULL, parse_env_statement(token, node_content), e_false, NULL));
	ft_free(node_content->in_redir.file_name);
	ft_free(node_content->out_redir.file_name);
	free(node_content);
	return (NULL);
}

static void	parser_initialize(t_parser_status *parser_status)
{
	parser_status->last_read_token = NULL;
	parser_status->status = OK;
	parser_status->open.double_qquotes = 0;
	parser_status->open.quotes = 0;
	parser_status->open.parenthesis = 0;
}
