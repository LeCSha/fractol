/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:26:00 by abaille           #+#    #+#             */
/*   Updated: 2017/11/22 16:26:03 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double  ft_modf(double nb, double *nbr)
{
  *nbr = (int)nb;
  return (nb - (int)nb);
}
