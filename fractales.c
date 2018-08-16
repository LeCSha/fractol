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

void mandelbrot(t_ftc *ftc, double x, double y)
{
  double i;
  double tmp;

  ftc->c.x = (x / WIDTH) * (ftc->end.x - ftc->start.x)
  * ftc->zoom + ftc->start.x + ftc->pdx;
  ftc->c.y = (y / HEIGHT) * (ftc->end.y - ftc->start.y)
  * ftc->zoom + ftc->start.y + ftc->pdy;
  ftc->z.x = 0;
  ftc->z.y = 0;
  i = 0;
  while (ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y < 4 && i < ftc->itmax)
  {
    tmp = ftc->z.x;
    ftc->z.x = tmp * tmp - ftc->z.y * ftc->z.y + ftc->c.x;
    ftc->z.y = 2 * tmp * ftc->z.y + ftc->c.y;
    i++;
  }
	draw_fractal(ftc, x, y, smoothcolor(ftc, i));
}

void burningship(t_ftc *ftc, double x, double y)
{
  double i;
  double tmp;

  ftc->c.x = (x / WIDTH) * (ftc->end.x - ftc->start.x)
  * ftc->zoom + ftc->start.x + ftc->pdx;
  ftc->c.y = (y / HEIGHT) * (ftc->end.y - ftc->start.y)
  * ftc->zoom + ftc->start.y + ftc->pdy;
  ftc->z.x = 0;
  ftc->z.y = 0;
  i = 0;
  while (ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y < 4 && i < ftc->itmax)
  {
    tmp = ftc->z.x;
    ftc->z.x = tmp * tmp - ftc->z.y * ftc->z.y + ftc->c.x;
    ftc->z.y = 2 * fabs(tmp * ftc->z.y) + ftc->c.y;
    i++;
  }
	draw_fractal(ftc, x, y, smoothcolor(ftc, i));
}

void julia(t_ftc *ftc, double x, double y)
{
  double i;
  double tmp;

  ftc->z.x = (x / WIDTH) * (ftc->end.x - ftc->start.x)
  * ftc->zoom + ftc->start.x + ftc->pdx;
  ftc->z.y = (y / HEIGHT) * (ftc->end.y - ftc->start.y)
  * ftc->zoom + ftc->start.y + ftc->pdy;
  i = 0;
  while ((ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y) < 4 && i < ftc->itmax)
  {
    tmp = ftc->z.x;
    ftc->z.x = ftc->z.x * ftc->z.x - ftc->z.y * ftc->z.y + ftc->c.x;
    ftc->z.y = 2 * tmp * ftc->z.y + ftc->c.y;
    i++;
  }
	draw_fractal(ftc, x, y, smoothcolor(ftc, i));
}

void julia_4(t_ftc *ftc, double x, double y)
{
	double i;
	double tmp;

	ftc->c.x = (x / WIDTH) * (ftc->end.x - ftc->start.x)
	* ftc->zoom + ftc->start.x + ftc->pdx;
	ftc->c.y = (y / HEIGHT) * (ftc->end.y - ftc->start.y)
	* ftc->zoom + ftc->start.y + ftc->pdy;
	ftc->z.x = 0;
	ftc->z.y = 0;
	i = 0;
	while (ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y < 4 && i < ftc->itmax)
	{
		tmp = ftc->z.x;
		ftc->z.x = tmp * tmp * tmp * tmp + ftc->z.y * ftc->z.y
		* ftc->z.y * ftc->z.y - 6 * tmp * tmp * ftc->z.y * ftc->z.y + ftc->c.x;
		ftc->z.y = 4 * tmp * ftc->z.y * (tmp * tmp - ftc->z.y * ftc->z.y) + ftc->c.y;
		i++;
	}
	draw_fractal(ftc, x, y, smoothcolor(ftc, i));
}

void	test(t_ftc *ftc, double x, double y)
{
  double i;
  double tmp;

  ftc->c.x = (x / WIDTH) * (ftc->end.x - ftc->start.x)
  * ftc->zoom + ftc->start.x + ftc->pdx;
  ftc->c.y = (y / HEIGHT) * (ftc->end.y - ftc->start.y)
  * ftc->zoom + ftc->start.y + ftc->pdy;
  ftc->z.x = 0;
  ftc->z.y = 0;
  i = 0;
  while (ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y < 4 && i < ftc->itmax)
  {
    tmp = ftc->z.x;
    ftc->z.x = cos(tmp * tmp - ftc->z.y * ftc->z.y) / ftc->c.x;
    ftc->z.y = 2 * tmp * ftc->z.y + ftc->c.y;
    i++;
  }
	draw_fractal(ftc, x, y, smoothcolor(ftc, i));
}