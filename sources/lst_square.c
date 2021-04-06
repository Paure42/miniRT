/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <paure@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:11:07 by paure             #+#    #+#             */
/*   Updated: 2020/05/13 14:16:47 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void		sq_lstadd_front(t_square **alst, t_square *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

void		sq_lstadd_back(t_square **alst, t_square *new)
{
	t_square	*tmp;

	if (!alst || !new)
		return ;
	new->next = 0;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_square	*sq_lstlast(t_square *lst)
{
	if (!(lst))
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_square	*sq_lstnew(void)
{
	t_square	*list;

	if (!(list = (t_square*)malloc(sizeof(*list))))
		return (0);
	list->next = 0;
	return (list);
}

int			sq_lstsize(t_square *lst)
{
	int	n;

	if (!lst)
		return (0);
	n = 1;
	while (lst->next)
	{
		lst = lst->next;
		n++;
	}
	return (n);
}
