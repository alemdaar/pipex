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
	char **cmd;
	char **opt;
	char **paths;
	char *all_path;
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
// |- parcing
// |  |->parcing1.c
int	parcing(t_cmd *cmd, char **av, char **envp);
void	edit_paths(t_cmd *cmd, char **envp);
void	find_path(t_cmd *cmd, char	**envp);
void count_path(t_cmd *cmd);
void	fill_path(t_cmd *cmd, t_ind ind);
void zerod_2(char ***str, int count);
void zerod_1(char **str, int count);
void free_all (t_cmd *cmd);
int	fill_cmd(char *input, t_cmd *cmd);
int	fill_opt(char *input, t_cmd *cmd);
#endif
