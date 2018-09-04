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

int				change_seqlyapu(t_ftc *ftc)
{
	char slyapu[100];

	ft_putstr("Enter a sequence Ex : (ABBA) (ABAAABB) (AAABAB) >>");
	ft_bzero(slyapu, 100);
	fgets(slyapu, 100, stdin);
	if (slyapu[0] != 0)
	{
		free(ftc->seq);
		if (!(ftc->seq = ft_strdup(slyapu)))
			print_error(1, ftc);
	}
	return (0);
}

static double	c_lyapu(t_ftc *ftc, int i, t_cpx ab)
{
	if (ftc->seq[i % ft_strlen(ftc->seq)] == 'A')
		return (ab.x);
	return (ab.y);
}

static void		draw_lmbda(t_ftc *ftc, double x, double y, double lmbda)
{
	if (lmbda < 0)
		draw_fractal(ftc, x, y, smoothcolor(ftc, lmbda * -1 * 255, ftc->c));
	else
		draw_fractal(ftc, x, y, ((int)(lmbda / 2 * 255)) << 0);
}

void			lyapunov(t_ftc *ftc, double x, double y)
{
	t_cpx	ab;
	double	lmbda;
	double	x_n[ftc->itmax + 1];
	int		i;

	x_n[0] = 0.5;
	ab.x = ftc->c.x - ftc->imgx / 2.0 + ftc->imgx * x / WIDTH + ftc->pdx;
	ab.y = ftc->c.y + ftc->imgy / 2.0 - ftc->imgy * y / HEIGHT + ftc->pdy;
	if (ab.x < 0 || ab.x > 4 || ab.y < 0 || ab.y > 4)
		lmbda = INT_MAX;
	else
	{
		lmbda = 0;
		i = 1;
		while (i <= ftc->itmax)
		{
			x_n[i] = c_lyapu(ftc, i - 1, ab) * x_n[i - 1] * (1 - x_n[i - 1]);
			lmbda += log(fabs(c_lyapu(ftc, i, ab) * (1 - 2 * x_n[i]))) /
			log(2);
			i++;
		}
		lmbda /= ftc->itmax;
	}
	draw_lmbda(ftc, x, y, lmbda);
}

void			init_lyapu(t_ftc *ftc)
{
	if (!(ftc->seq = ft_strdup("BBAAAAABBABA")))
		print_error(1, ftc);
	ftc->itmax = 100;
	ftc->zoom = 0.3f;
	ftc->imgy = ftc->zoom * 2;
	ftc->imgx = ftc->imgy * WIDTH / HEIGHT;
	ftc->stpmov = 0;
	ftc->c.x = 3.4f - ftc->imgx / 2;
	ftc->c.y = 3.7f;
}
