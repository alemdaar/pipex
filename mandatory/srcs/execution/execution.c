/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:03:38 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/24 17:32:09 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	exec(t_cmd *cmd, t_cmd *tmp, t_other *other)
{
	while (1);
	if (tmp->path_cmd == NULL)
	{
		free_all(&cmd, other);
		myputstr ("Error: command not found\n", 2);
		exit(1);
	}
	if (execve(tmp->path_cmd, tmp->argument, NULL) == ERROR)
	{
		free_all(&cmd, other);
		perror ("execve: ");
		exit(1);
	}
	return (SUCCESSFUL);
}

static int	pipping(t_cmd *cmd, t_other *other)
{
	t_ind	ind;

	ind.r = pipe(other->pipefd);
	if (ind.r == -1)
	{
		free_all(&cmd, other);
		why_exit("Error: pipe failed\n", FAILED);
	}
	return (SUCCESSFUL);
}

static int	dupping(t_cmd *tmp, t_other *other, int position)
{
	t_ind	ind;

	if (position == 0 && tmp->next != NULL)
	{
		ind.r = dup2(other->open1, 0);
		if (ind.r == -1)
			return (close_fds(other->pipefd, other->open1), ERROR);
		ind.r = dup2(other->pipefd[WRITE], 1);
		if (ind.r == -1)
			return (close_fds(other->pipefd, other->open1), ERROR);
		close_fds(other->pipefd, other->open1);
		return (SUCCESSFUL);
	}
	ind.r = dup2(other->pipefd[READ], 0);
	if (ind.r == -1)
		return (close_fds(other->pipefd, other->open2), ERROR);
	ind.r = dup2(other->open2, 1);
	if (ind.r == -1)
		return (close_fds(other->pipefd, other->open2), ERROR);
	close_fds(other->pipefd, other->open2);
	return (SUCCESSFUL);
}

static int	child_process(t_cmd *cmd, t_cmd *tmp, t_other *other, int position)
{
	t_ind	ind;

	ind.r = 0;
	ind.r = check_file(cmd, other, position);
	if (ind.r == -1)
		return (perror("open: "), exit(1), 1);
	ind.r = dupping(tmp, other, position);
	if (ind.r == -1)
	{
		free_all(&cmd, other);
		return (perror("Error dup2: "), exit(1), 1);
	}
	exec(cmd, tmp, other);
	exit(1);
}

int	execution(t_cmd *cmd, t_other *other)
{
	t_cmd	*tmp;

	tmp = cmd;
	pipping(cmd, other);
	tmp->pid = fork();
	if (tmp->pid == -1)
	{
		free_all(&cmd, other);
		why_exit("Error: fork failed\n", FAILED);
	}
	if (tmp->pid == 0)
		child_process(cmd, tmp, other, 0);
	while (1);
	tmp = tmp->next;
	tmp->pid = fork();
	if (tmp->pid == -1)
	{
		free_all(&cmd, other);
		why_exit("Error: fork failed\n", FAILED);
	}
	if (tmp->pid == 0)
		child_process(cmd, tmp, other, 1);
	close_fds(other->pipefd, -1);
	wait(NULL);
	wait(NULL);
	return (SUCCESSFUL);
}
