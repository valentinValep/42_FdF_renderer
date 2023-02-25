#include "render.h"
#include <mlx.h>

void	put_pixel(t_double_buffered_img	*images, t_pixel pixel)
{
	int	i;

	i = 0;
	while (images->drawed_pixels[i].x != -1
		&& (images->drawed_pixels[i].x != pixel.x
			|| images->drawed_pixels[i].y != pixel.y))
		i++;
	if (images->drawed_pixels[i].x != -1)
	{
		if (pixel.depth <= images->drawed_pixels[i].depth)
			return ;
	}
	else
		images->drawed_pixels[i + 1].x = -1;
	images->drawed_pixels[i].x = pixel.x;
	images->drawed_pixels[i].y = pixel.y;
	images->drawed_pixels[i].depth = pixel.depth;
	images->drawed_pixels[i].color = pixel.color;
}

void	clear_image(t_double_buffered_img *images, int offset)
{
	int	i;

	i = 0;
	while (images->drawed_pixels[i].x != -1)
	{
		((int *)images->img[offset].pixels)[images->drawed_pixels[i].x % images->w
			+ images->drawed_pixels[i].y * images->w] = 0;
		i++;
	}
}

void	fill_image(t_double_buffered_img *images)
{
	int	i;

	i = 0;
	while (images->drawed_pixels[i].x != -1)
	{
		((int *)images->img[images->img_offset].pixels)[images->drawed_pixels[i].x % images->w
			+ images->drawed_pixels[i].y * images->w] = images->drawed_pixels[i].color;
		i++;
	}
}

int	clear_renderer(t_renderer	*renderer)
{
	renderer->images.drawed_pixels[0].x = -1;
}
