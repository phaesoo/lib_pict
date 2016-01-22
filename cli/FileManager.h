#pragma once

class
{

};
class CFileManager
{
	// have to add modes
	enum Mode
	{
		BYTE,
	};

public:
	CFileManager()
		: file_(nullptr) {};
	~CFileManager();

public:
	bool OpenFile(const wchar_t* fileLoc, Mode mode);
	long GetFileSize();
	std::shared_ptr<unsigned char> GetFileBuffer();

private:
	bool GetModeByChar(const Mode md, wchar_t* mode);

private:
	FILE* file_;
};

