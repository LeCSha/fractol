
#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>
# include <limits.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

# define WIDTH 800
# define HEIGHT 800

typedef struct  s_cpx   t_cpx;
typedef struct  s_rgb   t_rgb;
typedef struct  s_mlx   t_mlx;
typedef struct  s_ftc   t_ftc;

struct  s_cpx
{
  double  x;
  double  y;
};

struct  s_rgb
{
  double r;
  double g;
  double b;
};

struct  s_mlx
{
  void   *mptr;
  void   *wptr;
	void   *iptr;
	int    *data;
	int    size_l;
	int    bpp;
	int    endian;
};

struct  s_ftc
{
  t_cpx   start;
  t_cpx   end;
  t_cpx   c;
  t_cpx   z;
  t_mlx   *mx;
  char    *fname;
  char    *lyapu;
  double  zoom;
  int  itmax;
  double  pdx;
  double  pdy;
  double  imgx;
  double  imgy;
  int     stpmov;
  void    (*fractal)(t_ftc *ftc, double, double);
};

int   keycode(int key, t_ftc *ftc);
int   mousemotion(int x, int y, t_ftc *ftc);
int   mousecode(int button, int x, int y, t_ftc *ftc);

void  mandelbrot(t_ftc *ftc, double x, double y);
void  julia(t_ftc *ftc, double x, double y);
void  mandel_tri(t_ftc *ftc, double x, double y);
void  julia5(t_ftc *ftc, double x, double y);
void	init_lyapu(t_ftc *ftc, double x, double y);
void	lyapunov(t_ftc *ftc, double x, double y);
void  burningship(t_ftc *ftc, double x, double y);

void  string_put(t_ftc *ftc);

void  it_draw(t_ftc *ftc, void (func)(t_ftc *, double, double));
void  draw_fractal(t_ftc *ftc, int x, int y, int color);
void  redraw(t_ftc *ftc);
void  print_error(int nb, t_ftc *ftc);

#endif
