/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:50:01 by abaille           #+#    #+#             */
/*   Updated: 2018/06/25 09:50:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_fractal(t_ftc *ftc, int x, int y, int color)
{
	ftc->mx->data[y * WIDTH + x] = color;
}

void	it_draw(t_ftc *ftc, void (func)(t_ftc *, double, double))
{
	double x;
	double y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			func(ftc, x, y);
			x++;
		}
		y++;
	}
}

void 	redraw(t_ftc *ftc)
{
	mlx_clear_window(ftc->mx->mptr, ftc->mx->wptr);
	string_put(ftc);
	it_draw(ftc, ftc->fractal);
	mlx_put_image_to_window(ftc->mx->mptr, ftc->mx->wptr, ftc->mx->iptr, 0, 0);
}