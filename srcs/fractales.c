/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:50:01 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 09:50:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_ftc *ftc, double x, double y)
{
	double i;
	double tmp;
	t_cpx	z;
	t_cpx	c;

	c.x = (x / WIDTH) * (ftc->end.x - ftc->start.x)
	* ftc->zoom + ftc->start.x + ftc->pdx;
	c.y = (y / HEIGHT) * (ftc->end.y - ftc->start.y)
	* ftc->zoom + ftc->start.y + ftc->pdy;
	z.x = 0;
	z.y = 0;
	i = 0;
	while (z.x * z.x + z.y * z.y < 4 && i < ftc->itmax)
	{
		tmp = z.x;
		z.x = tmp * tmp - z.y * z.y + c.x;
		z.y = 2 * tmp * z.y + c.y;
		i++;
	}
	draw_fractal(ftc, x, y, smoothcolor(ftc, i, z));
}

void	burningship(t_ftc *ftc, double x, double y)
{
	double i;
	double tmp;
	t_cpx	z;
	t_cpx	c;

	c.x = (x / WIDTH) * (ftc->end.x - ftc->start.x)
	* ftc->zoom + ftc->start.x + ftc->pdx;
	c.y = (y / HEIGHT) * (ftc->end.y - ftc->start.y)
	* ftc->zoom + ftc->start.y + ftc->pdy;
	z.x = 0;
	z.y = 0;
	i = 0;
	while (z.x * z.x + z.y * z.y < 4 && i < ftc->itmax)
	{
		tmp = z.x;
		z.x = tmp * tmp - z.y * z.y + c.x;
		z.y = 2 * fabs(tmp * z.y) + c.y;
		i++;
	}
	draw_fractal(ftc, x, y, smoothcolor(ftc, i, z));
}

void	julia(t_ftc *ftc, double x, double y)
{
	double i;
	double tmp;
	t_cpx	z;

	z.x = (x / WIDTH) * (ftc->end.x - ftc->start.x)
	* ftc->zoom + ftc->start.x + ftc->pdx;
	z.y = (y / HEIGHT) * (ftc->end.y - ftc->start.y)
	* ftc->zoom + ftc->start.y + ftc->pdy;
	i = 0;
	while ((z.x * z.x + z.y * z.y) < 4 && i < ftc->itmax)
	{
		tmp = z.x;
		z.x = z.x * z.x - z.y * z.y + ftc->c.x;
		z.y = 2 * tmp * z.y + ftc->c.y;
		i++;
	}
	draw_fractal(ftc, x, y, smoothcolor(ftc, i, z));
}

void	tribrot(t_ftc *ftc, double x, double y)
{
	double i;
	double tmp;
	t_cpx	z;
	t_cpx	c;

	c.x = (x / WIDTH) * (ftc->end.x - ftc->start.x)
	* ftc->zoom + ftc->start.x + ftc->pdx;
	c.y = (y / HEIGHT) * (ftc->end.y - ftc->start.y)
	* ftc->zoom + ftc->start.y + ftc->pdy;
	z.x = 0;
	z.y = 0;
	i = 0;
	while (z.x * z.x + z.y * z.y < 4 && i < ftc->itmax)
	{
		tmp = z.x;
		z.x = tmp * tmp * tmp * tmp + z.y * z.y
		* z.y * z.y - 6 * tmp * tmp * z.y * z.y + c.x;
		z.y = 4 * tmp * z.y *
		(tmp * tmp - z.y * z.y) + c.y;
		i++;
	}
	draw_fractal(ftc, x, y, smoothcolor(ftc, i, z));
}
