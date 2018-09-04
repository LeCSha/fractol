
#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>
# include <limits.h>
# include "mlx.h"
# include "libft.h"
# include <pthread.h>

# define WIDTH 1000
# define HEIGHT 1000
# define KEY_1	18
# define KEY_2	19
# define KEY_3	20
# define KEY_4	21
# define KEY_5	22
# define KEY_6	23
# define KEY_NUM1	83
# define KEY_NUM2	84
# define KEY_NUM3	85
# define KEY_NUM4	86
# define KEY_NUM5	87
# define SCROLL_UP		4
# define SCROLL_DOWN	5
# define RIGHT_CLICK	2
# define LEFT_CLICK		1
# define KEY_UP     126
# define KEY_DOWN	125
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define T_TH1 ftc->th1.thread
# define T_TH2 ftc->th2.thread
# define T_TH3 ftc->th3.thread
# define T_TH4 ftc->th4.thread

typedef struct  s_cpx   t_cpx;
typedef struct  s_rgb   t_rgb;
typedef struct  s_mlx   t_mlx;
typedef struct  s_ftc   t_ftc;
typedef struct  s_pal   t_pal;
typedef struct  s_thr   t_thr;

struct  s_cpx
{
	double  x;
	double  y;
};

struct	s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
};

struct  s_pal
{
	int size;
	int c[5];
};

struct	s_thr
{
	int			nb;
	t_ftc		*ftc;
	pthread_t	thread;
};

struct	s_mlx
{
	void	*mptr;
	void	*wptr;
	void	*iptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
};

struct  s_ftc
{
	t_cpx   start;
	t_cpx   end;
	t_cpx   c;
	t_mlx   *mx;
	t_pal   *pcolors;
	t_pal   *palptr;
	t_thr	th1;
	t_thr	th2;
	t_thr	th3;
	t_thr	th4;
	char    *fname;
	char    *seq;
	double  zoom;
	int     itmax;
	double  pdx;
	double  pdy;
	double  imgx;
	double  imgy;
	int     stpmov;
	void    (*fractal)(t_ftc *ftc, double, double);
};

int		keycode(int key, t_ftc *ftc);
int		mousemotion(int x, int y, t_ftc *ftc);
int		mousecode(int button, int x, int y, t_ftc *ftc);
int		change_seqlyapu(t_ftc *ftc);

void 	mandelbrot(t_ftc *ftc, double x, double y);
void 	julia(t_ftc *ftc, double x, double y);
void 	burningship(t_ftc *ftc, double x, double y);
void	tribrot(t_ftc *ftc, double x, double y);
void	init_lyapu(t_ftc *ftc);
void	lyapunov(t_ftc *ftc, double x, double y);

int		init_thread(t_ftc *ftc);

void	string_put(t_ftc *ftc);

void	it_draw(t_ftc *ftc, void (func)(t_ftc *, double, double), int line);
void	draw_fractal(t_ftc *ftc, int x, int y, int color);
void	redraw(t_ftc *ftc);

void	print_error(int nb, t_ftc *ftc);
void	checkargs(char *av);
void	free_fract(t_ftc *ftc);
void	exit_ftc(t_ftc *ftc);
void	reset(t_ftc *ftc);

t_pal	*init_colors(void);
int		smoothcolor(t_ftc *ftc, double i, t_cpx z);
#endif
