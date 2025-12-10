/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/09 21:30:37 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_rt.h"

/*
** Configura los hooks de eventos de X11 para la ventana
** Parámetros:
**   - rt: estructura principal con mlx y ventana
** Funcionamiento:
**   - Hook de KeyPress: captura teclas presionadas → key_handler
**   - Hook de DestroyNotify: captura cierre de ventana → close_handler
** NOTA: No usa mlx_key_hook porque necesitamos hooks específicos de X11
*/
static void	events_init(t_minirt *rt)
{
	mlx_hook(rt->win, KeyPress, KeyPressMask, key_handler, rt);
	mlx_hook(rt->win, DestroyNotify, StructureNotifyMask, close_handler, rt);
}

/*
** Maneja errores de memoria durante la inicialización
** Parámetros:
**   - rt: estructura principal (parcialmente inicializada)
** Comportamiento:
**   - Libera recursos MLX ya allocados (ventana, display)
**   - Llama a error_manager para mostrar mensaje y salir
** NOTA: Solo libera lo que ya se haya inicializado exitosamente
*/
static void	malloc_error(t_minirt *rt)
{
	if (rt->mlx)
	{
		if (rt->win)
		{
			mlx_destroy_window(rt->mlx, rt->win);
		}
		mlx_destroy_display(rt->mlx);
		free(rt->mlx);
	}
	error_manager("Error: Memory allocation failed");
}

/*
** Inicializa todos los componentes de MinilibX y la cámara
** Parámetros:
**   - rt: estructura principal (debe estar inicializada con ft_bzero)
** Proceso:
**   1. Inicializa conexión MLX con el servidor X
**   2. Crea ventana de WIDTH x HEIGHT píxeles
**   3. Crea imagen en memoria para renderizado rápido
**   4. Obtiene puntero directo a los píxeles de la imagen
**   5. Inicializa cámara con valores por defecto
**   6. Configura hooks de eventos (teclado y cierre)
** NOTA: Si falla algún paso, llama a malloc_error que limpia y sale
*/
void	minirt_init(t_minirt *rt)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
		malloc_error(rt);
	rt->win = mlx_new_window(rt->mlx, WIDTH, HEIGHT, WIN_TITLE);
	if (!rt->win)
		malloc_error(rt);
	rt->img.img_ptr = mlx_new_image(rt->mlx, WIDTH, HEIGHT);
	if (!rt->img.img_ptr)
		malloc_error(rt);
	rt->img.pixels_ptr = mlx_get_data_addr(rt->img.img_ptr, &rt->img.bpp,
			&rt->img.line_len, &rt->img.endian);
	camera_init(&rt->camera);
	events_init(rt);
}

/*
** Libera todos los recursos allocados por miniRT
** Parámetros:
**   - rt: estructura principal a limpiar
** Comportamiento:
**   - Destruye imagen de MLX
**   - Destruye ventana de MLX
**   - Destruye conexión con X11 (mlx_destroy_display)
**   - Libera la estructura mlx
**   - Libera la escena parseada
** NOTA: Debe llamarse antes de terminar el programa
**       El orden de destrucción es importante (primero imagen, luego ventana)
*/
void	minirt_cleanup(t_minirt *rt)
{
	if (rt->img.img_ptr)
		mlx_destroy_image(rt->mlx, rt->img.img_ptr);
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	if (rt->mlx)
	{
		mlx_destroy_display(rt->mlx);
		free(rt->mlx);
	}
	if (rt->scene)
		escene_destructor(rt->scene);
}
