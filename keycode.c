
#include "fractol.h"

void free_fract(t_ftc *ftc)
{
	free(ftc->mx);
	free(ftc);
}

void    exit_ftc(t_ftc *ftc)
{
	mlx_destroy_image(ftc->mx->mptr, ftc->mx->iptr);
	mlx_clear_window(ftc->mx->mptr, ftc->mx->wptr);
	mlx_destroy_window(ftc->mx->mptr, ftc->mx->wptr);
	free_fract(ftc);
	exit(0);
}

void zoom(int key, t_ftc *ftc)
{
	double oldw;
	double oldy;
	double neww;
	double newy;

	oldw = (ftc->end.x - ftc->start.x) * ftc->zoom;
	oldy = (ftc->end.y - ftc->start.y) * ftc->zoom;
	ftc->zoom = (key == 69) ? ftc->zoom * (1 / 1.1f) : ftc->zoom * 1.1f;
	neww = (ftc->end.x - ftc->start.x) * ftc->zoom;
	newy = (ftc->end.y - ftc->start.y) * ftc->zoom;
	ftc->zoox -= ((double)WIDTH / 2 / WIDTH) * (neww - oldw);
	ftc->zooy -= ((double)HEIGHT / 2 / HEIGHT) * (newy - oldy);


}

int keycode(int key, t_ftc *ftc)
{
	if (key == 53)
		exit_ftc(ftc);
	if (key == 116 || key == 121)
		ftc->itmax += key == 116 ? 5 : (ftc->itmax > 0) ? -5 : (ft_abs(ftc->itmax) + 2);
	if (key == 69 || key == 78)
		zoom(key, ftc);
	mlx_clear_window(ftc->mx->mptr, ftc->mx->wptr);
	string_put(ftc);
	mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 200, 830, 0x2EDD17, "pos x : ");
	mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 270, 830, 0x2EDD17, ft_ftoa(ftc->start.x));
	mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 200, 860, 0x2EDD17, "pos y : ");
	mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 270, 860, 0x2EDD17, ft_ftoa(ftc->start.y));
	it_draw(ftc, ftc->func);
	mlx_put_image_to_window(ftc->mx->mptr, ftc->mx->wptr, ftc->mx->iptr, 0, 0);
	return (0);
}
