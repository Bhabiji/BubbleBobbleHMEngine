#pragma once
#include "SDL.h"
namespace HiveMind
{
	typedef SDL_Rect RectI; //Takes int values
	struct Line {
		int x1, y1, x2, y2;
	};
}