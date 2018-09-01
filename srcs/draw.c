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

void	reset(t_ftc *ftc)
{
	ftc->palptr = &ftc->pcolors[0];
	ftc->seq = NULL;
	ftc->itmax = 100;
	ftc->zoom = 1.0f;
	ftc->stpmov = 5;
	ftc->c.x = 0.0;
	ftc->c.y = 0.0;
	ftc->start.x = -2.0f;
	ftc->end.x = 2.0f;
	ftc->start.y = -2.0f;
	ftc->end.y = 2.0f;
	ftc->pdx = 0.0;
	ftc->pdy = 0.0;
}

void	draw_fractal(t_ftc *ftc, int x, int y, int color)
{
	ftc->mx->data[y * WIDTH + x] = color;
}

void	it_draw(t_ftc *ftc, void (func)(t_ftc *, double, double), int line)
{
	double x;
	double y;

	y = line - 1;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			func(ftc, x, y);
			x++;
		}
		y += 4;
	}
}

void	redraw(t_ftc *ftc)
{
	mlx_clear_window(ftc->mx->mptr, ftc->mx->wptr);
	string_put(ftc);
	init_thread(ftc);
	mlx_put_image_to_window(ftc->mx->mptr, ftc->mx->wptr, ftc->mx->iptr, 0, 0);
}
