/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:50:01 by abaille           #+#    #+#             */
/*   Updated: 2018/06/25 09:50:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void print_error(int nb, t_ftc *ftc)
{
  if (nb == 1)
    ft_putstr("Problem with allocation memory\n");
  else if (nb == 2)
    ft_putstr("Map not valid\n");
  else if (nb == 3)
    ft_putstr("Problem reading file/allocation failed\n");
  else if (nb == 4)
    ft_putstr("Map size not valid/no value\n");
  else if (nb == 5)
    ftc = NULL;
    // fdf_usage();
  exit(0);
}
