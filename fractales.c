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
  if (i == ftc->itmax)
    // mlx_pixel_put(ftc->mx->mptr, ftc->mx->wptr, x, y, 0x000000);
    draw_fractal(ftc, x, y, 0x000000);
  else
  {
    // i = i - log(log(sqrt(ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.x))) / log(2);
    // mlx_pixel_put(ftc->mx->mptr, ftc->mx->wptr, x, y, i * (0xFF0000 / ftc->itmax) / 50);
    // i = i + 1 - log(log(fabs(ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.x))) / log(2);
    // mlx_pixel_put(ftc->mx->mptr, ftc->mx->wptr, x, y, (int)(i * 0x84742d / ftc->itmax) >> 16);
    i = i - log(log(sqrt(ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y))) + 4;
    // mlx_pixel_put(ftc->mx->mptr, ftc->mx->wptr, x, y, i * 0x84742d / ftc->itmax);
    draw_fractal(ftc, x, y, i * i);
    // draw_fractal(ftc, x, y, i * (0x84742d / ftc->itmax) / 50);
  }
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
  if (i == ftc->itmax)
    draw_fractal(ftc, x, y, 0x000000);
  else
  {
    i = i - log(log(sqrt(ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y))) + 4;
    draw_fractal(ftc, x, y, ((int)(i * i)) << 16);
  }
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
  if (i == ftc->itmax)
    draw_fractal(ftc, x, y, 0x000000);
  else
  {
    i = i - log(log(sqrt(ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y))) + 4;
    draw_fractal(ftc, x, y, i * i);
  }
}

void mandel_tri(t_ftc *ftc, double x, double y)
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
  if (i == ftc->itmax)
    draw_fractal(ftc, x, y, 0x000000);
  else
  {
    i = i - log(log(sqrt(ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y))) + 4;
    draw_fractal(ftc, x, y, i * i);
  }
}


double	c_lyapu(t_ftc *ftc, int i, double a, double b)
{
	if (ftc->lyapu[i % ft_strlen(ftc->lyapu)] == 'A')
		return (a);
	return (b);
}

void	lyapunov(t_ftc *ftc, double x, double y)
{
	double	a;
	double	b;
	double	lmbda;
	double	x_n[ftc->itmax + 1];
	int			i;

	x_n[0] = 0.5;
	while	(y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			a = ftc->z.x - ftc->imgx / 2.0 + ftc->imgx * x / WIDTH;
			b = ftc->z.y + ftc->imgy / 2.0 - ftc->imgy * y / HEIGHT;
			if (a < 0 || a > 4 || b < 0 || b > 4)
				lmbda = INT_MAX;
			else
			{
				lmbda = 0;
				i = 1;
				while (i <= ftc->itmax)
				{
					x_n[i] = c_lyapu(ftc, i - 1, a, b) * x_n[i - 1] * (1 - x_n[i - 1]);
					lmbda += log(fabs(c_lyapu(ftc, i, a, b) * (1 - 2 * x_n[i]))) / log(2);
					i++;
				}
				lmbda /= ftc->itmax;
			}
			if (lmbda == INT_MAX)
				draw_fractal(ftc, x, y, 0x000000);
			else if (lmbda < 0)
				draw_fractal(ftc, x, y, ((int)(lmbda/-1*255)) << 8);
			else
				draw_fractal(ftc, x, y, ((int)(lmbda/2*255)) << 0);
			x++;
		}
		y++;
	}	
}

void	init_lyapu(t_ftc *ftc, double x, double y)
{
	ftc->lyapu = ft_strdup("AAAAAABBBBBB");
	ftc->itmax = 100;
	ftc->zoom = 0.3f;
	ftc->imgy = ftc->zoom * 2;
	ftc->imgx = ftc->imgy * WIDTH / HEIGHT;
	ftc->z.x = 3.4f - ftc->imgx / 2;
	ftc->z.y = 3.7f;
	ftc->stpmov = 0;
	lyapunov(ftc, x, y);
}
// 0xb000b5
// 0x707020