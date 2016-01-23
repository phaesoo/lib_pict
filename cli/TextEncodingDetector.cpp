#include <memory>
#include <cassert>

#include "text_encoding_detect.h"
#include "TextEncodingDetector.h"

using namespace AutoIt::Text;

TextEncodingDetect::Encoding TextEncodingDetector::DetectTextEncoding(const wchar_t* fileLoc)
{
	TextEncodingDetect::Encoding encoding = TextEncodingDetect::None;

	// Open file in binary mode
	FILE *file = nullptr;
	errno_t err = _wfopen_s(&file, fileLoc, L"rb");
	if (err != 0)
	{
		assert(0);
		return encoding;
	}

	// Get file size
	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Read it all in
	unsigned char *buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	// Detect the encoding
	TextEncodingDetect textDetect;
	return textDetect.DetectEncoding(buffer, fsize);
}


