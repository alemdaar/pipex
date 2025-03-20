/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:20:38 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/20 22:27:40 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

int	check_file2(t_cmd *cmd, t_other *other, int flag)
{
	char	*s;

	if (flag == other->count_proc - 1)
	{
		s = other->outfile;
		if (other->is_limiter == TRUE)
			other->open2 = open(r, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			other->open2 = open(r, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (other->open2 == -1)
		{
			close(other->prev_read);
			return (free_all(cmd, other), perror("open: "), exit(1), 1);
		}
	}
	return (SUCCESSFUL);
}
