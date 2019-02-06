//////////////////////////////////////////////////
//MODIFYING THIS FILE REQUIRE ENGINE COMPILATION//
//////////////////////////////////////////////////

#define SGC_MATERIAL_UBO_BINDING_POINT 1
#define SGC_MATERIAL_MAX_NUMBER 50
#define SGC_MATERIAL_USE_DIFFUSE_TEXTURE 1
#define SGC_MATERIAL_USE_DIFFUSE_COLOR 2
#define SGC_MATERIAL_USE_NORMAL_TEXTURE 4
#define SGC_MATERIAL_IS_BUMP_TEXTURE 8
#define SGC_MATERIAL_USE_SPECULAR_TEXTURE 16

#define SGC_CAMERA_UBO_BINDING_POINT 2

#define SGC_POINTLIGHT_UBO_BINDING_POINT 3
#define SGC_POINTLIGHT_MAX_NUMBER 1500

#define SGC_DIRECTIONALLIGHT_UBO_BINDING_POINT 4
#define SGC_DIRECTIONALLIGHT_MAX_NUMBER 50

#define SGC_POINTLIGHT_CULL_SSBO_BINDING_POINT 5
#define SGC_POINTLIGHT_CULL_MAX_NUMBER 1024
#define SGC_CULL_TILE_SIZE 16

#define SGC_SHADER_CONSTANTS_UBO_BINDING_POINT 6