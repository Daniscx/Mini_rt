/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/22 12:12:37 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"
#include "../includes/messages.h"

int	is_autorepeat_release(t_minirt *rt, int keycode)
{
	Display	*display;
	XEvent	next;

	display = ((t_xvar *)rt->mlx)->display;
	if (XPending(display))
	{
		XPeekEvent(display, &next);
		if (next.type == KeyPress && next.xkey.keycode == (unsigned int)keycode)
			return (1);
	}
	return (0);
}

int	close_handler(t_minirt *rt)
{
	minirt_cleanup(rt);
	printf("%s", SD_PROTOCOL);
	exit(EXIT_SUCCESS);
}

int	expose_handler(t_minirt *rt)
{
	if (rt->high_res_mode && rt->img_high.img_ptr)
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img_high.img_ptr, 0, 0);
	else if (rt->img.img_ptr)
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img_ptr, 0, 0);
	return (0);
}


