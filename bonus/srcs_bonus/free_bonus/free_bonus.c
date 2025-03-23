/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:15:10 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/22 17:36:28 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

static void	free_all2(t_cmd *tmp, t_ind *ind)
{
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
		ind->i = 0;
		while (tmp->argument[ind->i] && ind->i < tmp->ar)
			free(tmp->argument[ind->i++]);
		free(tmp->argument);
	}
}

void	free_all(t_cmd *cmd, t_other *other)
{
	t_ind	ind;
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		cmd = cmd->next;
		free_all2(tmp, &ind);
		free (tmp);
		tmp = NULL;
		tmp = cmd;
	}
	if (other->paths)
	{
		ind.i = 0;
		while (other->paths[ind.i] && ind.i < other->count_path)
			free(other->paths[ind.i++]);
		free(other->paths);
	}
	return ;
}
