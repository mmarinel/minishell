/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_module.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:23:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/19 17:10:45 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_MODULE_H
# define PRINT_MODULE_H

//* user defined types
# include "print_types.h"
# include "../types.h"


//* user defined exposed functions
void	put_error(char *preamble, char *message, char *epilogue,
			t_bool free_epilogue);
void	redirector(t_stdout_to_dump opcode);
char	*get_stdout_dump_file_name(void);
size_t	printer(t_print_opcode opcode);

#endif