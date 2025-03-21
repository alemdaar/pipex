/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:57:09 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/21 01:51:57 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

static void	is_here_doc(char *str, t_other *other)
{
	other->is_limiter = 0;
	if (str[0] == 'h' && str[1] == 'e' && str[2] == 'r')
	{
		if (str[3] == 'e' && str[4] == '_' && str[5] == 'd')
		{
			if (str[6] == 'o' && str[7] == 'c' && str[8] == 0)
			{
				other->is_limiter = 1;
				if (access("/tmp/here_doc", F_OK) == 0)
					unlink("/tmp/here_doc");
				return ;
			}
		}
	}
	return ;
}

static void	set_up(int ac, char **av, t_other *other)
{
	other->paths = NULL;
	other->limiter = NULL;
	other->ac = ac;
	other->count_proc = ac - 3;
	if (other->is_limiter == TRUE)
		other->count_proc --;
	if (other->is_limiter == TRUE)
		other->limiter = av[2];
	if (other->is_limiter == FALSE)
		other->infile = av[1];
	else
		other->infile = "/tmp/here_doc";
	other->outfile = av[ac - 1];
}

void ll(){
	system("leaks pipex");
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	t_other	other;
	atexit(ll);
	if (ac < 5)
		return (myputstr("args nb < 5 !\n", 2), FAILED);
	is_here_doc(av[1], &other);
	set_up(ac, av, &other);
	if (other.is_limiter == TRUE)
		make_heredoc(&other);
	cmd = NULL;
	edit_paths(&other, envp);
	parcing(&cmd, av, &other);
	execution(cmd, &other);
	free_all(cmd, &other);
}
