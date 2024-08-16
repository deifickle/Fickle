#include "BuntingFileIO.h"
#include <stdio.h>

std::list<BuntingFile*> openFiles;

int bunOpenFile(const char* path, const char* filename, BuntingFile::KOpenMode mode) {
	
	//allocate space in the heap as it is a pointer
	BuntingFile* file = new BuntingFile();
	int result = file->open(path, filename, mode);
	
	if (result == 0) {
		file->read();//read the file

		std::string err;
		assert(file->isContentReady);//ensure content is ready in file

		const char* jsonEnd = picojson::parse(
			file->jsonData, file->content, file->content + file->length, &err);

		assert(err.empty());

		file->isJsonParsed = true;

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
