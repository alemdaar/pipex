#include "../../header.h"

int	exec(t_cmd *tmp, t_cmd *cmd, t_other *other)
{
    if (tmp->cmd == NULL)
    {
        perror ("Error: command not found\n");
        exit(1);
    }
	if (execve(tmp->path_cmd, tmp->argument, NULL) == ERROR)
    {
        free_all(cmd, other);
        exit(1);
    }
    return (SUCCESSFUL);
}

int pipping(t_cmd *cmd, t_other *other)
{
	t_ind ind;

	ind.r = pipe(other->pipefd);
	if (ind.r == -1)
	{
		free_all(cmd, other);
		why_exit("Error: pipe failed\n", FAILED);
	}
    return (SUCCESSFUL);
}

int check_file(t_cmd *cmd, t_other *other, int flag)
{
	if (flag == 0)
	{
		other->open1 = open (other->infile, O_RDWR);
		if (other->open1 == -1)
		{
			free_all(cmd, other);
			perror("open: ");
			exit(FAILED);
		}
		return (SUCCESSFUL);
	}
	other->open2 = open (other->outfile, O_RDWR | O_CREAT, 0644);
	if (other->open2 == -1)
	{
		free_all(cmd, other);
		perror("open: ");
		exit(FAILED);
	}
	return (SUCCESSFUL);
}

int dupping(t_cmd *tmp, t_cmd *cmd, t_other *other, int position)
{
    t_ind ind;

    dprintf(other->debug, "hna\n");
    if (position == 0 && tmp->next != NULL)
    {
        dprintf(other->debug, "hna1\n");
        ind.r = dup2(other->open1, 0);
        if (ind.r == -1)
        {
            free_all(cmd, other);
            perror("dup21: ");
            exit(FAILED);
        }
        ind.r = dup2(other->pipefd[1], 1);
        if (ind.r == -1)
        {
            free_all(cmd, other);
            perror("dup22: ");
            exit(FAILED);
        }
        close (other->pipefd[0]);
        close (other->pipefd[1]);
	    close(other->open1);
        return (SUCCESSFUL);
    }
    dprintf(other->debug, "hna\n");
    ind.r = dup2(other->pipefd[0], 0);
    if (ind.r == -1)
    {
        free_all(cmd, other);
        perror("dup23: ");
        exit(FAILED);
    }
    ind.r = dup2(other->open2, 1);
    if (ind.r == -1)
    {
        free_all(cmd, other);
        perror("dup24: ");
        exit(FAILED);
    }
    close (other->pipefd[0]);
    close (other->pipefd[1]);
    close(other->open2);
    return (SUCCESSFUL);
}
int child_process(t_cmd *tmp, t_cmd *cmd, t_other *other, int position)
{
    check_file(cmd, other, position);
    dupping(tmp, cmd, other, position);
    exec(tmp, cmd, other);
    exit(1);
}

int execution(t_cmd *cmd, t_other *other)
{
    t_cmd *tmp;
    
	tmp = cmd;
	pipping(cmd, other);
    tmp->pid = fork();
    if (tmp->pid == -1)
    {
        free_all(cmd, other);
        why_exit("Error: fork failed\n", FAILED);
    }
    if (tmp->pid == 0)
    {
        child_process(tmp, cmd, other, 0);
        exit(1);
    }
    tmp = tmp->next;
    tmp->pid = fork();
    if (tmp->pid == -1)
    {
        free_all(cmd, other);
        why_exit("Error: fork failed\n", FAILED);
    }
    if (tmp->pid == 0)
    {
        child_process(tmp, cmd, other, 1);
        exit(1);
    }
    close (other->pipefd[0]);
	close (other->pipefd[1]);
	wait(NULL);
	wait(NULL);
	close(other->open1);
	close(other->open2);
    return (SUCCESSFUL);
}