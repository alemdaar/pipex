#include "../../header.h"

int parcing(t_cmd *cmd, char **av, char **envp)
{
	edit_paths(cmd, envp);
	cmd->cmd = malloc (sizeof(char *) * 2);
	if (!cmd->cmd)
		return (free_all(cmd), why_exit("cmd->cmd failed\n", FAILED), FAILED);
	cmd->opt = malloc (sizeof(char *) * 2);
	if (!cmd->opt)
		return (free_all(cmd), why_exit("cmd->cmd failed\n", FAILED), FAILED);
	edit_cmd(cmd, av);
	free_all(cmd);
	// exec(av);
	return (SUCCESSFUL);
}

void	edit_paths(t_cmd *cmd, char **envp)
{
	t_ind ind;

	find_path(cmd, envp);
	count_path(cmd);
	cmd->paths = malloc (sizeof(char *) * cmd->count_path);
	if (!cmd->paths)
		why_exit("cmd->paths allocation failed !", FAILED);
	zerod_2(&cmd->paths, cmd->count_path);
	ind.i = 5;
	ind.c = 0;
	ind.j = ind.i;
	while (cmd->all_path[ind.i])
	{
		while (cmd->all_path[ind.j] && cmd->all_path[ind.j] != ':')
			ind.j++;
		if (!cmd->all_path[ind.j] || cmd->all_path[ind.j] == ':')
		{
			fill_path(cmd, ind);
			printf ("pat : %s\n", cmd->paths[ind.c]);
		}
		if (cmd->all_path[ind.j] == ':')
			ind.j ++;
		ind.i = ind.j;
		ind.c ++;
	}
	return ;
}

void	find_path(t_cmd *cmd, char	**envp)
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
					cmd->all_path = envp[i];
			}
		}
		i++;
	}
	return ;
}

void count_path(t_cmd *cmd)
{
	t_ind ind;

	ind.i = 5;
	cmd->count_path = 0;
	while (cmd->all_path[ind.i])
	{
		while (cmd->all_path[ind.i] && cmd->all_path[ind.i] != ':')
			ind.i ++;
		if (cmd->all_path[ind.i] == ':')
		{
			cmd->count_path ++;
			ind.i ++;
		}
		if (!cmd->all_path[ind.i])
			cmd->count_path ++;
	}
	return ;
}

void	fill_path(t_cmd *cmd, t_ind ind)
{
	int	a;

	a = 0;
	cmd->paths[ind.c] = malloc (sizeof(char) * (ind.j - ind.i) + 1);
	if (!cmd->paths[ind.c])
		free_all(cmd);
	zerod_1(&cmd->paths[ind.c], ind.j - ind.i);
	while (ind.i < ind.j)
		cmd->paths[ind.c][a++] = cmd->all_path[ind.i++];
	cmd->paths[ind.c][a] = 0;
	printf ("str : %s\n", cmd->paths[ind.c]);
}

int edit_cmd(t_cmd *cmd, char **av)
{
	fill_cmd(av[2], cmd, 0);
	fill_cmd(av[2], cmd, 1);
	fill_opt(av[3], cmd, 0);
	fill_opt(av[3], cmd, 1);
	check_cmd(cmd);
}

int	fill_cmd(char *input, t_cmd *cmd, int flag)
{
	t_ind ind;

	ind.i = 0;
	while (input[ind.i] && input[ind.i] != ' ')
		ind.i++;
	cmd->cmd[flag] = malloc (sizeof(char) * ind.i + 1);
	if (!cmd->cmd[flag])
		return (free_all(cmd), why_exit("some command not alloacted\n", FAILED), FAILED);
	ind.j = 0;
	while (ind.j < ind.i)
	{
		cmd->cmd[flag][ind.j] = input[ind.j];
		ind.j++;
	}
	cmd->cmd[flag][ind.j] = 0;
	return (SUCCESSFUL);
}

int	fill_opt(char *input, t_cmd *cmd, int flag)
{
	int	i;
	int	j;

	i = 0;
	while (input[i] && input[i] != ' ')
		i++;
	while (input[i] && input[i] == ' ')
		i++;
	if (!input[i])
		return (cmd->opt[flag] = NULL, FAILED);
	cmd->opt[flag] = malloc (sizeof(char) * i + 1);
	if (!cmd->opt[flag])
		return (free_all(cmd), why_exit("some option not alloacted\n", FAILED), FAILED);
	j = 0;
	while (j < i)
	{
		cmd->opt[flag][j] = input[j];
		j++;
	}
	cmd->opt[flag][j] = 0;
	return (SUCCESSFUL);
}

int check_cmd(t_cmd *cmd)
{
	t_ind ind;

	ind.i = 0;
	ind.c = FALSE;
	while (ind.i < cmd->count_path)
	{
		// hna
		ind.c = check_access(cmd->paths[ind.i], cmd->cmd);
		if (ind.c == TRUE)
			break;
		ind.i ++;
	}
	if (ind.c == FALSE)
		return (free_all(cmd), why_exit("command not found\n", FAILED), FAILED);
	return (SUCCESSFUL);
}

int	check_access(char *path, char **cmd)
{
	char *full_path;
	int	i;

	full_path = mixem(path, cmd);
	if (!full_path)
		return (free(cmd) ,why_exit("full path failed allocation\n", FAILED), FAILED);
	i = 0;
	if (access(full_path, F_OK) == SUCCESSFUL)
	{
		if (access(full_path, X_OK) == SUCCESSFUL)
			return (free(full_path), SUCCESSFUL);
	}
	return (free(full_path), FAILED);
}

// int exec(char **av)
// {
// 	int		pipefd[2];
// 	int		r_pipe;
// 	pid_t	pid;

// 	r_pipe = pipe(pipefd);
// 	if (r_pipe == ERROR)
// 		why_exit("pipe function failed \n", FAILED);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(OUTPUT, pipefd[INPUT]);
// 		if (execve("/bin/ls", args, NULL) == -1) {
//         perror("execve failed");
//         return 1;
//     }
// 		return (SUCCESSFUL);
// 	}

// }

// ft_exec()
// {
// 	pipe()
// 	fork()
// 	if (child)
// 	{
// 		dup2()
// 		execve()
// 	}
// 	else
// 	{
// 		close()
// 	}
// }