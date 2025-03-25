/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:56:48 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/25 17:29:06 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define SUCCESSFUL 0
# define FAILED 1
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define INPUT 0
# define OUTPUT 1
# define READ 0
# define WRITE 1
# define STD_OUT 1
# define STD_ERR 2

// public prototypes
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
// struct
typedef struct s_cmd {
	char			*cmd;
	char			*path_cmd;
	char			*opt;
	char			**argument;
	int				ar;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_other {
	int		count_path;
	char	*all_path;
	char	**paths;
	int		ac;
	int		count_proc;
	char	*infile;
	char	*outfile;
	int		open1;
	int		open2;
	int		pipefd[2];
}	t_other;

typedef struct s_ind
{
	int	i;
	int	j;
	int	c;
	int	r;
	int	t;
	int	f;
}	t_ind;

void	myputstr(char *str, int fd);
void	why_exit(char *str, int type);
char	*mixem(t_cmd *cmd, t_other *other, int path_ind);
int		mystrlen(char *str);
void	protect_it(t_cmd *cmd);
int		parcing(t_cmd **cmd, char **av, t_other *other);
void	edit_paths(t_other *other, char **envp);
int		find_path(t_other *other, char **envp);
void	count_path(t_other *other);
void	fill_path(t_other *other, t_ind ind);
void	free_all(t_cmd **cmd, t_other *other);
int		fill_cmd(char *input, t_cmd *cmd, t_ind *rtn);
int		fill_opt(char *input, t_cmd *cmd, int pos);
int		fill_opt2(char *input, t_cmd *cmd, t_ind *ind);
int		check_cmd(t_cmd *cmd, t_other *other);
int		check_access(t_cmd *cmd, t_other *other, int path_ind);
int		edit_cmd(t_cmd *cmd, char **av, int flag);
int		check_file(t_cmd *cmd, t_other *other, int flag);
int		fill_argument(t_cmd **cmd);
int		fill_argument2(t_cmd *tmp, t_ind *ind);
t_cmd	*ft_lstnew(void);
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstlast(t_cmd *lst);
int		is_awk(char *cmd);
int		awk_arg(t_cmd **cmd);
int		awk_arg2(t_cmd *tmp, t_ind *ind);
int		awk_arg3(t_cmd *tmp, t_ind *ind);
int		count_awk_opt(char *opt);
int		execution(t_cmd *cmd, t_other *other);
int		close_fds(int fds[2], int file);
#endif