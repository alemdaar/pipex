/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:15:10 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/25 03:15:41 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

static void	free_tmp(t_cmd *tmp)
{
	t_ind	ind;

	if (tmp->cmd)
	{
		free(tmp->cmd);
		tmp->cmd = NULL;
	}
	if (tmp->opt)
	{
		free(tmp->opt);
		tmp->opt = NULL;
	}
	if (tmp->path_cmd)
	{
		free(tmp->path_cmd);
		tmp->path_cmd = NULL;
	}
	if (tmp->argument)
	{
		ind.i = 0;
		while (tmp->argument[ind.i] && ind.i < tmp->ar)
			free(tmp->argument[ind.i++]);
		free(tmp->argument);
		tmp->argument = NULL;
	}
}

static void	free_paths(t_other *other)
{
	t_ind	ind;

	ind.i = 0;
	while (other->paths[ind.i] && ind.i < other->count_path)
	{
		free(other->paths[ind.i]);
		other->paths[ind.i++] = NULL;
	}
	free(other->paths);
	other->paths = NULL;
}

void	free_all(t_cmd **cmd, t_other *other)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	if (other->paths)
		free_paths(other);
	if (!cmd || !*cmd)
		return ;
	tmp = *cmd;
	while (tmp)
	{
		tmp2 = tmp->next;
		free_tmp(tmp);
		free (tmp);
		tmp = tmp2;
	}
	return ;
}
