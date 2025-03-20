/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:03:29 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/20 22:27:53 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

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

int	check_file(t_cmd *tmp, t_cmd *cmd, t_other *other, int flag)
{
	if (flag == 0)
	{
		if (other->is_limiter == FALSE)
			other->open1 = open(other->infile, O_RDWR);
		else
			other->open1 = open(other->infile, O_RDWR | O_APPEND);
		if (other->open1 == -1)
		{
			close_fds(tmp->pipefd, -1);
			return (free_all(cmd, other), perror("open: "), exit(1), 1);
		}
		return (SUCCESSFUL);
	}
	check_file2(cmd, other, flag);
	return (SUCCESSFUL);
}

void	protect_it(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->opt = NULL;
	cmd->path_cmd = NULL;
	cmd->argument = NULL;
}
