#ifndef BUNTING_COMMON_INTERNAL_H
#define BUNTING_COMMON_INTERNAL_H

// BuntingEditor.h : Include file for standard system include files,
// or project specific include files.

#define BUNTING_VERSION	"0.1.0"

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <list>
#include <vector>
#include <algorithm>

#include "raylibImgui/include/imgui.h"
#include "raylibImgui/include/rlImGui.h"
#include "raylibImgui/include/imgui_impl_raylib.h"

// TODO: Reference additional headers your program requires here.
#include "BuntingMacros.h"
#include "BuntingObject.h"

BUNTING_DECLARE_FUNCTION_PTR(bool, BuntingKeyCallback, void*);
//typedef bool (*BuntingKeyCallbackFPtr)(void* userData);

struct BuntingEditorState {
	struct Callbacks {
		BuntingKeyCallbackFPtr key;
	}callback;
};

extern BuntingEditorState buntingState;

#endif // !BUNTING_COMMON_INTERNAL_H