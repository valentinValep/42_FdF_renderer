#include "render.h"
#include <stddef.h>

double	max(double *tab, size_t size)
{
	size_t	i;
	double	max;

	if (!size)
		return (0.);
	i = 1;
	max = tab[0];
	while (i < size)
	{
		if (max < tab[i])
			max = tab[i];
		i++;
	}
	return (max);
}

void	draw_line(t_renderer	*renderer, t_point p1, t_point p2)
{
	int		i;
	double	x;
	double	y;
	double	z;
	double	m;

	x = p1.x;
	y = p1.y;
	z = p1.z;
	i = 0;
	m = max((double []){
			(p2.x - p1.x) *((p2.x - p1.x > 0) * 2 - 1),
			(p2.y - p1.y) * ((p2.y - p1.y > 0) * 2 - 1),
			(p2.z - p1.z) * ((p2.z - p1.z > 0) * 2 - 1)},
			3);
	while (i < m)
	{
		draw_point(renderer, (t_point){x, y, z, p1.color});
		x += (p2.x - p1.x) / m;
		y += (p2.x - p1.x) / m;
		z += (p2.x - p1.x) / m;
		i++;
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
