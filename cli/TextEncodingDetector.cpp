#include <memory>
#include <assert.h>

#include "text_encoding_detect.h"
#include "TextEncodingDetector.h"


Encoding CTextEncodingDetector::DetectTextEncoding(const wchar_t* fileLoc)
{
	if (GetFileBuffer)
}

bool CTextEncodingDetector::GetFileBuffer(const wchar_t* fileLoc, unsigned char* buffer)
{
	if (buffer != nullptr) { assert(0); return false; }

	// Open file in binary mode
	FILE* file;
	file = _wfopen(fileLoc, L"rb");
	if (file == nullptr) { assert(0);  return false; }

	// Get file size
	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Read it all in
	buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	return true;
}

