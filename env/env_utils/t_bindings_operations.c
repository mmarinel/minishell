/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_bindings_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:42:44 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 15:34:19 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"

void	binding_add_new(t_bindings **head, t_bindings *new_binding,
			t_bool in_order)
{
	t_bindings	*cursor;

	if (!(*head))
		binding_add_front(head, new_binding);
	else if (in_order == e_false)
		binding_add_back(head, new_binding);
	else
		binding_add_in_order(head, new_binding);
}

/**
 * @brief this function tries to modify the value of an existing environment variable
 * 
 * @return pointer to the over-written binding, or a NULL pointer if no such variable exist in the environment
 */
t_bindings	*binding_over_write(t_bindings *head, t_bindings *binding)
{
	t_bindings	*cursor;

	cursor = head;
	while (cursor)
	{
		if (ft_strcmp(cursor->var_name, binding->var_name) == 0)
		{
			if (binding->concat_mode == e_true)
				cursor->var_val = ft_strjoin(cursor->var_val, binding->var_val, e_true, e_false);
			else
				ft_str_replace(&(cursor->var_val), binding->var_val);
			return (cursor);
		}
		cursor = cursor->next;
	}
	return (NULL);
}

void	binding_remove(t_bindings **head, char *var_name)
{
	t_bindings	*cur_binding;

	cur_binding = *head;
	while (cur_binding)
	{
		if (0 == ft_strcmp(cur_binding->var_name, var_name))
			break ;
		cur_binding = cur_binding->next;
	}
	if (!cur_binding)
		return ;
	{
		if (cur_binding->prev)
			cur_binding->prev->next = cur_binding->next;
		else
			*head = (*head)->next;
	}
	if (cur_binding->next)
	{
		cur_binding->next->prev = cur_binding->prev;
	}
	free(cur_binding->var_name);
	free(cur_binding->var_val);
	free(cur_binding);
}

/**
 * @brief this function returns the current value for the environment variable 'name'
 * 
 * @param head the head of the environment list
 * @param name the name to search
 * @return char* (always malloc-ed !) if variable is defined, its value is returned, otherwise an empty string is returned
 */
char	*binding_get_value(t_bindings *head, char *name)
{
	t_bindings	*cursor;

	cursor = head;
	while (cursor)
	{
		if (0 == ft_strcmp(cursor->var_name, name))
			return (
				ft_strcpy(NULL, cursor->var_val,
					ft_strlen(cursor->var_val))
			);
		cursor = cursor->next;
	}
	return (ft_strcpy(NULL, "", sizeof(char)));
}