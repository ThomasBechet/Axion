#pragma once

#define MATERIAL_UBO_BINDING_POINT 1
#define MATERIAL_MAX_NUMBER 50
#define MATERIAL_USE_DIFFUSE_TEXTURE 1
#define MATERIAL_USE_DIFFUSE_COLOR 2
#define MATERIAL_USE_NORMAL_TEXTURE 4
#define MATERIAL_IS_BUMP_TEXTURE 8
#define MATERIAL_USE_SPECULAR_TEXTURE 16

#define CAMERA_UBO_BINDING_POINT 2

#define POINTLIGHT_UBO_BINDING_POINT 3
#define POINTLIGHT_MAX_NUMBER 500

#define DIRECTIONALLIGHT_UBO_BINDING_POINT 4
#define DIRECTIONALLIGHT_MAX_NUMBER 50

#define POINTLIGHT_CULL_SSBO_BINDING_POINT 5
#define POINTLIGHT_CULL_MAX_NUMBER 1024
#define CULL_TILE_SIZE 16