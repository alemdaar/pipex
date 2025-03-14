#include "header.h"

void leak()
{
    system("leaks -q pipex");
}

int	exec(t_cmd *tmp, t_cmd *cmd, t_other *other)
{
	if (execve(tmp->path_cmd, tmp->argument, NULL) == ERROR)
    {
        free_all(cmd, other);
	    why_exit ("execve failed\n", FAILED);
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
            perror("dup2: ");
            exit(FAILED);
        }
        ind.r = dup2(other->pipefd[1], 1);
        if (ind.r == -1)
        {
            free_all(cmd, other);
            perror("dup2: ");
            exit(FAILED);
        }
        return (SUCCESSFUL);
    }
    dprintf(other->debug, "hna\n");
    ind.r = dup2(other->pipefd[0], 0);
    if (ind.r == -1)
    {
        free_all(cmd, other);
        perror("dup2: ");
        exit(FAILED);
    }
    ind.r = dup2(other->open2, 1);
    if (ind.r == -1)
    {
        free_all(cmd, other);
        perror("dup2: ");
        exit(FAILED);
    }
    return (SUCCESSFUL);
}
int child_process(t_cmd *tmp, t_cmd *cmd, t_other *other, int position)
{
    check_file(cmd, other, 1);
    dupping(tmp, cmd, other, position);
    exec(tmp, cmd, other);
    exit(1);
}

int execution(t_cmd *cmd, t_other *other)
{
	t_cmd *tmp;
	t_ind ind;

	tmp = cmd;
	pipping(cmd, other);
    tmp->pid = fork();
    if (tmp->pid == -1)
    {
        free_all(cmd, other);
        why_exit("Error: fork failed\n", FAILED);
    }
    if (tmp->pid == 0)
        child_process(tmp, cmd, other, 1);
    wait(NULL);
    tmp = tmp->next;
    tmp->pid = fork();
    if (tmp->pid == -1)
    {
        free_all(cmd, other);
        why_exit("Error: fork failed\n", FAILED);
    }
    if (tmp->pid == 0)
        child_process(tmp, cmd, other, 1);
    wait(NULL);
    return (SUCCESSFUL);
}

int main(int ac, char **av, char **envp)
{
    t_cmd *cmd;
    t_cmd *tmp;
    // int i;
    // pid_t pid;
    t_other other;

    // atexit(leak);
    if (ac != 5)
        return (myputstr("the number o arguments is not 5 !\n"), FAILED);
    other.debug = open ("debug", O_RDWR);
    cmd = NULL;
    other.paths = NULL;
    other.ac = ac;
    other.count_proc = ac - 3;
    edit_paths(&other, envp);
    parcing(&cmd, av, &other);
    other.infile = av[1];
    other.outfile = av[4];
    tmp = cmd;
    int i;
    while (tmp)
    {
	    printf ("cmd : %s\n", tmp->cmd);
    	printf ("opt : %s\n", tmp->opt);
        i = 0;
        while (tmp->argument[i])
	        printf ("argument : %s\n", tmp->argument[i++]);
	    printf ("ar : %d\n", tmp->ar);
    	printf ("path_cmd : %s\n", tmp->path_cmd);
        tmp = tmp->next;
    }
    printf ("all_path : %s\n", other.all_path);
	printf ("count_path : %d\n", other.count_path);
	int d = 0;
	while (d < other.count_path)
		printf ("paths : %s\n", other.paths[d++]);
    printf ("infile : %s\n", other.infile);
    printf ("outfile : %s\n", other.outfile);
    execution(cmd, &other);
    // while (1);
    free_all(cmd, &other);
    // i = 0;
    // while (i < 2)
    // {
    //     pid = fork();
    //     if (pid == 0)
    //         child_process(&cmd, av);
    //     i++;
    // }
}
