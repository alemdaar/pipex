/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:33:19 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/10 20:07:08 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_cmd	*ft_lstnew(void)
{
	t_cmd	*elem;

	elem = malloc(sizeof(t_cmd));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	return (elem);
}

void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last_node;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}

t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
