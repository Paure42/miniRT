/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <paure@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:11:11 by paure             #+#    #+#             */
/*   Updated: 2020/05/13 14:11:12 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void			tr_lstadd_front(t_triangle **alst, t_triangle *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

void			tr_lstadd_back(t_triangle **alst, t_triangle *new)
{
	t_triangle	*tmp;

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

t_triangle		*tr_lstlast(t_triangle *lst)
{
	if (!(lst))
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_triangle		*tr_lstnew(void)
{
	t_triangle	*list;

	if (!(list = (t_triangle*)malloc(sizeof(*list))))
		return (0);
	list->next = 0;
	return (list);
}

int				tr_lstsize(t_triangle *lst)
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
