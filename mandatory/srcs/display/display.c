/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:02:49 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/16 18:03:15 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	myputstr(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

void	why_exit(char *str, int type)
{
	int	fd;

	if (type == 1)
		fd = 2;
	else if (type == 0)
		fd = 1;
	myputstr(str, fd);
	exit(type);
}
