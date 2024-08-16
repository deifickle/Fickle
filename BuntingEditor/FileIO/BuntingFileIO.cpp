#include "BuntingFileIO.h"
#include <stdio.h>

int BuntingFileIO::openFile(const char* path, const char* filename, BuntingFile::KOpenMode mode) {
	
	//allocate space in the heap as it is a pointer
	BuntingFile* file = new BuntingFile();
	int result = file->open(path, filename, mode);
	
	if (result == 0) {
		openFiles.push_back(file);
		return (int)openFiles.size() - 1;// success! return file's index in the list as the return value.
	}

	delete file;//failure to reach here. hence delete the allocated space.
	return result;//return the failed result from file.open()
}

const char* BuntingFileIO::getData(int index) {
	assert(index < (openFiles.size()));//ensure the index is not our of bounds
	
	std::list<BuntingFile*>::iterator itr = openFiles.begin();
	std::advance(itr, index);

	BuntingFile* f = *itr;

	if (f->isOpen) {
		return f->read();
	}
	else {
		return nullptr;//error - file not open
	}
}
