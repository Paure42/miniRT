/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_disk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <paure@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:10:50 by paure             #+#    #+#             */
/*   Updated: 2020/05/13 14:16:31 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void		di_lstadd_front(t_disk **alst, t_disk *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

void		di_lstadd_back(t_disk **alst, t_disk *new)
{
	t_disk	*tmp;

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

t_disk		*di_lstlast(t_disk *lst)
{
	if (!(lst))
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_disk		*di_lstnew(void)
{
	t_disk	*list;

	if (!(list = (t_disk*)malloc(sizeof(*list))))
		return (0);
	list->next = 0;
	return (list);
}

int			di_lstsize(t_disk *lst)
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
