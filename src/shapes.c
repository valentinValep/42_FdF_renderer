#include "render.h"
#include <stddef.h>
#include <math.h>

//static double	get_distance(t_point p1, t_point p2)
//{
//	double	res;

//	res = 0;
//	res += (p1.x - p2.x) * (p1.x - p2.x);
//	res += (p1.y - p2.y) * (p1.y - p2.y);
//	res += (p1.z - p2.z) * (p1.z - p2.z);
//	return (sqrt(res));
//}

//void	draw_line(t_renderer	*renderer, t_point p1, t_point p2)
//{
//	int		i;
//	double	x;
//	double	y;
//	double	z;
//	double	d;

//	x = p1.x;
//	y = p1.y;
//	z = p1.z;
//	i = 0;
//	d = get_distance(p1, p2);
//	while (i < d)
//	{
//		draw_point(renderer, (t_point){x, y, z, p1.color});
//		x += (p2.x - p1.x) / d;
//		y += (p2.y - p1.y) / d;
//		z += (p2.z - p1.z) / d;
//		i++;
//	}
//}

void	draw_line(t_renderer	*renderer, t_point p1, t_point p2)
{
	const t_pixel	pix_1 = project(renderer, p1);
	const t_pixel	pix_2 = project(renderer, p2);
	t_pixel			pix_current;
	int				dx;
	int				dy;
	int				p;

	pix_current.color = pix_1.color;
	pix_current.depth = pix_1.depth;
	pix_current.x = pix_1.x;
	pix_current.y = pix_1.y;
	dx = (pix_2.x - pix_1.x) * ((pix_2.x - pix_1.x > 0) * 2 - 1);
	dy = (pix_2.y - pix_1.y) * ((pix_2.y - pix_1.y > 0) * 2 - 1);
	p = 2 * dy - dx;
	while (pix_current.x <= pix_2.x)
	{
		put_pixel(&renderer->images, pix_current);
		pix_current.x++;
		if (p < 0)
			p += 2 * dy;
		else
		{
			pix_current.y++;
			p += 2 * (dy - dx);
		}
	}
}

void	draw_cube(t_renderer	*renderer, t_point start, double w)
{
	draw_line(renderer, start, (t_point){w, 0, 0, start.color});
	draw_line(renderer, start, (t_point){0, w, 0, start.color});
	draw_line(renderer, start, (t_point){0, 0, w, start.color});
	draw_line(renderer, (t_point){start.x + w, start.y, start.z, start.color},
		(t_point){0, 0, w, start.color});
	draw_line(renderer, (t_point){start.x, start.y + w, start.z, start.color},
		(t_point){0, 0, w, start.color});
	draw_line(renderer, (t_point){start.x + w, start.y + w, start.z, start.color},
		(t_point){0, 0, w, start.color});
	draw_line(renderer, (t_point){start.x + w, start.y, start.z + w, start.color},
		(t_point){0, w, 0, start.color});
	draw_line(renderer, (t_point){start.x, start.y + w, start.z + w, start.color},
		(t_point){w, 0, 0, start.color});
	draw_line(renderer, (t_point){start.x + w, start.y, start.z, start.color},
		(t_point){0, w, 0, start.color});
	draw_line(renderer, (t_point){start.x, start.y + w, start.z, start.color},
		(t_point){w, 0, 0, start.color});
	draw_line(renderer, (t_point){start.x, start.y, start.z + w, start.color},
		(t_point){w, 0, 0, start.color});
	draw_line(renderer, (t_point){start.x, start.y, start.z + w, start.color},
		(t_point){0, w, 0, start.color});
}

void	put_origins(t_renderer	*renderer)
{
	int	i;

	i = 0;
	while (draw_point(renderer, (t_point){i, 0, 0, 0x00FF0000}))
		i++;
	i = 0;
	while (draw_point(renderer, (t_point){0, i, 0, 0x0000FF00}))
		i++;
	i = 0;
	while (draw_point(renderer, (t_point){0, 0, i, 0x000000FF}))
		i++;
}
