#ifndef BUNTING_FILE_H
#define BUNTING_FILE_H

#include "../BuntingCommon_internal.h"
#include "PicoJSON/picojson.h"

typedef picojson::value BuntingJsonData;

struct BuntingFile {

	enum KOpenMode {
		kOpenModeRead,
		kOpenModeWrite,
		kOpenModeReadBinary,
		kOpenModeWriteBinary,
		kOpenModeAppend,
		kOpenModeAppendBinary,
		kOpenModeReadWrite,
		kOpenModeReadWriteBinary
	};

	KOpenMode openMode;
	
	long length = -1;

	FILE* pointerToFile = nullptr;
	bool isOpen = false;
	bool isContentReady = false;
	bool isJsonParsed = false;

	char* name = nullptr;
	char* content = nullptr;
	char* fullPath = nullptr;
	BuntingJsonData jsonData;

	int open(const char* path, const char* filename, KOpenMode mode = kOpenModeReadBinary);
	char* read();
	int close();
};

#endif // !BUNTING_FILE_H
