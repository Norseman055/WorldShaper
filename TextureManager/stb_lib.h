#pragma once

// Disable compiler warnings caused by stb_image.h
#pragma warning( disable : 4505 )
#pragma warning( disable : 4244 )

#define STBI_ONLY_TGA

#define STB_IMAGE_IMPLEMENTATION
#include "stb\stb_image.h"