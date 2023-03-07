/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:21:52 by soylee            #+#    #+#             */
/*   Updated: 2022/04/09 22:27:27 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*curr;
	t_list	*tmp;

	new = 0;
	curr = 0;
	while (1)
	{
		tmp = ft_lstnew(f(lst -> content));
		if (!tmp)
		{
			ft_lstclear(&new, del);
			break ;
		}
		if (curr == 0)
			new = tmp;
		else
			curr -> next = tmp;
		curr = tmp;
		lst = lst -> next;
		if (!lst)
			break ;
	}
	return (new);
}
