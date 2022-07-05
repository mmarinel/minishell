/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 07:51:39 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 12:03:25 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../includes.h"
# include "../read/prompt/prompt_module.h"

void	sig_handler(int signum);
void	shell_executor_handler(int signum);
void	line_completion_prompt_sig_handler(int signum);

#endif
