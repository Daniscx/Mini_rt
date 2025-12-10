/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/12/10 02:16:23 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_rt.h"

/*
** Inicializa la cámara con valores por defecto
** Parámetros:
**   - camera: puntero a la cámara a inicializar
** Configuración por defecto:
**   - position: (0, 0, -5) → 5 unidades atrás del origen
**   - direction: (0, 0, 1) → mirando hacia +Z
**   - up: (0, 1, 0) → eje Y como "arriba"
**   - right: producto cruz de direction × up
**   - fov: 60 grados
**   - aspect_ratio: WIDTH / HEIGHT
** TODO: Reemplazar valores por defecto con datos del archivo .rt parseado
*/
void	camera_init(t_camera *camera)
{
	camera->position = vec3_new(0.0, 0.0, -5.0);
	camera->direction = vec3_new(0.0, 0.0, 1.0);
	camera->up = vec3_new(0.0, 1.0, 0.0);
	camera->right = vec3_cross(camera->direction, camera->up);
	camera->fov = 60.0;
	camera->aspect_ratio = (double)WIDTH / (double)HEIGHT;
}

/*
** Mueve la cámara en el espacio 3D
** Parámetros:
**   - camera: cámara a mover
**   - offset: vector de desplazamiento a añadir a la posición actual
** Comportamiento:
**   - Suma el offset a la posición de la cámara
**   - No modifica la dirección ni orientación
** Ejemplo:
**   - offset = camera.direction * 0.5 → avanza 0.5 unidades hacia adelante
**   - offset = camera.right * -0.5 → se mueve 0.5 unidades a la izquierda
*/
void	camera_move(t_camera *camera, t_vec3 offset)
{
	camera->position = vec3_add(camera->position, offset);
}

/*
** Rota la cámara usando ángulos de Euler (yaw y pitch)
** Parámetros:
**   - camera: cámara a rotar
**   - yaw: rotación horizontal en radianes (izquierda/derecha)
**   - pitch: rotación vertical en radianes (arriba/abajo)
** Funcionamiento:
**   1. Calcula nueva dirección aplicando rotaciones yaw y pitch
**   2. Normaliza la nueva dirección
**   3. Recalcula vectores right y up para mantener base ortonormal
** Matrices de rotación:
**   - Yaw: rota alrededor del eje Y (horizontal)
**   - Pitch: rota alrededor del eje X (vertical)
** NOTA: Los vectores right y up se recalculan para mantener ortogonalidad
*/
void	camera_rotate(t_camera *camera, double yaw, double pitch)
{
	double	cos_yaw;
	double	sin_yaw;
	double	cos_pitch;
	double	sin_pitch;
	t_vec3	new_dir;

	cos_yaw = cos(yaw);
	sin_yaw = sin(yaw);
	cos_pitch = cos(pitch);
	sin_pitch = sin(pitch);
	new_dir.x = camera->direction.x * cos_yaw - camera->direction.z * sin_yaw;
	new_dir.z = camera->direction.x * sin_yaw + camera->direction.z * cos_yaw;
	new_dir.y = camera->direction.y * cos_pitch - new_dir.z * sin_pitch;
	new_dir.z = camera->direction.y * sin_pitch + new_dir.z * cos_pitch;
	new_dir.x = new_dir.x;
	camera->direction = vec3_normalize(new_dir);
	camera->right = vec3_normalize(vec3_cross(camera->direction, vec3_new(0.0, 1.0, 0.0)));
	camera->up = vec3_normalize(vec3_cross(camera->right, camera->direction));
}
