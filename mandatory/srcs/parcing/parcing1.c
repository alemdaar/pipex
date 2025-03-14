/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:13:15 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/14 22:06:09 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void protect_it(t_cmd *cmd)
{
    cmd->cmd = NULL;
    cmd->opt = NULL;
    cmd->path_cmd = NULL;
    cmd->argument = NULL;
}

int parcing(t_cmd **cmd, char **av, t_other *other)
{
	t_ind ind;
	t_cmd *tmp;

	ind.i = 2;
	tmp = *cmd;
	while (ind.i < other->ac - 1)
	{
		tmp = ft_lstnew();
		if (!tmp)
			return (why_exit("node allocation failed !\n", FAILED), FAILED);
		protect_it(tmp);
		ft_lstadd_back(cmd, tmp);
		ind.f = edit_cmd(tmp, av, ind.i);
		if (ind.f == ERROR)
			return (free_all(*cmd, other), exit(1), 1);
		ind.c = check_cmd(tmp, other);
		if (ind.c == ERROR)
			return (free_all(*cmd, other), exit(1), 1);
		ind.r = fill_argument(&tmp);
		if (ind.r == ERROR)
			return (free_all(*cmd, other), exit(1), 1);
		tmp = tmp->next;
		ind.i ++;
	}
	return (SUCCESSFUL);
}

void	edit_paths(t_other *other, char **envp)
{
	t_ind ind;

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
	int i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A')
		{
			if (envp[i][2] == 'T' && envp[i][3] == 'H')
			{
				if (envp[i][4] == '=')
					other->all_path = envp[i];
			}
		}
		i++;
	}
	return ;
}

void count_path(t_other *other)
{
	t_ind ind;

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
}

int edit_cmd(t_cmd *cmd, char **av, int flag)
{
	t_ind ind;

	fill_cmd(av[flag], cmd, &ind);
	if (ind.r == ERROR)
		return (ERROR);
	cmd->ar = 1;
	ind.f = fill_opt(av[flag], cmd, ind.r);
	if (ind.f == ERROR)
		return (ERROR);
	return (SUCCESSFUL);
}

int	fill_cmd(char *input, t_cmd *cmd, t_ind *rtn)
{
	t_ind ind;

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
		return (printf("command not alloacted\n"), ERROR);
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

int	fill_opt(char *input, t_cmd *cmd, int pos)
{
	t_ind ind;

	ind.i = 0;
	ind.c = 0;
	ind.r = FALSE;
	while (input[pos] && input[pos] == ' ')
		pos++;
	if (!input[pos])
		return (cmd->opt = NULL, SUCCESSFUL);
	ind.t = pos;
	while (input[ind.t])
	{
		if (input[ind.t] != ' ' && ind.r == FALSE)
		{
			cmd->ar ++;
			ind.r = TRUE;
		}
		if (input[ind.t] == ' ')
			ind.r = FALSE;
		ind.t ++;
		ind.c ++;
	}
	cmd->opt = malloc (sizeof(char) * ind.c + 1);
	if (!cmd->opt)
		return (printf("some option not alloacted\n"), ERROR);
	ind.j = 0;
	while (ind.j < ind.c)
		cmd->opt[ind.j++] = input[pos++];
	cmd->opt[ind.j] = 0;
	return (SUCCESSFUL);
}

int check_cmd(t_cmd *cmd, t_other *other)
{
	t_ind ind;
	ind.i = 0;
	ind.c = FALSE;
	while (ind.i < other->count_path)
	{
		ind.c = check_access(cmd, other, ind.i);
		if (ind.c == TRUE)
			break;
		else if (ind.c == ERROR)
			return (ERROR);
		ind.i ++;
	}
	if (ind.c == FALSE)
		return (cmd->path_cmd = NULL, FAILED);
	return (SUCCESSFUL);
}

int	check_access(t_cmd *cmd, t_other *other, int path_ind)
{
	int	i;
	cmd->path_cmd = mixem(cmd, other, path_ind);
	if (!cmd->path_cmd)
		return (myputstr("full path failed allocation\n"), ERROR);
	i = 0;
	if (access(cmd->path_cmd, F_OK) == SUCCESSFUL)
	{
		if (access(cmd->path_cmd, X_OK) == SUCCESSFUL)
			return (TRUE);
	}
	return (free(cmd->path_cmd), cmd->path_cmd = NULL, FALSE);
}

// int check_file(char **av, t_cmd *cmd, int flag)
// {
// 	if (flag == 2)
// 	{
// 		cmd->file = open(av[1], O_RDWR);
// 		if (cmd->file == -1)
// 		{
// 			perror("Error: ");
// 			myputstr(av[1]);
// 			myputstr("\n");
// 		}
// 	}
// 	else if (flag == 3)
// 	{
// 		cmd->file = open(av[4], O_CREAT | O_RDWR, 0644);
// 		if (cmd->file == -1)
// 		{
// 			perror("ERROR: ");
// 			myputstr(av[1]);
// 			myputstr("\n");
// 		}
// 	}
// 	return (SUCCESSFUL);
// }

int fill_argument(t_cmd **cmd)
{
	t_ind ind;
	t_cmd *tmp;

	tmp = *cmd;
	ind.i = 0;
	ind.j = 0;
	ind.f = 0;
	if (is_awk(tmp->cmd) ==  TRUE)
	{
		ind.r = awk_arg(cmd);
		if (ind.r == ERROR)
			return (ERROR);
		return (SUCCESSFUL);
	}
	tmp->argument = malloc (sizeof(char *) * (tmp->ar + 1));
	if (!tmp->argument)
		return (myputstr("argument failed !\n"), ERROR);
	tmp->argument[ind.i] = malloc (mystrlen(tmp->cmd) + 1);
	if (!tmp->argument[ind.i])
		return (myputstr("tmp->argument[ind.i] allocation failed\n"), ERROR);
	ind.t = 0;
	while (tmp->cmd[ind.f])
		tmp->argument[ind.i][ind.t++] = tmp->cmd[ind.f++];
	ind.i ++;
	if (tmp->opt == NULL)
		return (tmp->argument[ind.i] = NULL, SUCCESSFUL);
	while (ind.i < tmp->ar)
	{
		ind.t = 0;
		while (tmp->opt[ind.j] == ' ')
			ind.j ++;
		ind.c = ind.j;
		while (tmp->opt[ind.c] && tmp->opt[ind.c] != ' ')
			ind.c ++;
		tmp->argument[ind.i] = malloc ((ind.c - ind.j) + 2);
		if (!tmp->argument[ind.i])
			return (myputstr("tmp->arg[] failed\n"), ERROR);
		while (tmp->opt[ind.j] && ind.j < ind.c)
			tmp->argument[ind.i][ind.t++] = tmp->opt[ind.j++];
		tmp->argument[ind.i][ind.t] = 0;
		ind.i ++;
	}
	tmp->argument[ind.i] = NULL;
	return (SUCCESSFUL);
}

int is_awk(char *cmd)
{
	if (cmd[0] == 'a' && cmd[1] == 'w')
	{
		if (cmd[2] == 'k' && cmd[3] == 0)
			return (TRUE);
	}
	return (FALSE);
}

int awk_arg(t_cmd **cmd)
{
	t_ind ind;
	t_cmd *tmp;

	tmp = *cmd;
	ind.i = 0;
	ind.j = 0;
	tmp->ar = count_awk_opt(tmp->opt) + 1;
	tmp->argument = malloc (sizeof(char *) * (tmp->ar + 1));
	if (!tmp->argument)
		return (myputstr("argument failed !\n"), ERROR);
	tmp->argument[ind.i] = malloc (mystrlen(tmp->cmd) + 1);
	if (!tmp->argument[ind.i])
		return (myputstr("tmp->argument[ind.i] allocation failed\n"), ERROR);
	ind.f = 0;
	ind.t = 0;
	while (tmp->cmd[ind.f])
		tmp->argument[ind.i][ind.t++] = tmp->cmd[ind.f++];
	ind.i ++;
	if (tmp->opt == NULL)
		return (tmp->argument[ind.i] = NULL, SUCCESSFUL);
	
	while (ind.i < tmp->ar)
	{
		ind.t = 0;
		while (tmp->opt[ind.j] && tmp->opt[ind.j] == ' ')
			ind.j ++;
		ind.c = ind.j;
		if (tmp->opt[ind.c] == 39)
		{
			ind.c ++;
			while (tmp->opt[ind.c])
				ind.c ++;
			if (tmp->opt[ind.c] == 39)
				ind.c ++;
		}
		else
		{
			while (tmp->opt[ind.c] && tmp->opt[ind.c] != ' ')
				ind.c ++;
		}
		tmp->argument[ind.i] = malloc ((ind.c - ind.j) + 2);
		if (!tmp->argument[ind.i])
			return (myputstr("tmp->arg[] (awk) failed \n"), ERROR);
		while (tmp->opt[ind.j] && ind.j < ind.c)
			tmp->argument[ind.i][ind.t++] = tmp->opt[ind.j++];
		tmp->argument[ind.i][ind.t] = 0;
		ind.i ++;
	}
	tmp->argument[ind.i] = NULL;
	return (SUCCESSFUL);
}

int count_awk_opt(char *opt)
{
	t_ind ind;

	ind.i = 0;
	ind.c = TRUE;
	ind.r = 0;
	if (opt == NULL)
		return (ind.r);
	printf ("str : %s\n", opt);
	// -F,    '   {   print    1 } '
	while (opt[ind.i])
	{
		if (opt[ind.i] != ' ' &&  opt[ind.i] != 39 && ind.c == TRUE) // normal
		{
			printf ("normal\n");
			ind.c = FALSE;
			ind.r ++;
		}
		else if (opt[ind.i] == ' ' && ind.c == FALSE) // space
		{
			printf ("space\n");
			ind.c = TRUE;
		}
		else if (opt[ind.i] == 39) // single quote
		{
			printf ("single quote\n");
			ind.r ++;
			return (ind.r);
		}
		ind.i ++;	
	}
	return (ind.r);
}

// ft_exec()
// {
	// 	pipe()
	// 	pid = fork()
	// 	if (pid == -1)
	// 	{
	// 	}
	// 	if (!pid)
	// 	{

	// 		dup2()
	// 		execve()
	// 	}
	// 	else
	// 	{
	// 		close()
	// 	}
// }
