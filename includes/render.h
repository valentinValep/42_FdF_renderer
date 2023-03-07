#ifndef RENDER_H
# define RENDER_H

# define WINDOW_W 1920
# define WINDOW_H 1080
# define PROJECTIONS_NUMBER 2
# define _XOPEN_SOURCE 500 // Use for math.h in render.c

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_point;

typedef struct s_pixel
{
	double	depth;
	int		x;
	int		y;
	int		color;
}	t_pixel;

typedef struct s_img
{
	void	*addr;
	char	*pixels;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_double_buffered_img
{
	t_img				img[2];
	int					img_offset;
	int					h;
	int					w;
	t_pixel				*drawed_pixels;
}	t_double_buffered_img;

typedef struct s_projection_matrix
{
	char	*name;
	double	i_hat[2];
	double	j_hat[2];
	double	k_hat[2];
}	t_projection_matrix;

typedef struct s_renderer
{
	t_double_buffered_img	images;
	void					*mlx; // @TODO remove ? (not really a renderer part)
	void					*window;
	t_projection_matrix		projections[PROJECTIONS_NUMBER];
	int						projection_select;
	int						origin_x;
	int						origin_y;
}	t_renderer;

// Private
void	clear_image(t_double_buffered_img *images, int offset);
void	fill_image(t_double_buffered_img *images);
int		put_pixel(t_double_buffered_img *images, t_pixel pixel);
t_pixel	project(t_renderer *renderer, t_point point);

// Public
int		init_renderer(t_renderer	*renderer)
		__attribute__((warn_unused_result));
int		destroy_renderer(t_renderer	*renderer);
void	render_tick(t_renderer *renderer);
void	clear_renderer(t_renderer	*renderer);

int		draw_point(t_renderer	*renderer, t_point point);
void	put_origins(t_renderer	*renderer);
void	draw_cube(t_renderer	*renderer, t_point start, double w);
void	draw_line(t_renderer	*renderer, t_point p1, t_point p2);

void	swap_projection(t_renderer *renderer);

#endif