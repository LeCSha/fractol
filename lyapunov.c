/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lyapunov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:50:01 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 09:50:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	c_lyapu(t_ftc *ftc, int i, double a, double b)
{
	if (ftc->seq[i % ft_strlen(ftc->seq)] == 'A')
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
	a = ftc->z.x - ftc->imgx / 2.0 + ftc->imgx * x / WIDTH + ftc->pdx;
	b = ftc->z.y + ftc->imgy / 2.0 - ftc->imgy * y / HEIGHT + ftc->pdy;
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
	if (lmbda < 0)
		draw_fractal(ftc, x, y, smoothcolor(ftc, lmbda * -1 * 255));
	else
		draw_fractal(ftc, x, y, ((int)(lmbda/2*255)) << 0);
}

void	init_lyapu(t_ftc *ftc)
{
	if (!(ftc->seq = ft_strdup("AABB")))
		print_error(1, ftc);
	ftc->itmax = 100;
	ftc->zoom = 0.3f;
	ftc->imgy = ftc->zoom * 2;
	ftc->imgx = ftc->imgy * WIDTH / HEIGHT;
	ftc->z.x = 3.4f - ftc->imgx / 2;
	ftc->z.y = 3.7f;
	ftc->stpmov = 0;
}
