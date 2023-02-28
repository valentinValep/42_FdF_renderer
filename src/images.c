#include "render.h"
#include <mlx.h>

int	put_pixel(t_double_buffered_img *images, t_pixel pixel)
{
	int	i;

	i = 0;
	if (pixel.x < 0 || pixel.x >= images->w
		|| pixel.y < 0 || pixel.y >= images->h)
		return (1);
	while (i < images->w
		&& images->drawed_pixels[i + pixel.y * images->w].x != -1
		&& (images->drawed_pixels[i + pixel.y * images->w].x != pixel.x
			|| images->drawed_pixels[i + pixel.y * images->w].y != pixel.y))
		i++;
	if (images->drawed_pixels[i + pixel.y * images->w].x != -1)
	{
		if (pixel.depth <= images->drawed_pixels[i + pixel.y * images->w].depth)
			return (0);
	}
	else
		if (i < images->w - 1)
			images->drawed_pixels[i + pixel.y * images->w + 1].x = -1;
	images->drawed_pixels[i + pixel.y * images->w].x = pixel.x;
	images->drawed_pixels[i + pixel.y * images->w].y = pixel.y;
	images->drawed_pixels[i + pixel.y * images->w].depth = pixel.depth;
	images->drawed_pixels[i + pixel.y * images->w].color = pixel.color;
	return (0);
}

void	clear_image(t_double_buffered_img *images, int offset)
{
	int	i;
	int	line;

	line = 0;
	while (line < images->h)
	{
		i = 0;
		while (images->drawed_pixels[i + line * images->w].x != -1)
		{
			((int *)images->img[offset].pixels)[images->drawed_pixels[i + line * images->w].x % images->w
				+ images->drawed_pixels[i + line * images->w].y * images->w] = 0;
			i++;
		}
		line++;
	}
}

void	fill_image(t_double_buffered_img *images)
{
	int	i;
	int	line;

	line = 0;
	while (line < images->h)
	{
		i = 0;
		while (images->drawed_pixels[i + line * images->w].x != -1)
		{
			((int *)images->img[images->img_offset].pixels)[images->drawed_pixels[i + line * images->w].x % images->w
				+ images->drawed_pixels[i + line * images->w].y * images->w] = images->drawed_pixels[i + line * images->w].color;
			i++;
		}
		line++;
	}
}

void	clear_renderer(t_renderer	*renderer)
{
	int	line;

	renderer->images.img_offset = (renderer->images.img_offset + 1) % 2;
	clear_image(&renderer->images, renderer->images.img_offset);
	line = 0;
	while (line < renderer->images.h)
	{
		renderer->images.drawed_pixels[line * renderer->images.w].x = -1;
		line++;
	}
}
