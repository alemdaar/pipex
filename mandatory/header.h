#if !defined(HEADER_H)
#define HEADER_H

#define SUCCESSFUL 0
#define FAILED 1
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define INPUT 0
#define OUTPUT 1

// public prototypes
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
// struct
typedef struct s_cmd {
	char *cmd;
	char *opt;
	char **paths;
	char **all_path;
	int	count_path;
	
}	t_cmd;

typedef struct s_ind
{
	int	i;
	int	j;
	int	c;
}	t_ind;

// prototypes
// |
// |-display
// |  |->display.c
void myputstr(char *str);
void why_exit(char *str, int type);
// |-tools
// |  |->tools.c
int		mystrlen(char *str);
char	*mixem(char *path, char *cmd);
// |- parcing
// |  |->parcing1.c
int		parcing(char **av, char **envp);
int		check_cmd(char *cmd, t_cmd *cmd);
int		check_access(char *path, char *cmd);
char	*fill_cmd(char *cmd);
#endif
