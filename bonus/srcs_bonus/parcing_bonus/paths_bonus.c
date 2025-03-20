/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:03:29 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/20 22:58:17 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

void	edit_paths(t_other *other, char **envp)
{
	t_ind	ind;

	find_path(other, envp);
	count_path(other);
	other->paths = malloc (sizeof(char *) * other->count_path);
	if (!other->paths)
		why_exit("other->paths allocation failed !", FAILED);
	ind.i = 5;
	ind.c = 0;
	ind.j = ind.i;
	while (other->all_path[ind.i])
	{
		while (other->all_path[ind.j] && other->all_path[ind.j] != ':')
			ind.j++;
		if (!other->all_path[ind.j] || other->all_path[ind.j] == ':')
			fill_path(other, ind);
		if (other->all_path[ind.j] == ':')
			ind.j ++;
		ind.i = ind.j;
		ind.c ++;
	}
	return ;
}

void	find_path(t_other *other, char	**envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A')
		{
			if (envp[i][2] == 'T' && envp[i][3] == 'H')
			{
				if (envp[i][4] == '=')
				{
					other->all_path = envp[i];
					return ;
				}
			}
		}
		i++;
	}
	return ;
}

void	count_path(t_other *other)
{
	t_ind	ind;

	ind.i = 5;
	other->count_path = 0;
	while (other->all_path[ind.i])
	{
		while (other->all_path[ind.i] && other->all_path[ind.i] != ':')
			ind.i ++;
		if (other->all_path[ind.i] == ':')
		{
			other->count_path ++;
			ind.i ++;
		}
		if (!other->all_path[ind.i])
			other->count_path ++;
	}
	return ;
}

void	fill_path(t_other *other, t_ind ind)
{
	int	a;

	a = 0;
	other->paths[ind.c] = malloc (sizeof(char) * (ind.j - ind.i) + 1);
	if (!other->paths[ind.c])
		free_all(NULL, other);
	while (ind.i < ind.j)
		other->paths[ind.c][a++] = other->all_path[ind.i++];
	other->paths[ind.c][a] = 0;
	return ;
}
