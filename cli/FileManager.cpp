#include <stdio.h>
#include <assert.h>
#include <memory>

#include "FileManager.h"

CFileManager::~CFileManager()
{
	fclose(file_);
}

bool CFileManager::OpenFile(const wchar_t* fileLoc, Mode mode)
{
	wchar_t* modename = nullptr;
	if (!GetModeByChar(mode, modename)) { return false; }
	if (modename == nullptr) { assert(0);  return false; }

	file_ = _wfopen(fileLoc, modename);
	if (file_ == nullptr) { assert(0);  return false; }
}

long CFileManager::GetFileSize()
{
	fseek(file_, 0, SEEK_END);
	long fsize = ftell(file_);
	fseek(file_, 0, SEEK_SET);

	return fsize;
}

std::shared_ptr<unsigned char> CFileManager::GetFileBuffer()
{
	// Read it all in
	unsigned char* buffer = new unsigned char[GetFileSize()];
	fread(buffer, fsize, 1, file);

	std::shared_ptr<unsigned char> buffera(nullptr);



	fclose(file);
}



bool CFileManager::GetModeByChar(const Mode mode, wchar_t* modename)
{
	switch (mode)
	{
	case CFileManager::BYTE:
		modename = L"rb";
		break;
	default:
		assert(0);
		return false;
	}
}
