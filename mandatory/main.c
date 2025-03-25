/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:57:09 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/25 17:43:06 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// void ll(){
// 	while (1);
// }

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	t_other	other;

	// atexit(ll);
	if (ac != 5)
		return (myputstr("args != 5 !\n", 2), FAILED);
	if (envp == NULL)
		return (myputstr("env is empty\n", 2), FAILED);
	cmd = NULL;
	other.paths = NULL;
	other.ac = ac;
	other.count_proc = ac - 3;
	other.infile = av[1];
	other.outfile = av[ac - 1];
	edit_paths(&other, envp);
	parcing(&cmd, av, &other);
	int i;
	t_cmd *tmp;
	tmp = cmd;
	while (tmp)
	{
		printf ("cmd : %s\n", tmp->cmd);
		printf ("opt : %s\n", tmp->opt);
		printf ("path_cmd : %s\n", tmp->path_cmd);
		i = 0;
		while (tmp->argument[i])
			printf ("argument : %s\n", tmp->argument[i++]);
		tmp = tmp->next;
	}
	printf ("ac : %d\n", other.ac);
	printf ("all path : %s\n", other.all_path);
	printf ("count_path : %d\n", other.count_path);
	printf ("count_proc : %d\n", other.count_proc);
	printf ("infile : %s\n", other.infile);
	printf ("outfile : %s\n", other.outfile);
	i = 0;
	while (other.paths[i])
		printf ("paths : %s\n", other.paths[i++]);
	execution(cmd, &other);
	free_all(&cmd, &other);
	
}
