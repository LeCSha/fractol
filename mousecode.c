
#include "fractol.h"

int mousemotion(int x, int y, t_ftc *ftc)
{
  if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT && ftc->stpmov > 0)
  {
    ftc->c.x = (double)x / (double)WIDTH * 4 - 2;
    ftc->c.y = (double)y / (double)HEIGHT * 4 - 2;
  	mlx_clear_window(ftc->mx->mptr, ftc->mx->wptr);
    string_put(ftc);
    it_draw(ftc, ftc->func);
    mlx_put_image_to_window(ftc->mx->mptr, ftc->mx->wptr, ftc->mx->iptr, 0, 0);
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
  ftc->zoox -= ((double)x / WIDTH) * (neww - oldw);
  ftc->zooy -= ((double)y / HEIGHT) * (newy - oldy);
}

int   mousecode(int button, int x, int y, t_ftc *ftc)
{
  if (button == 4 || button == 5)
    zoomouse(button, x, y, ftc);
  if (button == 1 || button == 2)
		ftc->stpmov = (button == 2) ? 1 : 0;
  mlx_clear_window(ftc->mx->mptr, ftc->mx->wptr);
	string_put(ftc);

	it_draw(ftc, ftc->func);
	mlx_put_image_to_window(ftc->mx->mptr, ftc->mx->wptr, ftc->mx->iptr, 0, 0);
  return (1);
}
