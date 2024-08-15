#ifndef BUNTING_OBJECT_H
#define BUNTING_OBJECT_H

struct Spec {};

struct BuntingObject {

	virtual void init() {}
	virtual void quash() {}

	bool m_initialized = false;
	const char* m_name = nullptr;
};

#endif // !BUNTING_OBJECT_H