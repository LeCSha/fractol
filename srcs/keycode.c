/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:50:01 by abaille           #+#    #+#             */
/*   Updated: 2019/05/28 22:17:40 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	choose_fract(int key, t_ftc *ftc)
{
	if (key == 83)
	{
		ftc->fname = ft_strdup("mandelbrot");
		ftc->fractal = &mandelbrot;
	}
	else if (key == 84)
	{
		ftc->fname = ft_strdup("julia");
		ftc->fractal = &julia;
	}
	else if (key == 85)
	{
		ftc->fname = ft_strdup("tribrot");
		ftc->fractal = &tribrot;
	}
	else if (key == 86)
	{
		ftc->fname = ft_strdup("burningship");
		ftc->fractal = &burningship;
	}
	else if (key == 87)
	{
		ftc->fname = ft_strdup("lyapunov");
		ftc->fractal = &lyapunov;
	}
}

void	change_fract(int key, t_ftc *ftc)
{
	free(ftc->fname);
	if (ftc->seq != NULL)
		free(ftc->seq);
	reset(ftc);
	choose_fract(key, ftc);
	if (key == 87)
		init_lyapu(ftc);
}

void	zoom(int key, t_ftc *ftc)
{
	double oldw;
	double oldh;
	double neww;
	double newh;

	oldw = (ftc->end.x - ftc->start.x) * ftc->zoom;
	oldh = (ftc->end.y - ftc->start.y) * ftc->zoom;
	ftc->zoom = (key == 69) ? ftc->zoom * (1 / 1.1f) : ftc->zoom * 1.1f;
	neww = (ftc->end.x - ftc->start.x) * ftc->zoom;
	newh = (ftc->end.y - ftc->start.y) * ftc->zoom;
	ftc->pdx -= ((double)WIDTH / 2 / WIDTH) * (neww - oldw);
	ftc->pdy -= ((double)HEIGHT / 2 / HEIGHT) * (newh - oldh);
}

void	moove(int key, t_ftc *ftc)
{
	if (key == 123)
		ftc->pdx -= ftc->zoom * 0.5f;
	if (key == 124)
		ftc->pdx += ftc->zoom * 0.5f;
	if (key == 125)
		ftc->pdy += ftc->zoom * 0.5f;
	if (key == 126)
		ftc->pdy -= ftc->zoom * 0.5f;
}

int		keycode(int key, t_ftc *ftc)
{
	if (key == 53)
		exit_ftc(ftc);
	if (key == 76)
		reset(ftc);
	if (key == 7)
		ftc->itmax += 5;
	if (key == 6)
	{
		if (ftc->itmax > 0)
			ftc->itmax -= 5;
		else
			ftc->itmax = 0;
	}
	if (key == 69 || key == 78)
		zoom(key, ftc);
	if (key == 125 || key == 126 || key == 123 || key == 124)
		moove(key, ftc);
	if (key >= 83 && key <= 87)
		change_fract(key, ftc);
	if (key >= KEY_1 && key <= KEY_6)
		ftc->palptr = &ftc->pcolors[key - KEY_1];
	if (ft_strcmp(ftc->fname, "lyapunov") == 0 && key == 8)
		change_seqlyapu(ftc);
	redraw(ftc);
	return (0);
}
