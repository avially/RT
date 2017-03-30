/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avially <avially@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 22:01:00 by vdaviot           #+#    #+#             */
/*   Updated: 2017/03/30 19:06:16 by avially          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <stdlib.h>
#include "keywords.h"

#define NEW_OBJECT(var, n) var = (t_object *)malloc(sizeof(t_object)); if (!var) ft_exit("malloc error"); ft_strcpy(var->name, n);
#define SS(t) while(*t&&ft_isspace(*t))t++;
#define SKIP_EMPTY_LINE(l) {char*t=l;SS(t);if (*t==0)continue;}

bool			check_obj_line(char *line, char *obj_name, int *indent_level)
{
	char	*k;
	int		space_number;

	space_number = 0;
	(*indent_level) = 0;
	while (*line && (*line == '\t' || *line == ' '))
	{
		if (*line == '\t')
			(*indent_level)++;
		else if (*line == ' ')
			space_number++;
		if (space_number == 4 && !(space_number = 0))
			(*indent_level)++;
		line++;
	}
	if (!*line)
		return false;
	k = line;
	while (*line && *line++ != ':')
		;
	if (!*line)
	{
		if (FOREACH(g_restricted_keywords, keyword))
		{
			if (!ft_strcmp(k, keyword))
				return false;
		}
		ft_strlcpy(obj_name, k, 256);
		return true;
	}
	else
		return false;
}

void 			fill_prop_camera(t_camera *cam, char *line, const char *prop)
{
	int		ret;
	char	*str = (char *)(char[256]){0};
	char	word[256];
	int		i;

	ret = 0;
	ft_sscanf(LF_RT_FOV, line, &cam->fov);

	if (!ft_sscanf(LF_RT_MASK, line, str, 256))
	{
		while ((get_next_word(&str, word)))
		{
			i = 0;
			while (ft_strcmp(mask_restricted_keywords[i].name, "END"))
			{
				if (!ft_strcmp(mask_restricted_keywords[i].name, word))
					ret |= mask_restricted_keywords[i].value;
				i++;
			}
		}
		cam->post_processing_mask = ret;
	}
}

void  		fill_prop_primitive(t_primitive *prim, char *line, const char *prop)
{
	ft_sscanf(LF_RT_RADIUS, line, &prim->radius);
	ft_sscanf(LF_RT_HEIGHT, line, &prim->height);
	ft_sscanf(LF_RT_ANGLE, line, &prim->angle);

	if (!ft_sscanf(LF_RT_SLICE, line, &prim->slice))
		prim->nb_slice++;
}

void			fill_prop_light(t_light *light, char *line, const char *prop)
{
	char	name[256];

	ft_sscanf(LF_RT_COLOR, line, &light->color.x, &light->color.y, &light->color.z);

	ft_sscanf(LF_RT_INTENSITY, line, &light->intensity);
	ft_sscanf(LF_RT_ANGLE, line, &light->angle);

	ft_sscanf(LF_RT_TYPE, line, &name, sizeof(name));
}

void			fill_prop_transform(t_transform *tsf, char *line, const char *prop)
{
	ft_sscanf(LF_RT_POS, line, &tsf->position.x, &tsf->position.y, &tsf->position.z);
	ft_sscanf(LF_RT_ROT, line, &tsf->rotation.x, &tsf->rotation.y, &tsf->rotation.z);
}

void  		fill_prop_material(t_material *mtl, char *line, const char *prop)
{
	char	*str = (char *)(char[256]){0};
	char	word[256];
	int		ret;
	int		i;

	ret = 0;
	ft_sscanf(LF_RT_COLOR, line, &mtl->color.x, &mtl->color.y, &mtl->color.z);
	ft_sscanf(LF_RT_EMISSION_COLOR, line, &mtl->emission_color.x, &mtl->emission_color.y, &mtl->emission_color.z);
	ft_sscanf(LF_RT_HIGHLIGHT_COLOR, line, &mtl->highlight_color.x, &mtl->highlight_color.y, &mtl->highlight_color.z);

	ft_sscanf(LF_RT_TRANSPARENCY, line, &mtl->transparency);
	ft_sscanf(LF_RT_SPECULAR, line, &mtl->specular);
	ft_sscanf(LF_RT_REFLECTION, line, &mtl->reflection);
	ft_sscanf(LF_RT_REFRACTION, line, &mtl->refraction);

	if (FOR(i = 0, i < 2, i++))
	{
		struct {char *fmt; t_image *img;} maps[8] ={
			{LF_RT_BUMPMAP, &mtl->bumpmap},
			{LF_RT_TEXTURE, &mtl->texture},
			{LF_RT_EMISSION_MAP, &mtl->texture},
			{LF_RT_HIGHLIGHT_MAP, &mtl->emission_map},
			{LF_RT_TRANSPARENCY_MAP, &mtl->transparency_map},
			{LF_RT_SPECULAR_MAP, &mtl->specular_map},
			{LF_RT_REFLECTION_MAP, &mtl->reflection_map},
			{LF_RT_REFRACTION_MAP, &mtl->refraction_map},
		};
		//if (ft_sscanf(maps[i].fmt, line, maps[i].img->file, 1024))
		//	maps[i].img->opengl_id = SOIL_load_OGL_texture(maps[i].img->file, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		//		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS);
	}
	/*ft_sscanf(LF_RT_BUMPMAP, line, &mtl->bumpmap.file, sizeof(mtl->bumpmap.file));
	ft_sscanf(LF_RT_TEXTURE, line, &mtl->texture.file, sizeof(mtl->texture.file));
	ft_sscanf(LF_RT_EMISSION_MAP, line, &mtl->emission_map.file, sizeof(mtl->transparency_map.file));
	ft_sscanf(LF_RT_HIGHLIGHT_MAP, line, &mtl->highlight_map.file, sizeof(mtl->highlight_map.file));
	ft_sscanf(LF_RT_TRANSPARENCY_MAP, line, &mtl->transparency_map.file, sizeof(mtl->transparency_map.file));
	ft_sscanf(LF_RT_SPECULAR_MAP, line, &mtl->specular_map.file, sizeof(mtl->specular_map.file));
	ft_sscanf(LF_RT_REFLECTION_MAP, line, &mtl->reflection_map.file, sizeof(mtl->reflection_map.file));
	ft_sscanf(LF_RT_REFRACTION_MAP, line, &mtl->refraction_map.file, sizeof(mtl->refraction_map.file));*/

	if (!ft_sscanf(LF_RT_ILLUM, line, str, 256))
	{
			while (get_next_word(&str, word))
			{
				if (FOR(i = 0, illum_restricted_keywords[i].value != END, i++))
				{
					if (!ft_strcmp(illum_restricted_keywords[i].name, word))
						ret |= illum_restricted_keywords[i].value;
				}
			}
			mtl->illum = ret;
	}
}

//T: protection for size of bumpmaps: same size than textures.

#define FILL_PROP(X, line, pname) _Generic((X), t_light *: fill_prop_light, t_transform *: fill_prop_transform, t_material *:fill_prop_material, t_camera *:fill_prop_camera, t_primitive *:fill_prop_primitive) (X, line, pname)
#define A(c, line, p1) FILL_PROP(&c-> p1, line, #p1);// FILL_PROP(&c-> p2, line, #p2);
void			parse_rt_file(char *file, t_scene *scene)
{
	int			fd;
	char		line[0xF000 + 1];
	char		obj_name[256];
	int			indent_level;
	t_object	*current_object;

	INIT(int, line_count, 0);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("Open Failed");
	while (gl(line, &fd))
	{
		SKIP_EMPTY_LINE(line);
		if (check_obj_line(line, obj_name, &indent_level))
		{

			NEW_OBJECT(current_object, obj_name);
			current_object->indent_level = indent_level;
			continue ;
		}
		if (indent_level >= 10)
			ft_exit("max indentation reached at line: %i\n", line_count);
		if (indent_level == current_object->indent_level + 1)
		{
			A(current_object, line, transform);
			A(current_object, line, material);
			A(current_object, line, primitive);
			A(current_object, line, light_prop);
			A(current_object, line, camera);

			printf("name: %s\n", current_object->name);
			printf("line: %s\n", line);
			if (current_object->material.transparency)
				printf("transparency: %f\n", current_object->material.transparency);
			if (current_object->material.specular)
				printf("specular: %f\n", current_object->material.specular);
			if (current_object->material.reflection)
				printf("reflection: %f\n", current_object->material.reflection);
			if (current_object->material.refraction)
				printf("refraction: %f\n", current_object->material.refraction);
			printf("pos.x: %f, pos.y: %f, pos.z: %f\n", current_object->transform.position.x,current_object->transform.position.y,current_object->transform.position.z);
			printf("rot.x: %f, rot.y: %f, rot.z: %f\n", current_object->transform.rotation.x,current_object->transform.rotation.y,current_object->transform.rotation.z);
			if (current_object->camera.post_processing_mask)
				printf("mask: %x\n", current_object->camera.post_processing_mask);
			if (current_object->material.illum)
				printf("material illum: %x\n", current_object->material.illum);
		}
		else
			ft_exit("bad indentation at line %i\n", line_count);
	}
	(void)scene;
	close(fd);
}
