/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <paure@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:10:46 by paure             #+#    #+#             */
/*   Updated: 2020/05/13 14:16:18 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void		cy_lstadd_front(t_cylinder **alst, t_cylinder *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

void		cy_lstadd_back(t_cylinder **alst, t_cylinder *new)
{
	t_cylinder	*tmp;

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

t_cylinder	*cy_lstlast(t_cylinder *lst)
{
	if (!(lst))
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_cylinder	*cy_lstnew(void)
{
	t_cylinder	*list;

	if (!(list = (t_cylinder*)malloc(sizeof(*list))))
		return (0);
	list->next = 0;
	return (list);
}

int			cy_lstsize(t_cylinder *lst)
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
