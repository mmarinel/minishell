/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_opt_err_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:28:28 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/07 19:35:44 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"

void	put_env_opt_err(void)
{
	put_error_message(
		"minishell at execute_env: ", "Illegal arguments or option found",
		NULL, e_false
	);
}
