#ifndef BUNTING_FILE_H
#define BUNTING_FILE_H

#include "../BuntingCommon_internal.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h" 
#include "rapidjson/filewritestream.h" 
#include "rapidjson/writer.h" 
#include <fstream> 
#include <iostream> 

typedef rapidjson::Document BuntingJsonDoc;
typedef rapidjson::Value	BuntingJsonValue;

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

	std::ifstream filePointer;
	bool isOpen = false;
	bool isContentReady = false;
	bool isJsonParsed = false;

	char* name = nullptr;
	char* fullPath = nullptr;
	std::string content = "";
	BuntingJsonDoc jsonDoc;

	int open(const char* path, const char* filename, const char* extn, KOpenMode mode = kOpenModeReadBinary);
	int read();
	int close();
};

#endif // !BUNTING_FILE_H
