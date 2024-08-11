#include "EditorCommon.h"

class BuntingEditor {
public:
	void init();
	void drawMenu();
private:
	bool showMsgBox{ false };
	Rectangle rect, guiRect;
};
