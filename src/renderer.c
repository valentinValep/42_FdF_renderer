#include "render.h"
#include <mlx.h>
#include <stdlib.h>
#include <math.h>

void	init_projections(t_renderer	*renderer)
{
	renderer->projections[0].name = "Isometric"; // @TODO verif this string is not delete
	renderer->projections[0].i_hat[0] = cos(M_PI / 6.);
	renderer->projections[0].i_hat[1] = sin(M_PI / 6);
	renderer->projections[0].j_hat[0] = cos(5. * M_PI / 6.);
	renderer->projections[0].j_hat[1] = sin(5. * M_PI / 6.);
	renderer->projections[0].k_hat[0] = 0.;
	renderer->projections[0].k_hat[1] = -1. * renderer->height_factor;
	renderer->projections[1].name = "Military"; // @TODO verif this string is not delete
	renderer->projections[1].i_hat[0] = 1;
	renderer->projections[1].i_hat[1] = 1;
	renderer->projections[1].j_hat[0] = -1;
	renderer->projections[1].j_hat[1] = 1;
	renderer->projections[1].k_hat[0] = 0.;
	renderer->projections[1].k_hat[1] = -1. * renderer->height_factor;
}

int	init_images(t_renderer	*renderer)
{
	int	i;

	renderer->images.img_offset = 0;
	renderer->images.w = WINDOW_W;
	renderer->images.h = WINDOW_H;
	renderer->images.img[0].addr = mlx_new_image(renderer->mlx, renderer->images.w, renderer->images.h);
	renderer->images.img[0].pixels = mlx_get_data_addr(
			renderer->images.img[0].addr, &renderer->images.img[0].bits_per_pixel,
			&renderer->images.img[0].line_len, &renderer->images.img[0].endian);
	renderer->images.img[1].addr = mlx_new_image(renderer->mlx, renderer->images.w, renderer->images.h);
	renderer->images.img[1].pixels = mlx_get_data_addr(
			renderer->images.img[1].addr, &renderer->images.img[1].bits_per_pixel,
			&renderer->images.img[1].line_len, &renderer->images.img[1].endian);
	renderer->images.drawed_pixels = malloc((renderer->images.w * renderer->images.h) * sizeof(t_pixel));
	if (!renderer->images.drawed_pixels)
		return (1);
	i = 0;
	while (i < renderer->images.w * renderer->images.h)
		renderer->images.drawed_pixels[i++].x = -1;
	return (0);
}

int	init_renderer(t_renderer	*renderer)
{
	renderer->mlx = mlx_init();
	renderer->window = mlx_new_window(renderer->mlx, WINDOW_W, WINDOW_H, "Test isometrique"); // @TODO custom window name
	renderer->origin_x = WINDOW_W / 2;
	renderer->origin_y = WINDOW_H / 2;
	renderer->height_factor = 0.1;
	init_projections(renderer);
	renderer->projection_select = 0;
	if (init_images(renderer))
		return (1);
	return (0);
}

int	destroy_renderer(t_renderer	*renderer)
{
	int	result;

	result = 0;
	free(renderer->images.drawed_pixels);
	result += mlx_destroy_window(renderer->mlx, renderer->window);
	result += mlx_destroy_image(renderer->mlx, renderer->images.img[0].addr);
	result += mlx_destroy_image(renderer->mlx, renderer->images.img[1].addr);
	result += mlx_destroy_display(renderer->mlx);
	free(renderer->mlx);
	return (0);
}

void	swap_projection(t_renderer *renderer)
{
	renderer->projection_select
		= (renderer->projection_select + 1) % PROJECTIONS_NUMBER;
}
