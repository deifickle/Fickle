#include "BuntingFileIO.h"
#include <stdio.h>

std::list<BuntingFile*> openFiles;

bool bunValidateJsonFile(BuntingFile* file) {

	file->jsonDoc.Parse(file->content.c_str());

	assert(!file->jsonDoc.HasParseError());

	const char* fileVersion = (file->jsonDoc)["BuntingJsonVersion"].GetString();
	assert(strcmp(fileVersion, BUNTING_VERSION) == 0);

	file->isJsonParsed = true;
	return true;
}

int bunOpenFile(const char* path, const char* filename, const char* extn, BuntingFile::KOpenMode mode) {
	
	//allocate space in the heap as it is a pointer
	BuntingFile* file = new BuntingFile();
	int result = file->open(path, filename, extn, mode);
	
	if (result == 0) {
		file->read();//read the file

		std::string err;
		assert(file->isContentReady);//ensure content is ready in file

		if (strcmp(extn, "json") == 0) {
			bunValidateJsonFile(file);
		}

		openFiles.push_back(file);
		return (int)openFiles.size() - 1;// success! return file's index in the list as the return value.
	}

	delete file;//failure to reach here. hence delete the allocated space.
	return result;//return the failed result from file.open()
}

BuntingFile* bunGetFile(int index) {
	assert(index < (openFiles.size()));//ensure the index is not our of bounds
	
	std::list<BuntingFile*>::iterator itr = openFiles.begin();
	std::advance(itr, index);
	
	return *itr;
}
