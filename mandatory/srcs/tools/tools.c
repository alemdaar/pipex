/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:03:29 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/17 21:01:47 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	mystrlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*mixem(t_cmd *cmd, t_other *other, int path_ind)
{
	char	*str;
	int		i;
	int		j;

	str = malloc (mystrlen(other->paths[path_ind]) + mystrlen(cmd->cmd) + 2);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (other->paths[path_ind][j])
		str[i++] = other->paths[path_ind][j++];
	j = 0;
	str[i++] = '/';
	while (cmd->cmd[j])
		str[i++] = cmd->cmd[j++];
	str[i] = 0;
	return (str);
}

int	close_fds(int fds[2], int file)
{
	close(fds[READ]);
	close(fds[WRITE]);
	if (file != -1)
		close(file);
	return (SUCCESSFUL);
}

int	check_file(t_cmd *cmd, t_other *other, int flag)
{
	if (flag == 0)
	{
		other->open1 = open (other->infile, O_RDONLY);
		if (other->open1 == -1)
		{
			close_fds(other->pipefd, -1);
			free_all(cmd, other);
			perror("open: ");
			exit(FAILED);
		}
		return (SUCCESSFUL);
	}
	other->open2 = open (other->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (other->open2 == -1)
	{
		close_fds(other->pipefd, -1);
		free_all(cmd, other);
		perror("open: ");
		exit(FAILED);
	}
	return (SUCCESSFUL);
}

void	protect_it(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->opt = NULL;
	cmd->path_cmd = NULL;
	cmd->argument = NULL;
}
