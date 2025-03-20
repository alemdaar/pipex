/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:30:43 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/20 22:09:51 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

int	dupping2(t_cmd *tmp, t_other *other, int position)
{
	t_ind	ind;

	if (position != 0 && tmp->next != NULL)
	{
		ind.r = dup2(other->prev_read, 0);
		if (ind.r == -1)
			return (close_fds(tmp->pipefd, other->prev_read), ERROR);
		ind.r = dup2(tmp->pipefd[WRITE], 1);
		if (ind.r == -1)
			return (close_fds(tmp->pipefd, other->prev_read), ERROR);
		close_fds(tmp->pipefd, other->prev_read);
	}
	else
	{
		ind.r = dup2(other->prev_read, 0);
		if (ind.r == -1)
			return (close(other->prev_read), close(other->open2), ERROR);
		ind.r = dup2(other->open2, 1);
		if (ind.r == -1)
			return (close(other->prev_read), close(other->open2), ERROR);
		close(other->prev_read);
		close(other->open2);
	}
	return (SUCCESSFUL);
}

int	execution2(t_cmd *tmp, t_cmd *cmd, t_other *other, int i)
{
	if (tmp->pid == -1)
	{
		free_all(cmd, other);
		why_exit("Error: fork failed\n", FAILED);
	}
	if (tmp->pid == 0)
		child_process(tmp, cmd, other, i);
	if (i != 0)
		close(other->prev_read);
	if (tmp->next)
	{
		close(tmp->pipefd[WRITE]);
		other->prev_read = tmp->pipefd[READ];
	}
	return (SUCCESSFUL);
}
