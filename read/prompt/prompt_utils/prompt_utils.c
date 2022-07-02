/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:00:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/02 09:42:07 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_utils.h"

void	here_doc_read_current(char *delimiter, char *handle_name);
size_t	here_docs_count(char *command);
char	**here_doc_take_delimiters(char *command);

t_bool	here_doc_line(char *command)
{
	return (here_docs_count(command) > 0);
	// return (here_doc_take_delimiter(command) != NULL);
}

void	here_doc_read(char *command)
{
	char	*cur_file_name;
	char	**here_doc_delims;
	size_t	here_docs;
	size_t	i;

	here_docs = here_docs_count(command);
	printf("There are %zu here_docs\n", here_docs);
	here_doc_delims =  here_doc_take_delimiters(command);
	i = 0;
	while (i < here_docs)
	{
		printf("delim is: %s\n", here_doc_delims[i]);
		cur_file_name = ft_strjoin(".here_doc-", ft_itoa(i), e_false, e_true);
		printf("file_name is: %s\n", cur_file_name);
		here_doc_read_current(here_doc_delims[i], cur_file_name);
		free(cur_file_name);
		i++;
	}
}

void	here_doc_read_current(char *delimiter, char *handle_name)
{
	int		fd_here_document;
	char	*next_line;
	int		delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	fd_here_document = open(handle_name, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (-1 == fd_here_document)
		exit_shell(EXIT_FAILURE, e_false);
	while (e_true)
	{
		write(STDOUT_FILENO, "heredoc> ",
			ft_strlen("heredoc> ") * sizeof(char));
		next_line = get_next_line(STDIN_FILENO, 1);
		if (!ft_strncmp(delimiter, next_line, delimiter_len))
			break ;
		else
		{
			write(fd_here_document, next_line, ft_strlen(next_line));
			free(next_line);
		}
	}
	free(next_line);
	close(fd_here_document);
}

// void	here_doc_read(char *delimiter)
// {
// 	int		fd_here_document;
// 	char	*next_line;
// 	char	*here_doc;
// 	int		delimiter_len;

// 	here_doc = ".here_doc";
// 	delimiter_len = ft_strlen(delimiter);
// 	fd_here_document = open(here_doc, O_CREAT | O_RDWR | O_APPEND, 0777);
// 	if (-1 == fd_here_document)
// 		exit_shell(EXIT_FAILURE, e_false);
// 	while (e_true)
// 	{
// 		write(STDOUT_FILENO, "heredoc> ",
// 			ft_strlen("heredoc> ") * sizeof(char));
// 		next_line = get_next_line(STDIN_FILENO, 1);
// 		if (!ft_strncmp(delimiter, next_line, delimiter_len))
// 			break ;
// 		else
// 		{
// 			write(fd_here_document, next_line, ft_strlen(next_line));
// 			free(next_line);
// 		}
// 	}
// 	free(next_line);
// 	close(fd_here_document);
// }

size_t	here_docs_count(char *command)
{
	size_t	i;
	size_t	here_docs;

	here_docs = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '<' && command[i + 1] == '<' && command[i + 2] == '<')
			return (0);
		if (command[i] == '<' && command[i + 1] == '<' && command[i + 2] != '<')
			here_docs++;
		i++;
	}
	return (here_docs);
}

char	**here_doc_take_delimiters(char *command)
{
	size_t	i;
	size_t	j;
	size_t	here_docs;
	char	**here_docs_file_names;

	here_docs = here_docs_count(command);
	if (here_docs == 0)
	{
		printf("HGHGHJGHJGHJGHJGHJGHJ");
		return (NULL);
	}
	here_docs_file_names = (char **) malloc((here_docs + 1) * sizeof(char *));
	here_docs_file_names[here_docs] = NULL;
	j = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '<' && command[i + 1] == '<')
		{
			i += 2;
			while (e_true == ft_isspace(command[i]))
				i++;
			here_docs_file_names[j] = take_next_word(command + i);
			j++;
		}
		else
			i++;
	}
	return (here_docs_file_names);
}

// char	*here_doc_take_delimiter(char *command)
// {
// 	char	*start;

// 	start = take_substr(command, "<<");
// 	if (!start)
// 		return (NULL);
// 	start += 2;
// 	while (ft_isspace(*start))
// 		start++;
// 	return (take_next_word(start));
// }

/**
 * @brief this function adds 'command' to the history of commands 
 * iff it's not an empty string or already present.
 * 
 * @param command a quote balanced command string
 * @return char** the address of the last stored entry in the history.
 */
char	**ft_add_history(char *command)
{
	static char	*last = NULL;

	if (command)
	{
		if (str_not_empty(command)
			&& (!last || ft_strncmp(command, last, ft_strlen(last)))
		)
		{
			add_history(command);
			ft_free(last);
			last = NULL;
			last = ft_strcpy(last, command, ft_strlen(command));
		}
	}
	return (&last);
}
