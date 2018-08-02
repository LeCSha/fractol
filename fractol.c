#include "fractol.h"

void print_error(int nb, t_ftc *ftc)
{
  if (nb == 1)
    ft_putstr("Problem with allocation memory\n");
  else if (nb == 2)
    ft_putstr("Map not valid\n");
  else if (nb == 3)
    ft_putstr("Problem reading file/allocation failed\n");
  else if (nb == 4)
    ft_putstr("Map size not valid/no value\n");
  else if (nb == 5)
    ftc = NULL;
    // fdf_usage();
  exit(0);
}

void string_put(t_ftc *ftc)
{
  mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 10, 810, 0x2EDD17, *ftc->fname);
  mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 10, 830, 0x2EDD17, "c x : ");
  mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 80, 830, 0x2EDD17, ft_ftoa(ftc->c.x));
  mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 10, 860, 0x2EDD17, "c y : ");
  mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 80, 860, 0x2EDD17, ft_ftoa(ftc->c.y));

  // mlx_string_put(ftc->mx->mptr, ftc->mx->wptr, 10, 810, 0x2EDD17, *ftc->fname);
}

void init_mlx(t_ftc *ftc)
{
  if (!(ftc->mx = (t_mlx *)malloc(sizeof(t_mlx))))
    print_error(1, ftc);
  ftc->mx->mptr = mlx_init();
  ftc->mx->wptr = mlx_new_window(ftc->mx->mptr, WIDTH, HEIGHT + 200, "Fract'ol");
  ftc->mx->iptr = mlx_new_image(ftc->mx->mptr, WIDTH, HEIGHT);
  ftc->mx->data = (int *)mlx_get_data_addr(ftc->mx->iptr, &ftc->mx->bpp, &ftc->mx->size_l, &ftc->mx->endian);
  ftc->itmax = 50;
  ftc->zoom = 1.0f;
  ftc->stpmov = 5;
  ftc->c.x = 0;
  ftc->c.y = 0;
  ftc->start.x = -2.0f;
  ftc->end.x = 2.0f;
  ftc->start.y = -2.0f;
  ftc->end.y = 2.0f;
  ftc->zoox = 0;
  ftc->zooy = 0;
}

void draw_fractal(t_ftc *ftc, int x, int y, int color)
{
  ftc->mx->data[y * WIDTH + x] = color;
}

void mandelbrot(t_ftc *ftc, double x, double y)
{
  double i;
  double tmp;

  ftc->c.x = ((double)x / WIDTH) * (ftc->end.x - ftc->start.x)
  * ftc->zoom + ftc->start.x + ftc->zoox;
  ftc->c.y = ((double)y / HEIGHT) * (ftc->end.y - ftc->start.y)
  * ftc->zoom + ftc->start.y + ftc->zooy;
  ftc->z.x = 0;
  ftc->z.y = 0;
  i = 0;
  while (ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y < 4 && i < ftc->itmax)
  {
    tmp = ftc->z.x;
    ftc->z.x = tmp * tmp - ftc->z.y * ftc->z.y + ftc->c.x;
    ftc->z.y = 2 * tmp * ftc->z.y + ftc->c.y;
    i++;
  }
  if (i == ftc->itmax)
    // mlx_pixel_put(ftc->mx->mptr, ftc->mx->wptr, x, y, 0x000000);
    draw_fractal(ftc, x, y, 0x000000);
  else
  {
    // i = i - log(log(sqrt(ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.x))) / log(2);
    // mlx_pixel_put(ftc->mx->mptr, ftc->mx->wptr, x, y, i * (0xFF0000 / ftc->itmax) / 50);
    // i = i + 1 - log(log(fabs(ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.x))) / log(2);
    // mlx_pixel_put(ftc->mx->mptr, ftc->mx->wptr, x, y, (int)(i * 0x84742d / ftc->itmax) >> 16);
    i = i - log(log(sqrt(ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y))) + 4;
    // mlx_pixel_put(ftc->mx->mptr, ftc->mx->wptr, x, y, i * 0x84742d / ftc->itmax);
    draw_fractal(ftc, x, y, i * i);
    // draw_fractal(ftc, x, y, i * (0x84742d / ftc->itmax) / 50);
  }
}

void julia(t_ftc *ftc, double x, double y)
{
  double i;
  double tmp;

  ftc->z.x = ((double)x / WIDTH) * (ftc->end.x - ftc->start.x)
  * ftc->zoom + ftc->start.x + ftc->zoox;
  ftc->z.y = ((double)y / HEIGHT) * (ftc->end.y - ftc->start.y)
  * ftc->zoom + ftc->start.y + ftc->zooy;
  i = 0;
  while ((ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y) < 4 && i < ftc->itmax)
  {
    tmp = ftc->z.x;
    ftc->z.x = ftc->z.x * ftc->z.x - ftc->z.y * ftc->z.y + ftc->c.x;
    ftc->z.y = 2 * tmp * ftc->z.y + ftc->c.y;
    i++;
  }
  if (i == ftc->itmax)
    draw_fractal(ftc, x, y, 0x000000);
  else
  {
    i = i - log(log(sqrt(ftc->z.x * ftc->z.x + ftc->z.y * ftc->z.y))) + 4;
    draw_fractal(ftc, x, y, i * i);
  }
}

void it_draw(t_ftc *ftc, void (func)(t_ftc *, double, double))
{
  double x;
  double y;

  y = 0;
  while (y < HEIGHT)
  {
    x = 0;
    while (x < WIDTH)
    {
      func(ftc, x, y);
      x++;
    }
    y++;
  }
}

int main(int ac, char **av)
{
  t_ftc *ftc;
  void  (*func)(t_ftc *ftc, double, double);

  func = NULL;
  if (!(ftc = (t_ftc *)malloc(sizeof(t_ftc))))
    print_error(1, ftc);
  init_mlx(ftc);
  if (ac < 1)
    return (0);
  if (ft_strcmp("mandelbrot" ,av[1]) == 0)
    func = &mandelbrot;
  if (ft_strcmp("julia", av[1]) == 0)
    func = &julia;
  ftc->func = func;
  ftc->fname = &av[1];
  it_draw(ftc, ftc->func);
  mlx_put_image_to_window(ftc->mx->mptr, ftc->mx->wptr, ftc->mx->iptr, 0, 0);
  mlx_key_hook(ftc->mx->wptr, keycode, ftc);
  mlx_mouse_hook(ftc->mx->wptr, mousecode, ftc);
  mlx_hook(ftc->mx->wptr, 6, 3, mousemotion, ftc);
  mlx_loop(ftc->mx->mptr);
  return (0);
}
