/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:09:32 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/16 20:01:33 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	is_awk(char *cmd)
{
	if (cmd[0] == 'a' && cmd[1] == 'w')
	{
		if (cmd[2] == 'k' && cmd[3] == 0)
			return (TRUE);
	}
	return (FALSE);
}

static int	awk_arg3(t_cmd *tmp, t_ind *ind)
{
	ind->c ++;
	while (tmp->opt[ind->c] && tmp->opt[ind->c] != 39)
		ind->c ++;
	if (tmp->opt[ind->c] == 39)
		ind->c ++;
	return (SUCCESSFUL);
}

static int	awk_arg2(t_cmd *tmp, t_ind *ind)
{
	ind->t = 0;
	while (tmp->opt[ind->j] && tmp->opt[ind->j] == ' ')
		ind->j ++;
	ind->c = ind->j;
	if (tmp->opt[ind->c] == 39 && tmp->opt[ind->c - 1] != 92)
		awk_arg3(tmp, ind);
	else
	{
		while (tmp->opt[ind->c] && tmp->opt[ind->c] != ' ')
			ind->c ++;
	}
	tmp->argument[ind->i] = malloc ((ind->c - ind->j) + 1);
	if (!tmp->argument[ind->i])
		return (myputstr("tmp->arg[] (awk) failed \n", 2), ERROR);
	while (tmp->opt[ind->j] && ind->j < ind->c)
	{
		if (tmp->opt[ind->j] == 39 && tmp->opt[ind->j - 1] != 92)
			ind->j ++;
		else
			tmp->argument[ind->i][ind->t++] = tmp->opt[ind->j++];
	}
	return (tmp->argument[ind->i++][ind->t] = 0, 0);
}

static int	count_awk_opt(char *opt)
{
	t_ind	ind;

	ind.i = 0;
	ind.c = TRUE;
	ind.r = 0;
	if (opt == NULL)
		return (ind.r);
	while (opt[ind.i])
	{
		if (opt[ind.i] != ' ' && opt[ind.i] != 39 && ind.c == TRUE)
		{
			ind.c = FALSE;
			ind.r ++;
		}
		else if (opt[ind.i] == ' ' && ind.c == FALSE)
			ind.c = TRUE;
		else if (opt[ind.i] == 39)
		{
			ind.r ++;
			return (ind.r);
		}
		ind.i ++;
	}
	return (ind.r);
}

int	awk_arg(t_cmd **cmd, t_other *other)
{
	t_ind	ind;
	t_cmd	*tmp;

	tmp = *cmd;
	ind.i = 0;
	ind.j = 0;
	tmp->ar = count_awk_opt(tmp->opt) + 1;
	tmp->argument = malloc (sizeof(char *) * (tmp->ar + 1));
	if (!tmp->argument)
		return (myputstr("argument failed !\n", 2), ERROR);
	tmp->argument[ind.i] = malloc (mystrlen(tmp->cmd) + 1);
	if (!tmp->argument[ind.i])
		return (myputstr("tmp->argument[ind.i] allocation failed\n", 2), ERROR);
	ind.f = 0;
	ind.t = 0;
	while (tmp->cmd[ind.f])
		tmp->argument[ind.i][ind.t++] = tmp->cmd[ind.f++];
	ind.i ++;
	if (tmp->opt == NULL)
		return (tmp->argument[ind.i] = NULL, SUCCESSFUL);
	while (ind.i < tmp->ar)
		awk_arg2(tmp, &ind);
	return (tmp->argument[ind.i] = NULL, 0);
}
