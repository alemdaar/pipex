/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:03:29 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/25 17:50:25 by macbookair       ###   ########.fr       */
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
	int		len;

	len = mystrlen(other->paths[path_ind]) + mystrlen(cmd->cmd);
	if (other->all_path == NULL || path_ind == -1)
		str = malloc (mystrlen(cmd->cmd) + 1);
	else
		str = malloc (len + 2);
	if (!other->all_path && path_ind != -1)
		return (NULL);
	i = 0;
	j = 0;
	if (path_ind != -1)
	{
		while (other->paths[path_ind][j])
			str[i++] = other->paths[path_ind][j++];
		j = 0;
		str[i++] = '/';
	}
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
			free_all(&cmd, other);
			close_fds(other->pipefd, -1);
			perror("open: ");
			exit(FAILED);
		}
		return (SUCCESSFUL);
	}
	other->open2 = open (other->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (other->open2 == -1)
	{
		free_all(&cmd, other);
		close_fds(other->pipefd, -1);
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
