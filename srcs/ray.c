/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:12:28 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/30 20:33:13 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ray_init(t_ray *ray, double rayAngle)
{
	ray->ray_angle = normalize_angle(rayAngle);
	ray->wall_hitX = 0;
	ray->wall_hitY = 0;
	ray->distance = 0;
	ray->wasHit_vertical = FALSE;

	// ray->ray_angle 광선의 진행하는 각도에 따라서 isRay_facing~~를 정해준다.
	// 위왼쪽 위오른쪽 아래왼쪽 아래오른쪽 이렇게 값을 가질수 있는거임
	ray->isRay_facingDown = ray->ray_angle > 0 && ray->ray_angle < M_PI;
	ray->isRay_facingUp = !ray->isRay_facingDown;
	ray->isRay_facingRight = ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI;
	ray->isRay_facingLeft = !ray->isRay_facingRight;
}

// (9)에서 3D화면이 왼쪽으로 압축되서 나와서 RAY_COUNT를  내 생각대로 수정
void	draw_ray(t_god *god)
{
	double angle;
	// double maxAngle; //CFLAGS 때문에 주석처리
	int i;

	i = 0;
	// god->player.rotationAngle 플레이어의 시야각은
	angle = god->player.rotationAngle - (RAY_RANGE / 2.0);
	// maxAngle = god->player.rotationAngle + (RAY_RANGE / 2.0);//CFLAGS 때문에 주석처리

	//(3D기준)화면상 왼쪽부터 오른쪽으로 쭉 그려진다.
	while (i < god->map.ray_count)
	{
		draw_one_ray(god, angle, i);
		angle += RAY_RANGE / god->map.ray_count;
		i++;
	}
}

//2차원 광선 한줄을 그린다.
// dx(플레이어와 벽과의 거리) == {벽과 부딪힌좌표} - {플레이어현재x 좌표}
void	draw_line(t_god *god, double dx, double dy)
{
	double	ray_x;
	double	ray_y;
	int x;
	int y;
	double	max_value;

	ray_x = god->player.x;
	ray_y = god->player.y;
	max_value = fmax(fabs(dx), fabs(dy));
	// 벽에 딱붙으면 거리는 0	dx/0 == 쎄그뻘트
	if (max_value == 0)
		return ;
	dx /= max_value;
	dy /= max_value;
	while (1)
	{
		if (!is_wall(&(god->map), ray_x, ray_y))
		{
			setting_map_location(&(god->map), &x, &y, ray_x, ray_y);
			god->img.data[god->map.window_width * y + x] = RAY_COLOR;
		}
		else
			break;
		ray_x += dx;
		ray_y += dy;
	}
}

void	draw_one_ray(t_god *god, double angle, int i)
{

	t_dpable_ray horz;
	t_dpable_ray vert;
	// double dx;
	// double dy;

	ray_init(&god->ray, angle);
	cal_horz_ray(god, &horz);
	cal_vert_ray(god, &vert);

	// 벽의 수직선들, 수평선들 중에 광선과 만나는 두점이 나옴 수직선과 만나는거 한점 수평선과 만나는거 한점
	// 두개의 점 중에 가까운 점이 벽과 광선ray이 최초로 만나는 지점임
	if (vert.distance < horz.distance)
	{
		god->ray.wall_hitX = vert.wall_hitX;
		god->ray.wall_hitY = vert.wall_hitY;
		god->ray.distance = vert.distance;
		god->ray.wasHit_vertical = TRUE;
	}
	else
	{
		god->ray.wall_hitX = horz.wall_hitX;
		god->ray.wall_hitY = horz.wall_hitY;
		god->ray.distance = horz.distance;
		god->ray.wasHit_vertical = FALSE;
	}
	draw_line(god, god->ray.wall_hitX - god->player.x, god->ray.wall_hitY - god->player.y);
	render_3d_project_walls(god, i);
}

double normalize_angle(double angle)
{
	if (angle >= 0)
	{
		while (angle >= M_PI * 2)
			angle -= M_PI * 2;
	}
	else
	{
		while (angle <= 0)
			angle += M_PI * 2;
	}
	return angle;
}

double distance_between_points(double x1, double y1, double x2, double y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	cal_distance(t_god *god, t_dpable_ray *horz_or_vert)
{
	// printf("horz_or_vert-> distance == %lf \n", horz_or_vert->distance);

	if (horz_or_vert->found_wallHit == TRUE)
		horz_or_vert->distance = distance_between_points(god->player.x, god->player.y, horz_or_vert->wall_hitX, horz_or_vert->wall_hitY);
	else
		horz_or_vert->distance = 999999999999;
		// horz_or_vert->distance = DBL_MAX;
	// 벽을 찾지 못할 경우 수평경계좌표와 수직경계좌표를 비교할때 선택되지 않도록
}

// 실질적으로 벽의 위치를 찾는 함수
// x_adjust, y_adjust는 플레이어가 왼쪽이랑 위쪽 볼때 벽이 밀려서 나타나는 현상이 있이서 값을 보정해주었다.
void	cal_ray(t_god *god, t_dpable_ray *horz_or_vert, int x_adjust, int y_adjust)
{
	double next_touchX;
	double next_touchY;

	next_touchX = horz_or_vert->xintercept;
	next_touchY = horz_or_vert->yintercept;
	while (next_touchX >= 0 && next_touchX <= god->map.window_width && next_touchY >= 0 && next_touchY <= god->map.window_height)
	{
		if (is_wall(&(god->map), next_touchX + x_adjust, next_touchY + y_adjust))
		{
			horz_or_vert->found_wallHit = TRUE;
			horz_or_vert->wall_hitX = next_touchX;
			horz_or_vert->wall_hitY = next_touchY;
			break;
		}
		else
		{
			next_touchX += horz_or_vert->xstep;
			next_touchY += horz_or_vert->ystep;
		}
	}
	cal_distance(god, horz_or_vert);
}

// 양옆으로 쭉 그어진 행모양 기준선
// cal_ray함수에서 벽의위치를 찾는데 쓰일
// xintercept, yintercept, xstep, ystep의 값을 정해줌
void	cal_horz_ray(t_god *god, t_dpable_ray *horz)
{
	horz->found_wallHit = FALSE;
	horz->wall_hitX = 0;
	horz->wall_hitY = 0;

	horz->yintercept = floor(god->player.y  / TILE_SIZE) * TILE_SIZE;
	// 밑에를 보면 타일의 크기만큼 
	horz->yintercept += god->ray.isRay_facingDown ? TILE_SIZE : 0;

	horz->xintercept = god->player.x + (horz->yintercept - god->player.y) / tan(god->ray.ray_angle);

	horz->ystep = TILE_SIZE;
	horz->ystep *= god->ray.isRay_facingUp ? -1 : 1;

	horz->xstep = TILE_SIZE / tan(god->ray.ray_angle);
	horz->xstep *= (god->ray.isRay_facingLeft && horz->xstep > 0) ? -1 : 1;
	horz->xstep *= (god->ray.isRay_facingRight && horz->xstep < 0) ? -1 : 1;

	cal_ray(god, horz, 0, god->ray.isRay_facingUp ? -1 : 0);
}

void cal_vert_ray(t_god *god, t_dpable_ray *vert)
{
	vert->found_wallHit = FALSE;
	vert->wall_hitX = 0;
	vert->wall_hitY = 0;

	vert->xintercept = floor(god->player.x  / TILE_SIZE) * TILE_SIZE;
	vert->xintercept += god->ray.isRay_facingRight ? TILE_SIZE : 0;

	vert->yintercept = god->player.y + (vert->xintercept - god->player.x) * tan(god->ray.ray_angle);

	vert->xstep = TILE_SIZE;
	vert->xstep *= god->ray.isRay_facingLeft ? -1 : 1;

	vert->ystep = TILE_SIZE * tan(god->ray.ray_angle);
	vert->ystep *= (god->ray.isRay_facingUp && vert->ystep > 0) ? -1 : 1;
	vert->ystep *= (god->ray.isRay_facingDown && vert->ystep < 0) ? -1 : 1;

	cal_ray(god, vert, god->ray.isRay_facingLeft ? -1 : 0, 0);
}
