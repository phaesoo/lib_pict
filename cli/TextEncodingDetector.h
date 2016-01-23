#pragma once

#include "../include/TextEncodingDetect/text_encoding_detect.h"

#include "strings.h"

//typedef AutoIt::Text::TextEncodingDetect::Encoding Encoding;

class TextEncodingDetector
{

public:
	TextEncodingDetector() {}
	~TextEncodingDetector() {}

	AutoIt::Text::TextEncodingDetect::Encoding DetectTextEncoding(const wchar_t* fileLoc);
};
