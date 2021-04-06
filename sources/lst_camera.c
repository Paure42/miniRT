/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <paure@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:10:41 by paure             #+#    #+#             */
/*   Updated: 2020/05/13 14:10:42 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void		cam_lstadd_front(t_cam **alst, t_cam *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

void		cam_lstadd_back(t_cam **alst, t_cam *new)
{
	t_cam *tmp;

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

t_cam		*cam_lstlast(t_cam *lst)
{
	if (!(lst))
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_cam		*cam_lstnew(void)
{
	t_cam	*list;

	if (!(list = (t_cam*)malloc(sizeof(*list))))
		return (0);
	list->next = 0;
	return (list);
}

int			cam_lstsize(t_cam *lst)
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
