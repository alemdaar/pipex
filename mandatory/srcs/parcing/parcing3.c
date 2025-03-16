/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:31:08 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/16 20:01:58 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	fill_cmd(char *input, t_cmd *cmd, t_ind *rtn)
{
	t_ind	ind;

	ind.i = 0;
	while (input[ind.i] && input[ind.i] == ' ')
		ind.i++;
	while (input[ind.i] && input[ind.i] != ' ')
		ind.i++;
	ind.r = ind.i;
	cmd->cmd = malloc (sizeof(char) * ind.i + 1);
	if (!cmd->cmd)
	{
		rtn->r = -1;
		return (myputstr("command not alloacted\n", 2), ERROR);
	}
	ind.j = 0;
	while (ind.j < ind.i)
	{
		cmd->cmd[ind.j] = input[ind.j];
		ind.j++;
	}
	cmd->cmd[ind.j] = 0;
	rtn->r = ind.r;
	return (SUCCESSFUL);
}

static int	fill_opt2(char *input, t_cmd *cmd, t_ind *ind)
{
	if (input[ind->t] != ' ' && ind->r == FALSE)
	{
		cmd->ar ++;
		ind->r = TRUE;
	}
	if (input[ind->t] == ' ')
		ind->r = FALSE;
	ind->t ++;
	ind->c ++;
	return (SUCCESSFUL);
}

int	fill_opt(char *input, t_cmd *cmd, int pos)
{
	t_ind	ind;

	ind.i = 0;
	ind.c = 0;
	ind.r = FALSE;
	while (input[pos] && input[pos] == ' ')
		pos++;
	if (!input[pos])
		return (cmd->opt = NULL, SUCCESSFUL);
	ind.t = pos;
	while (input[ind.t])
		fill_opt2(input, cmd, &ind);
	cmd->opt = malloc (sizeof(char) * ind.c + 1);
	if (!cmd->opt)
		return (myputstr("some option not alloacted\n", 2), ERROR);
	ind.j = 0;
	while (ind.j < ind.c)
		cmd->opt[ind.j++] = input[pos++];
	cmd->opt[ind.j] = 0;
	return (SUCCESSFUL);
}

int	check_access(t_cmd *cmd, t_other *other, int path_ind)
{
	cmd->path_cmd = mixem(cmd, other, path_ind);
	if (!cmd->path_cmd)
		return (myputstr("full path failed allocation\n", STD_ERR), ERROR);
	if (access(cmd->path_cmd, F_OK) == SUCCESSFUL)
	{
		if (access(cmd->path_cmd, X_OK) == SUCCESSFUL)
			return (TRUE);
	}
	return (free(cmd->path_cmd), cmd->path_cmd = NULL, FALSE);
}
