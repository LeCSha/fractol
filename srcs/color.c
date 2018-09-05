/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:50:01 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 09:50:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_rgb	inttorgb(int color)
{
	t_rgb rgb;

	rgb.r = ((double)(color >> 16));
	rgb.g = ((double)(color >> 8));
	rgb.b = ((double)color);
	return (rgb);
}

int		mixcolors(int color1, int color2, double p)
{
	t_rgb	c1;
	t_rgb	c2;
	t_rgb	rgb;
	int		color;

	if (color1 == color2)
		return (color1);
	c1 = inttorgb(color1);
	c2 = inttorgb(color2);
	rgb.r = (char)((double)c1.r + (c2.r - c1.r) * p);
	rgb.g = (char)((double)c1.g + (c2.g - c1.g) * p);
	rgb.b = (char)((double)c1.b + (c2.b - c1.b) * p);
	color = (rgb.r << 16) + (rgb.g << 8) + (rgb.b);
	return (color);
}

int		smoothcolor(t_ftc *ftc, double i, t_cpx z)
{
	double	index;
	double	adjust;
	int		c;

	if (i == ftc->itmax)
		return (0x000000);
	index = i + 1 - log(log(sqrt(z.x *
		z.x + z.y * z.y))) + 4;
	if (index < 0)
		index = 0;
	index = index / ftc->itmax;
	c = ftc->palptr->size - 1;
	adjust = fmod(index, 1.0f / c) * c;
	return (mixcolors((ftc->palptr->c[(int)(index * c) + 1]),
	(ftc->palptr->c[(int)(index * c)]),
		(int)adjust + 1 - adjust));
}

t_pal	*init_colors(void)
{
	t_pal	*tab;

	if (!(tab = (t_pal*)malloc(sizeof(t_pal) * 7)))
		return (NULL);
	tab[0] =
		(t_pal){5, {0x1B998B, 0xFFFD82, 0x2D3047, 0xED217C, 0xFF9B71}};
	tab[1] =
		(t_pal){5, {0xFD8437, 0x590B36, 0xDD3C39, 0xF48326, 0xF5F55C}};
	tab[2] =
		(t_pal){5, {0xBCABAE, 0x0F0F0F, 0x2D2E2E, 0x716969, 0xFBFBFB}};
	tab[3] =
		(t_pal){5, {0xD138BF, 0x7565BC, 0x41C0E0, 0x7494EA, 0xD138BF}};
	tab[4] =
		(t_pal){5, {0xDABFFF, 0x907AD6, 0x4F518C, 0x2C2A4A, 0x7FDEFF}};
	tab[5] =
		(t_pal){5, {0x3D314A, 0x02020A, 0x05204A, 0xB497D6, 0xE1E2EF}};
	return (tab);
}
