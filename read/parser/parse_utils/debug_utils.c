/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 12:02:01 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/05 18:01:32 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

void	print_operator(t_tree_node *node)
{
	if (node->content->operator_node.operator == e_PIPE)
		printf(" | ");
	if (node->content->operator_node.operator == e_OR)
		printf(" || ");
	if (node->content->operator_node.operator == e_AND)
		printf(" && ");
}

void	print_simple_command(t_tree_node *node)
{
	printf(GREEN "[cmd_name: %s, cmd_arg: %s, infile: %s, outfile: %s]" RESET, node->content->simple_cmd.cmd_name, node->content->simple_cmd.cmd_args, node->content->in_redir.file_name, node->content->out_redir.file_name);
}

void	print_env_statement(t_tree_node *node)
{
	// t_bindings	*binding;

	if (node->content->env_decl.set)
		printf(GREEN "[EXPORT : infile: %s, outfile: %s " RESET, node->content->in_redir.file_name, node->content->out_redir.file_name);
	else
		printf(GREEN "[UNSET : infile: %s, outfile: %s " RESET, node->content->in_redir.file_name, node->content->out_redir.file_name);
	// binding = node->content->env_decl.bindings;
	// while (binding)
	// {
	// 	printf("\tconcat: %d, var_name: %s, var_val: %s\t", binding->concat_mode, binding->var_name, binding->var_val);
	// 	binding = binding->next;
	// }
	// printf("]");
}

static void	tree_to_string_rec(t_tree_node *subtree_root, size_t space);

void	tree_to_string(t_tree_node *root)
{
	int		cur_stdout_backup;

	cur_stdout_backup = dup(STDOUT_FILENO);
	dup2(g_env.stdout_clone, STDOUT_FILENO);
	ft_printf("\n");
	tree_to_string_rec(root, 0);
	dup2(cur_stdout_backup, STDOUT_FILENO);
	close(cur_stdout_backup);
}

static void	tree_to_string_rec(t_tree_node *subtree_root, size_t spaces)
{
	size_t	i;

	if (subtree_root)
	{
		tree_to_string_rec(subtree_root->right, spaces + 1);
		i = 0;
		while (i < spaces)
		{
			ft_printf("\t");
			i++;
		}
		if (subtree_root->content->content_type == REDIR)
			ft_printf("REDIR_ONLY ");
		else if (subtree_root->content->content_type == SIMPL_CMD)
		{
			ft_printf("(cmd: %s; args: %s)", subtree_root->content->simple_cmd.cmd_name, subtree_root->content->simple_cmd.cmd_args); //print_simple_command(root);
		}
		else if (subtree_root->content->content_type == ENV_STATEMENT)
		{
			if (subtree_root->content->env_decl.set)
				ft_printf("SET ENV_STATEMENT "); //print_env_statement(root);
			else
				ft_printf("UNSET ENV_STATEMENT "); //print_env_statement(root);
		}
		else if (subtree_root->content->content_type == PAREN_EXP)
		{
			ft_printf("PAREN\n\n");
			tree_to_string_rec(subtree_root->content->parenthesis_node.subtree, spaces + 1);
		}
		else
		{
			if(subtree_root->content->operator_node.operator == e_PIPE)
				ft_printf("|");
			else if (subtree_root->content->operator_node.operator == e_OR)
				ft_printf("||");
			else if (subtree_root->content->operator_node.operator == e_AND)
				ft_printf("&&");
		}
		ft_printf("\n\n");
		tree_to_string_rec(subtree_root->left, spaces + 1);
	}
}
