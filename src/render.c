#include "render.h"
#include <mlx.h>

t_pixel	project(t_renderer	*renderer, t_point point)
{
	int const	pixel_x
		= point.x * renderer->projections[renderer->projection_select].i_hat[0]
		+ point.y * renderer->projections[renderer->projection_select].j_hat[0]
		+ point.z * renderer->projections[renderer->projection_select].k_hat[0]
		+ renderer->origin_x;
	int const	pixel_y
		= point.x * renderer->projections[renderer->projection_select].i_hat[1]
		+ point.y * renderer->projections[renderer->projection_select].j_hat[1]
		+ point.z * renderer->projections[renderer->projection_select].k_hat[1]
		+ renderer->origin_y;

	return (
		(t_pixel){
		point.x + point.y + point.z,
		pixel_x,
		pixel_y,
		point.color
	});
}

int	draw_point(t_renderer *renderer, t_point point)
{
	return (put_pixel(&renderer->images, project(renderer, point)));
}

void	render_tick(t_renderer *renderer)
{
	fill_image(&renderer->images);
	mlx_put_image_to_window(renderer->mlx, renderer->window, renderer->images.img[renderer->images.img_offset].addr, 0, 0);
	renderer->images.img_offset = (renderer->images.img_offset + 1) % 2;
	clear_image(&renderer->images, renderer->images.img_offset);
}
