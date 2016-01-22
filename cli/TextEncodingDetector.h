#pragma once

#include "../include/TextEncodingDetect/text_encoding_detect.h"

#include "strings.h"

typedef AutoIt::Text::TextEncodingDetect::Encoding Encoding;

class CTextEncodingDetector
{
public:
	CTextEncodingDetector() {}
	~CTextEncodingDetector() {}

public:
	Encoding DetectTextEncoding(const wchar_t* fileLoc);

private:
	bool GetFileBuffer(const wchar_t* fileLoc, unsigned char* buffer);

private:

	std::shared_ptr<unsigned char> buffer_;
};

