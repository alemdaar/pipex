#include "header.h"

void leak()
{
    system("leaks -q pipex");
}

void protect_it(t_cmd *cmd)
{
    cmd->all_path = NULL;
    cmd->cmd = NULL;
    cmd->opt = NULL;
    cmd->paths = NULL;
}

int main (int ac, char **av, char **envp)
{
    t_cmd cmd;
    // ./pipex infile "ls -l" "wc -l" outfile
    // < infile ls -l | wc -l > outfile
    // ./pipex infile "grep a1" "wc -w" outfile
    // < infile grep a1 | wc -w > outfile
    atexit(leak);
    if (ac != 5)
        return (myputstr("the number o arguments is not 5 !"), FAILED);
    protect_it(&cmd);
    parcing(av, envp);
}
