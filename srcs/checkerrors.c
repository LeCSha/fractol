/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerrors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:50:01 by abaille           #+#    #+#             */
/*   Updated: 2018/06/25 09:50:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	exit_ftc(t_ftc *ftc)
{
	mlx_destroy_image(ftc->mx->mptr, ftc->mx->iptr);
	mlx_clear_window(ftc->mx->mptr, ftc->mx->wptr);
	mlx_destroy_window(ftc->mx->mptr, ftc->mx->wptr);
	free_fract(ftc);
	exit(0);
}

void	free_fract(t_ftc *ftc)
{
	if (ftc->mx)
		free(ftc->mx);
	if (ftc->pcolors)
		free(ftc->pcolors);
	if (ftc->fname)
		free(ftc->fname);
	if (ftc->seq)
		free(ftc->seq);
	free(ftc);
}

void	checkargs(char *av)
{
	if (ft_strcmp("mandelbrot", av) != 0 &&
	ft_strcmp("burningship", av) != 0 &&
	ft_strcmp("julia", av) != 0 &&
	ft_strcmp("tribrot", av) != 0 &&
	ft_strcmp("lyapunov", av) != 0)
		print_error(2, NULL);
}

void	usage(void)
{
	ft_putstr("\n\n---- USAGE ----\n\n");
	ft_putstr("./fractol [mandelbrot, julia, burningship,");
	ft_putstr(" tribrot, lyapunov]\n\n");
}

void	print_error(int nb, t_ftc *ftc)
{
	if (nb == 1)
		ft_putstr("Problem with allocation memory\n");
	else if (nb == 2)
		usage();
	if (ftc != NULL)
		free_fract(ftc);
	exit(0);
}
