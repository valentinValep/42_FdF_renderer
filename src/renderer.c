/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:14:00 by vlepille          #+#    #+#             */
/*   Updated: 2023/04/26 15:07:18 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <mlx.h>
#include <stdlib.h>
#include <math.h>

void	init_projections(t_renderer	*renderer)
{
	renderer->projections[0].name = "Isometric";
	renderer->projections[0].i_hat[0] = cos(M_PI / 6.);
	renderer->projections[0].i_hat[1] = sin(M_PI / 6);
	renderer->projections[0].j_hat[0] = cos(5. * M_PI / 6.);
	renderer->projections[0].j_hat[1] = sin(5. * M_PI / 6.);
	renderer->projections[0].k_hat[0] = 0.;
	renderer->projections[0].k_hat[1] = -1.;
	renderer->projections[1].name = "Military";
	renderer->projections[1].i_hat[0] = 1;
	renderer->projections[1].i_hat[1] = 1;
	renderer->projections[1].j_hat[0] = -1;
	renderer->projections[1].j_hat[1] = 1;
	renderer->projections[1].k_hat[0] = 0.;
	renderer->projections[1].k_hat[1] = -1.;
}

int	init_images(t_renderer	*renderer)
{
	int	i;

	renderer->images.img_offset = 0;
	renderer->images.w = WINDOW_W;
	renderer->images.h = WINDOW_H;
	renderer->images.img[0].addr = mlx_new_image(
			renderer->mlx, renderer->images.w, renderer->images.h);
	if (!renderer->images.img[0].addr)
		return (1);
	renderer->init_step++;
	renderer->images.img[0].pixels = mlx_get_data_addr(
			renderer->images.img[0].addr,
			&renderer->images.img[0].bits_per_pixel,
			&renderer->images.img[0].line_len, &renderer->images.img[0].endian);
	renderer->images.img[1].addr = mlx_new_image(
			renderer->mlx, renderer->images.w, renderer->images.h);
	if (!renderer->images.img[1].addr)
		return (1);
	renderer->init_step++;
	renderer->images.img[1].pixels = mlx_get_data_addr(
			renderer->images.img[1].addr,
			&renderer->images.img[1].bits_per_pixel,
			&renderer->images.img[1].line_len, &renderer->images.img[1].endian);
	renderer->images.drawed_pixels = malloc(
			(renderer->images.w * renderer->images.h) * sizeof(t_pixel));
	if (!renderer->images.drawed_pixels)
		return (1);
	renderer->init_step++;
	i = 0;
	while (i < renderer->images.w * renderer->images.h)
		renderer->images.drawed_pixels[i++].x = -1;
	return (0);
}

int	init_renderer(t_renderer	*renderer)
{
	renderer->init_step = 0;
	renderer->mlx = mlx_init();
	if (!renderer->mlx)
		return ((destroy_renderer(renderer), 1));
	renderer->init_step++;
	renderer->window = mlx_new_window(
			renderer->mlx, WINDOW_W, WINDOW_H, WINDOW_NAME);
	if (!renderer->window)
		return ((destroy_renderer(renderer), 2));
	renderer->init_step++;
	renderer->origin_x = WINDOW_W / 2;
	renderer->origin_y = WINDOW_H / 2;
	init_projections(renderer);
	renderer->projection_select = 0;
	if (init_images(renderer))
		return ((destroy_renderer(renderer), 3));
	return (0);
}

int	destroy_renderer(t_renderer	*renderer)
{
	int	result;

	result = 0;
	if (renderer->init_step > 4)
		free(renderer->images.drawed_pixels);
	if (renderer->init_step > 1)
		result += mlx_destroy_window(renderer->mlx, renderer->window);
	if (renderer->init_step > 2)
		result += mlx_destroy_image(renderer->mlx, renderer->images.img[0].addr);
	if (renderer->init_step > 3)
		result += mlx_destroy_image(renderer->mlx, renderer->images.img[1].addr);
	if (renderer->init_step > 0)
	{
		result += mlx_destroy_display(renderer->mlx);
		free(renderer->mlx);
	}
	return (0);
}

void	swap_projection(t_renderer *renderer)
{
	renderer->projection_select
		= (renderer->projection_select + 1) % PROJECTIONS_NUMBER;
}
