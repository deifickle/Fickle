#include "BuntingFile.h"

const char* getMode(BuntingFile::KOpenMode mode) {

	switch (mode)
	{
	case BuntingFile::kOpenModeRead:				return "r";
	case BuntingFile::kOpenModeWrite:				return "w";
	case BuntingFile::kOpenModeReadBinary:			return "rb";
	case BuntingFile::kOpenModeWriteBinary:			return "wb";
	case BuntingFile::kOpenModeAppend:				return "a";
	case BuntingFile::kOpenModeAppendBinary:		return "ab";
	case BuntingFile::kOpenModeReadWrite:			return "r+";
	case BuntingFile::kOpenModeReadWriteBinary:		return "rb+";
	default:										assert(false); return "";
	}
}

int BuntingFile::open(const char* path, const char* filename, KOpenMode mode) {
	
	openMode = mode;

	long filenameLength = strlen(filename);
	int pathLength = strlen(path);

	assert(filenameLength > 0);
	name = (char*)malloc(filenameLength);

	assert(name);
	memcpy(name, filename, filenameLength);
	
	fullPath = (char*)malloc(1 + strlen(path) + strlen(filename));

	assert(fullPath);
	memcpy(fullPath, path, pathLength);
	memcpy(fullPath + pathLength, name, filenameLength);

	pointerToFile = fopen(fullPath, getMode(mode));

	if (pointerToFile) {
		isOpen = true;
		return 0;
	}
	else {

		delete name;
		delete fullPath;

		name = nullptr;
		fullPath = nullptr;
	}
}

char* BuntingFile::read() {
	if (!content) {
		assert(isOpen);//file should've been open by now. 

		fseek(pointerToFile, 0, SEEK_END);
		length = ftell(pointerToFile);

		fseek(pointerToFile, 0, SEEK_SET);
		content = (char*)malloc(length * sizeof(char));
		if (content)
		{
			long readSize = fread(content, 1, length, pointerToFile);
			//if (readSize == length) {
			isContentReady = true;
			return content;// success
			//}
			
			// failure if we reach here. full file is not being read for some reason!
			// hence free the allocated space and return
			
			//free(content);
			//return nullptr;
		}
		// unable to read content for some reason
		return nullptr;
	}
	return content;
}

int BuntingFile::close() {
	if (pointerToFile) {
		fclose(pointerToFile);
		pointerToFile = nullptr;

		length = -1;

		delete name;
		delete content;
		delete fullPath;

		name = nullptr;
		content = nullptr;
		fullPath = nullptr;

		isContentReady = false;
		isOpen = false;

		return 0;
	}
	assert(false);
	return -1;//cannot close an invalid file. may be the file is not open!
}