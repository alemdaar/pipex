/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:57:09 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/17 17:08:14 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	t_other	other;

	if (ac != 5)
		return (myputstr("args != 5 !\n", 2), FAILED);
	cmd = NULL;
	other.paths = NULL;
	other.ac = ac;
	other.count_proc = ac - 3;
	other.infile = av[1];
	other.outfile = av[ac - 1];
	edit_paths(&other, envp);
	parcing(&cmd, av, &other);
	execution(cmd, &other);
	free_all(cmd, &other);
}
