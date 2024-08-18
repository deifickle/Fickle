#ifndef FICKLE_WINDOW_H
#define FICKLE_WINDOW_H

#include "../FickleCommon_internal.h"

struct FickleWindow : FickleObject{
	struct WindowSpec {
		const char* name;
	};

	int init();
	int createWindow();
	int update();
	int draw();
	int destroyWindow();
	int quash();
};

#endif // !FICKLE_WINDOW_H
