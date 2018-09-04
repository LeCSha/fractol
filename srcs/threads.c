/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:51:57 by abaille           #+#    #+#             */
/*   Updated: 2018/09/01 17:52:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*launch_thread(void *arg)
{
	t_thr	*tmp;

	tmp = (t_thr *)arg;
	it_draw(tmp->ftc, tmp->ftc->fractal, tmp->nb);
	pthread_exit(NULL);
}

void	set_thread(t_ftc *ftc)
{
	ftc->th1.ftc = ftc;
	ftc->th2.ftc = ftc;
	ftc->th3.ftc = ftc;
	ftc->th4.ftc = ftc;
	ftc->th1.nb = 1;
	ftc->th2.nb = 2;
	ftc->th3.nb = 3;
	ftc->th4.nb = 4;
}

int		init_thread(t_ftc *ftc)
{
	set_thread(ftc);
	if (pthread_create(&T_TH1, NULL, launch_thread, &(ftc->th1)))
		print_error(1, ftc);
	if (pthread_create(&T_TH2, NULL, launch_thread, &(ftc->th2)))
		print_error(1, ftc);
	if (pthread_create(&T_TH3, NULL, launch_thread, &(ftc->th3)))
		print_error(1, ftc);
	if (pthread_create(&T_TH4, NULL, launch_thread, &(ftc->th4)))
		print_error(1, ftc);
	if (pthread_join(T_TH1, NULL))
		print_error(1, ftc);
	if (pthread_join(T_TH2, NULL))
		print_error(1, ftc);
	if (pthread_join(T_TH3, NULL))
		print_error(1, ftc);
	if (pthread_join(T_TH4, NULL))
		print_error(1, ftc);
	return (0);
}
