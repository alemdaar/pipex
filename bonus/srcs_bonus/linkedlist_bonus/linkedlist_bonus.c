/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelhasso <elhassounioussama2@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:33:19 by oelhasso          #+#    #+#             */
/*   Updated: 2025/03/17 17:40:00 by oelhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header_bonus.h"

// int	ft_lstsize(t_cmd *lst)
// {
// 	int	count;

// 	count = 0;
// 	while (lst != NULL)
// 	{
// 		count++;
// 		lst = lst->next;
// 	}
// 	return (count);
// }

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
