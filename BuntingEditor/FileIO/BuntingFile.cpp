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

int BuntingFile::open(const char* path, const char* filename, const char* extn, KOpenMode mode) {
	
	openMode = mode;

	long filenameLength = strlen(filename);
	int pathLength = strlen(path);
	int extnLength = strlen(extn);

	assert(filenameLength > 0);
	name = (char*)malloc(filenameLength * sizeof(char));

	assert(name);
	memcpy(name, filename, filenameLength);
	int allocSize = (1 + pathLength + filenameLength + extnLength) * sizeof(char);
	fullPath = (char*)malloc(allocSize);

	assert(fullPath);
	memcpy(fullPath, path, pathLength);
	memcpy(fullPath + pathLength, filename, filenameLength);
	fullPath[pathLength + filenameLength] = '.';
	memcpy(fullPath + pathLength + filenameLength + 1, extn, extnLength);
	fullPath[allocSize] = '\0';

	filePointer = std::ifstream(fullPath);

	if (filePointer) {
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

int BuntingFile::read() {
	if (!isContentReady) {
		assert(isOpen);//file should've been open by now. 

		// Read the entire file into a string 
		content = std::string((std::istreambuf_iterator<char>(filePointer)),
		std::istreambuf_iterator<char>());
		isContentReady = true;
	}
	return 0;
}

int BuntingFile::close() {
	if (filePointer) {
		/*fclose(filePointer);*/
		

		length = -1;

		delete name;
		delete fullPath;

		name = nullptr;
		content = "";
		fullPath = nullptr;

		isContentReady = false;
		isOpen = false;
		isJsonParsed = false;

		return 0;
	}
	assert(false);
	return -1;//cannot close an invalid file. may be the file is not open!
}