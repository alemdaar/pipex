/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:00:40 by macbookair        #+#    #+#             */
/*   Updated: 2025/03/21 00:23:29 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

static int	open_here_doc(t_other *other)
{
	other->open1 = open(other->infile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (other->open1 == -1)
	{
		perror("open: ");
		exit(FAILED);
	}
	return (SUCCESSFUL);
}

int	is_limiter(char *line, char *limiter)
{
	t_ind	ind;

	ind.i = 0;
	while (limiter[ind.i] && limiter[ind.i] == line[ind.i])
		ind.i ++;
	if (limiter[ind.i] == 0 && line[ind.i] == '\n')
		return (TRUE);
	return (FALSE);
}

int	make_heredoc(t_other *other)
{
	char	*line;
	t_ind	ind;

	open_here_doc(other);
	ind.c = 0;
	while (1)
	{
		myputstr("pipe heredoc> ", 1);
		line = get_next_line(0);
		if (line == NULL && ind.c == 0)
		{
			close(other->open1);
			unlink(other->infile);
			return (myputstr("gnl failed\n", 2), 1);
		}
		if (line == NULL && ind.c == 1)
			break ;
		ind.c = 1;
		if (is_limiter(line, other->limiter) == TRUE)
			return (free(line), SUCCESSFUL);
		write (other->open1, line, mystrlen(line));
	}
	if (line)
		free(line);
	return (close(other->open1), other->open1 = -1, SUCCESSFUL);
}
