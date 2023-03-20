/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:03:28 by soylee            #+#    #+#             */
/*   Updated: 2023/03/12 15:03:29 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int     print_error(char *msg);
void    exit_error(char *msg);
int     check_extension(char *filename);
void    ft_free(char **str);

#endif