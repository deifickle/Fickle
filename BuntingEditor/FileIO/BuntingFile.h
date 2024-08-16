#ifndef BUNTING_FILE_H
#define BUNTING_FILE_H

#include "../BuntingCommon_internal.h"

struct BuntingFile {

	enum KOpenMode {
		kRead,
		kWrite,
		kReadBinary,
		kWriteBinary,
		kAppend,
		kAppendBinary,
		kReadWrite,
		kReadWriteBinary
	};

	KOpenMode openMode;
	long length = -1;

	FILE* pointerToFile = nullptr;
	bool isOpen = false;
	char* name = nullptr;
	char* content = nullptr;
	char* fullPath = nullptr;

	int open(const char* path, const char* filename, KOpenMode mode = kReadBinary);
	char* read();
	int close();
};

#endif // !BUNTING_FILE_H
