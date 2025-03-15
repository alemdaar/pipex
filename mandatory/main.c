#include "header.h"

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
    while (1);

}
