
#include "fractol.h"

int mousemotion(int x, int y, t_ftc *ftc)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT && ftc->stpmov > 0)
	{
		ftc->c.x = (double)x / (double)WIDTH * 4 - 2;
		ftc->c.y = (double)y / (double)HEIGHT * 4 - 2;
		redraw(ftc);
	}
	return (1);
}

void zoomouse(int button, int x, int y, t_ftc *ftc)
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
	ftc->pdx -= x / WIDTH * (neww - oldw);
	ftc->pdy -= y / HEIGHT * (newy - oldy);
}

void	zoomlyapu(int button, int x, int y, t_ftc *ftc)
{
	double r;
	double i;
	double im;
	double re;

	im = ftc->zoom * 2;
	re = im * WIDTH / HEIGHT;
	r = ftc->z.x / 2 + re * x / WIDTH;
	i = ftc->z.y / 2 + im * (HEIGHT - y) / HEIGHT;
	ftc->zoom = (button == 5) ? ftc->zoom * (1 / 1.1f) : ftc->zoom * 1.1f;
	im = ftc->zoom * 2;
	re = im * WIDTH / HEIGHT;
	ftc->z.x = re / 2 - re * x / WIDTH + r;
	ftc->z.y = im / 2 - im * (HEIGHT - y) / HEIGHT + i;
	ftc->imgy = ftc->zoom * 2;
	ftc->imgx = ftc->imgy * WIDTH / HEIGHT;
	lyapunov(ftc, 0, 0);
}

int   mousecode(int button, int x, int y, t_ftc *ftc)
{
	if ((button == 4 || button == 5) && ft_strcmp("Lyapunov", ftc->fname) != 0 )
		zoomouse(button, x, y, ftc);
	else
		zoomlyapu(button, x, y, ftc);
	if (button == 1 || button == 2)
		ftc->stpmov = (button == 2) ? 1 : 0;
	redraw(ftc);
	return (1);
}
