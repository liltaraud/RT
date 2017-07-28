/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 17:16:10 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/22 22:51:48 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_elm				*add_elm(void *ptr, char type, t_elm *stk)
{
	t_elm		*ret;

	if (stk == NULL || !(ret = malloc(sizeof(struct s_elm))))
		return (NULL);
	while (stk->next)
		stk = stk->next;
	stk->next = ret;
	ret->next = NULL;
	if (type == -1)
		ret->type = stk->type;
	else
		ret->type = type;
	ret->elm = ptr;
	return (ret);
}
