/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:13:15 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/25 03:26:29 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

int	parcing(t_cmd **cmd, char **av, t_other *other)
{
	t_ind	ind;
	t_cmd	*tmp;

	ind.i = set_parcing(other);
	tmp = *cmd;
	while (ind.i < other->ac - 1)
	{
		tmp = ft_lstnew();
		if (!tmp)
			return (free_all(cmd, other), why_exit("node failed !\n", 1), 1);
		protect_it(tmp);
		ft_lstadd_back(cmd, tmp);
		ind.f = edit_cmd(tmp, av, ind.i);
		if (ind.f == ERROR)
			return (free_all(cmd, other), exit(1), 1);
		ind.c = check_cmd(tmp, other);
		if (ind.c == ERROR)
			return (free_all(cmd, other), exit(1), 1);
		ind.r = fill_argument(&tmp);
		if (ind.r == ERROR)
			return (free_all(cmd, other), exit(1), 1);
		tmp = tmp->next;
		ind.i ++;
	}
	return (SUCCESSFUL);
}

int	edit_cmd(t_cmd *cmd, char **av, int flag)
{
	t_ind	ind;

	ind.r = 0;
	fill_cmd(av[flag], cmd, &ind);
	if (ind.r == ERROR)
		return (ERROR);
	cmd->ar = 1;
	ind.f = fill_opt(av[flag], cmd, ind.r);
	if (ind.f == ERROR)
		return (ERROR);
	return (SUCCESSFUL);
}

int	check_cmd(t_cmd *cmd, t_other *other)
{
	t_ind	ind;

	ind.i = 0;
	ind.c = FALSE;
	while (ind.i < other->count_path)
	{
		ind.c = check_access(cmd, other, ind.i);
		if (ind.c == TRUE)
			break ;
		else if (ind.c == ERROR)
			return (ERROR);
		ind.i ++;
	}
	if (ind.c == FALSE)
	{
		ind.c = check_access(cmd, other, -1);
		if (ind.c == FALSE)
			return (cmd->path_cmd = NULL, FAILED);
	}
	return (SUCCESSFUL);
}

int	fill_argument2(t_cmd *tmp, t_ind *ind)
{
	ind->t = 0;
	while (tmp->cmd[ind->f])
		tmp->argument[ind->i][ind->t++] = tmp->cmd[ind->f++];
	ind->i ++;
	if (tmp->opt == NULL)
		return (tmp->argument[ind->i] = NULL, SUCCESSFUL);
	while (ind->i < tmp->ar)
	{
		ind->t = 0;
		while (tmp->opt[ind->j] == ' ')
			ind->j ++;
		ind->c = ind->j;
		while (tmp->opt[ind->c] && tmp->opt[ind->c] != ' ')
			ind->c ++;
		tmp->argument[ind->i] = malloc ((ind->c - ind->j) + 1);
		if (!tmp->argument[ind->i])
			return (myputstr("tmp->arg[] failed\n", 2), ERROR);
		while (tmp->opt[ind->j] && ind->j < ind->c)
			tmp->argument[ind->i][ind->t++] = tmp->opt[ind->j++];
		tmp->argument[ind->i][ind->t] = 0;
		ind->i ++;
	}
	return (SUCCESSFUL);
}

int	fill_argument(t_cmd **cmd)
{
	t_ind	ind;
	t_cmd	*tmp;

	tmp = *cmd;
	ind.i = 0;
	ind.j = 0;
	ind.f = 0;
	if (is_awk(tmp->cmd) == TRUE)
	{
		ind.r = awk_arg(cmd);
		if (ind.r == ERROR)
			return (ERROR);
		return (SUCCESSFUL);
	}
	tmp->argument = malloc (sizeof(char *) * (tmp->ar + 1));
	if (!tmp->argument)
		return (myputstr("argument failed !\n", 2), ERROR);
	tmp->argument[ind.i] = malloc (mystrlen(tmp->cmd) + 1);
	if (!tmp->argument[ind.i])
		return (myputstr("tmp->argument[ind.i] allocation failed\n", 2), ERROR);
	ind.r = fill_argument2(tmp, &ind);
	if (ind.r == ERROR)
		return (ERROR);
	tmp->argument[ind.i] = NULL;
	return (SUCCESSFUL);
}
