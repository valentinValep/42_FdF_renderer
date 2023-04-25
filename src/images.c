#include "render.h"
#include <mlx.h>

int	put_pixel(t_double_buffered_img *images, t_pixel pixel)
{
	int	i;

	if (pixel.x < 0 || pixel.x >= images->w
		|| pixel.y < 0 || pixel.y >= images->h)
		return (1);
	i = 0;
	if (images->drawed_pixels[pixel.x + pixel.y * images->w].x != -1)
	{
		if (pixel.depth
			<= images->drawed_pixels[pixel.x + pixel.y * images->w].depth)
			return (0);
	}
	images->drawed_pixels[pixel.x + pixel.y * images->w].x = pixel.x;
	images->drawed_pixels[pixel.x + pixel.y * images->w].y = pixel.y;
	images->drawed_pixels[pixel.x + pixel.y * images->w].depth = pixel.depth;
	images->drawed_pixels[pixel.x + pixel.y * images->w].color = pixel.color;
	return (0);
}

void	clear_image(t_double_buffered_img *images, int offset)
{
	int	i;

	i = 0;
	while (i < images->h * images->w)
	{
		if (images->drawed_pixels[i].x != -1)
			((int *)images->img[offset].pixels)[images->drawed_pixels[i].x
				+ images->drawed_pixels[i].y * images->w] = 0;
		i++;
	}
}

void	fill_image(t_double_buffered_img *images)
{
	int	i;

	i = 0;
	while (i < images->h * images->w)
	{
		if (images->drawed_pixels[i].x != -1)
			((int *)images->img[images->img_offset].pixels)
			[images->drawed_pixels[i].x
				+ images->drawed_pixels[i].y * images->w]
				= images->drawed_pixels[i].color;
		i++;
	}
}

void	clear_renderer(t_renderer	*renderer)
{
	int	i;

	renderer->images.img_offset = (renderer->images.img_offset + 1) % 2;
	clear_image(&renderer->images, renderer->images.img_offset);
	i = 0;
	while (i < renderer->images.h * renderer->images.w)
	{
		renderer->images.drawed_pixels[i].x = -1;
		i++;
	}
}
