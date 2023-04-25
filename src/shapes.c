/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:14:01 by vlepille          #+#    #+#             */
/*   Updated: 2023/04/25 16:14:02 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stddef.h>
#include <math.h>

void	draw_vector(t_renderer *renderer, t_point p1, t_point p2)
{
	draw_line(renderer, p1,
		(t_point){p2.x + p1.x, p2.y + p1.y, p2.z + p1.z, p1.color});
}

void	draw_cube(t_renderer	*renderer, t_point start, double w)
{
	draw_vector(renderer, start, (t_point){w, 0, 0, start.color});
	draw_vector(renderer, start, (t_point){0, w, 0, start.color});
	draw_vector(renderer, start, (t_point){0, 0, w, start.color});
	draw_vector(renderer, (t_point){start.x + w, start.y, start.z, start.color},
		(t_point){0, 0, w, start.color});
	draw_vector(renderer, (t_point){start.x, start.y + w, start.z, start.color},
		(t_point){0, 0, w, start.color});
	draw_vector(renderer,
		(t_point){start.x + w, start.y + w, start.z, start.color},
		(t_point){0, 0, w, start.color});
	draw_vector(renderer,
		(t_point){start.x + w, start.y, start.z + w, start.color},
		(t_point){0, w, 0, start.color});
	draw_vector(renderer,
		(t_point){start.x, start.y + w, start.z + w, start.color},
		(t_point){w, 0, 0, start.color});
	draw_vector(renderer, (t_point){start.x + w, start.y, start.z, start.color},
		(t_point){0, w, 0, start.color});
	draw_vector(renderer, (t_point){start.x, start.y + w, start.z, start.color},
		(t_point){w, 0, 0, start.color});
	draw_vector(renderer, (t_point){start.x, start.y, start.z + w, start.color},
		(t_point){w, 0, 0, start.color});
	draw_vector(renderer, (t_point){start.x, start.y, start.z + w, start.color},
		(t_point){0, w, 0, start.color});
}

void	put_origins(t_renderer *renderer)
{
	int	i;

	i = 0;
	while (!draw_point(renderer, (t_point){i, 0, 0, 0x00FF0000}))
		i++;
	i = 0;
	while (!draw_point(renderer, (t_point){0, i, 0, 0x0000FF00}))
		i++;
	i = 0;
	while (!draw_point(renderer, (t_point){0, 0, i, 0x000000FF}))
		i++;
}
