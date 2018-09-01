/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousecode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:50:01 by abaille           #+#    #+#             */
/*   Updated: 2018/06/25 09:50:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mousemotion(int x, int y, t_ftc *ftc)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT && ftc->stpmov > 0)
	{
		ftc->c.x = (double)x / (double)WIDTH * 4.0 - 2;
		ftc->c.y = (double)y / (double)HEIGHT * 4.0 - 2;
		redraw(ftc);
	}
	return (1);
}

void	zoomouse(int button, int x, int y, t_ftc *ftc)
{
	double oldw;
	double oldy;
	double neww;
	double newy;

	oldw = (ftc->end.x - ftc->start.x) * ftc->zoom;
	oldy = (ftc->end.y - ftc->start.y) * ftc->zoom;
	ftc->zoom = (button == 5) ? ftc->zoom * (1 / 1.1f) : ftc->zoom * 1.1f;
	neww = (ftc->end.x - ftc->start.x) * ftc->zoom;
	newy = (ftc->end.y - ftc->start.y) * ftc->zoom;
	ftc->pdx -= (double)x / WIDTH * (neww - oldw);
	ftc->pdy -= (double)y / HEIGHT * (newy - oldy);
}

int		mousecode(int button, int x, int y, t_ftc *ftc)
{
	if ((button == 4 || button == 5) && ft_strcmp("lyapunov", ftc->fname) != 0)
		zoomouse(button, x, y, ftc);
	if (button == 1 || button == 2)
		ftc->stpmov = (button == 2) ? 1 : 0;
	redraw(ftc);
	return (1);
}
