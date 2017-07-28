/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 13:25:19 by ltaraud           #+#    #+#             */
/*   Updated: 2015/12/19 17:19:04 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*new;
	t_list		*head;

	new = NULL;
	head = NULL;
	if (lst == NULL || f == NULL)
		return (NULL);
	head = ft_lstnew(lst->content, lst->content_size);
	if (head == NULL)
		return (NULL);
	head = f(head);
	new = head;
	lst = lst->next;
	while (lst != NULL)
	{
		new->next = ft_lstnew(lst->content, lst->content_size);
		if (new->next == NULL)
			return (NULL);
		new->next = f(new->next);
		new = new->next;
		lst = lst->next;
	}
	return (head);
}
