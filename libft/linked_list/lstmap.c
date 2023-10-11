/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:55:16 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;
	void	*tmp_cont;

	head = (void *) 0;
	while (lst)
	{
		tmp_cont = f(lst->content);
		tmp = lstnew(tmp_cont);
		if (tmp)
			lstadd_back(&head, tmp);
		else
		{
			del(tmp_cont);
			lstclear(&head, del);
			return (head);
		}
		lst = lst->next;
	}
	return (head);
}
