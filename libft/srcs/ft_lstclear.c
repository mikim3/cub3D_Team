/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:31:21 by soylee            #+#    #+#             */
/*   Updated: 2022/04/07 18:42:48 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*tmp;

	curr = *lst;
	while (curr != 0)
	{
		tmp = curr -> next;
		ft_lstdelone(curr, del);
		curr = tmp;
	}
	*lst = 0;
}
