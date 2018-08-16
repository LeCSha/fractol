/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:50:01 by abaille           #+#    #+#             */
/*   Updated: 2018/06/25 09:50:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void string_put(t_ftc *ftc)
{
	mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 10, 810, 0x2EDD17, ftc->fname);
	mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 10, 830, 0x2EDD17, "c x : ");
	mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 80, 830, 0x2EDD17, ft_ftoa(ftc->c.x));
	mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 10, 860, 0x2EDD17, "c y : ");
	mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 80, 860, 0x2EDD17, ft_ftoa(ftc->c.y));
}

void init_mlx(t_ftc *ftc)
{
	if (!(ftc->mx = (t_mlx *)malloc(sizeof(t_mlx))))
		print_error(1, ftc);
	ftc->mx->mptr = mlx_init();
	ftc->mx->wptr = mlx_new_window(ftc->mx->mptr, WIDTH, HEIGHT + 200, "Fract'ol");
	ftc->mx->iptr = mlx_new_image(ftc->mx->mptr, WIDTH, HEIGHT);
	ftc->mx->data = (int *)mlx_get_data_addr(ftc->mx->iptr, &ftc->mx->bpp, &ftc->mx->size_l, &ftc->mx->endian);
	ftc->pcolors = init_colors();
	ftc->palptr = &ftc->pcolors[0];
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

void	ftc_info(t_ftc *ftc, char *av)
{
	void  (*fractal)(t_ftc *ftc, double, double);

	fractal = NULL;
	if (ft_strcmp("mandelbrot" ,av) == 0)
		fractal = &mandelbrot;
	if (ft_strcmp("burningship" ,av) == 0)
		fractal = &burningship;
	if (ft_strcmp("julia", av) == 0)
		fractal = &julia;
	if (ft_strcmp("julia_4", av) == 0)
		fractal = &julia_4;
	if (ft_strcmp("test", av) == 0)
		fractal = &test;
	if (ft_strcmp("lyapunov", av) == 0)
	{
		fractal = &lyapunov;
		init_lyapu(ftc);
	}
	ftc->fractal = fractal;
	if (!(ftc->fname = ft_strdup(av)))
		print_error(1, ftc);
}

int main(int ac, char **av)
{
	t_ftc *ftc;

	ac != 2 ? print_error(2, NULL) : checkargs(av[1]);
	if (!(ftc = (t_ftc *)malloc(sizeof(t_ftc))))
		print_error(1, NULL);
	init_mlx(ftc);
	ftc_info(ftc, av[1]);
	it_draw(ftc, ftc->fractal);
	mlx_put_image_to_window(ftc->mx->mptr, ftc->mx->wptr, ftc->mx->iptr, 0, 0);
	mlx_key_hook(ftc->mx->wptr, keycode, ftc);
	mlx_mouse_hook(ftc->mx->wptr, mousecode, ftc);
	mlx_hook(ftc->mx->wptr, 6, 3, mousemotion, ftc);
	mlx_loop(ftc->mx->mptr);
	return (0);
}
