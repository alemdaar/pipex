#include "../../header.h"

int parcing(t_cmd *cmd, char **av, char **envp)
{
	edit_paths(&cmd, envp);
	cmd->cmd = fill_cmd(av[1]);
	check_cmd(av[2], &cmd);
	check_cmd(av[3], &cmd);
	exec(av);
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
	while (cmd->all_path[ind.i])
	{
		ind.j = ind.i;
		while (cmd->all_path[ind.j] && cmd->all_path[ind.j] != ':')
			ind.j++;
		if (!cmd->all_path[ind.j] || cmd->all_path[ind.j] == ':')
			fill_path(cmd, ind.i, ind.j, ind.c);
		ind.i = ind.j;
		ind.c ++;
	}
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

	ind.i = 0;
	while (cmd->all_path[ind.i])
	{
		ind.j = ind.i;
		while (cmd->all_path[ind.j] && cmd->all_path[ind.j] != ':')
			ind.j++;
		if (!cmd->all_path[ind.j] || cmd->all_path[ind.j] == ':')
			cmd->count_path ++;
		ind.i = ind.j;
	}
	return ;
}

void	fill_path(t_cmd *cmd, int a, int z, int turn)
{
	t_ind ind;

	ind.i = 0;
	cmd->paths[turn] = malloc (sizeof(char) * (z - a));
	if (!cmd->paths[turn])
		free_all();
	zerod_1(cmd->paths[turn]);
	while ()
	{
		
	}
	

}

int check_cmd(char *input, t_cmd *cmd)
{
	if (check_access("/bin/", actual_cmd) == SUCCESSFUL)
		return (free(actual_cmd), SUCCESSFUL);
	if (check_access("/sbin/", actual_cmd) == SUCCESSFUL)
		return (free(actual_cmd), SUCCESSFUL);
	if (check_access("/usr/bin/", actual_cmd) == SUCCESSFUL)
		return (free(actual_cmd), SUCCESSFUL);
	if (check_access("/usr/sbin/", actual_cmd) == SUCCESSFUL)
		return (free(actual_cmd), SUCCESSFUL);
	if (check_access("/usr/local/bin/", actual_cmd) == SUCCESSFUL)
		return (free(actual_cmd), SUCCESSFUL);
	return (free(actual_cmd), why_exit("command not found\n", FAILED), FAILED);
}

int	check_access(char *path, char *cmd)
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

char *fill_cmd(char *cmd)
{
	char *actual_cmd;
	int	i;
	int	j;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	actual_cmd = malloc (sizeof(char) * i + 1);
	if (!actual_cmd)
		why_exit("actual cmd not alloacted\n", FAILED);
	j = 0;
	while (j < i)
	{
		actual_cmd[j] = cmd[j];
		j++;
	}
	actual_cmd[j] = 0;
	return (actual_cmd);
}

int exec(char **av)
{
	int		pipefd[2];
	int		r_pipe;
	pid_t	pid;

	r_pipe = pipe(pipefd);
	if (r_pipe == ERROR)
		why_exit("pipe function failed \n", FAILED);
	pid = fork();
	if (pid == 0)
	{
		dup2(OUTPUT, pipefd[INPUT]);
		if (execve("/bin/ls", args, NULL) == -1) {
        perror("execve failed");
        return 1;
    }
		return (SUCCESSFUL);
	}

}

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