
#include "fractol.h"

void    exit_ftc(t_ftc *ftc)
{
	mlx_destroy_image(ftc->mx->mptr, ftc->mx->iptr);
	mlx_clear_window(ftc->mx->mptr, ftc->mx->wptr);
	mlx_destroy_window(ftc->mx->mptr, ftc->mx->wptr);
	free_fract(ftc);
	exit(0);
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
		ftc->pdx -= ftc->zoom * 0.01f;
	if (key == 124)
		ftc->pdx += ftc->zoom * 0.01f;
	if (key == 125)
		ftc->pdy += ftc->zoom * 0.01f;
	if (key == 126)
		ftc->pdy -= ftc->zoom * 0.01f;
}

int		keycode(int key, t_ftc *ftc)
{
	if (key == 53)
		exit_ftc(ftc);
	if (key == 6 || key == 7)
		ftc->itmax += key == 7 ? 5 : (ftc->itmax > 0) ? -5 : (ft_abs(ftc->itmax) + 2);
	if (key == 69 || key == 78)
		zoom(key, ftc);
	if (key == 125 || key == 126 || key == 123 || key == 124)
		moove(key, ftc);
	if (key >= 18 && key <= 24)
		ftc->palptr = &ftc->pcolors[key - 18];
	redraw(ftc);
	return (0);
}
