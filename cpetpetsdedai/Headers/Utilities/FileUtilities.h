#pragma once
#include <filesystem>

#include "../../TList.h"

class FileUtilities
{
public:
    static bool FileExists(std::string _filePath);
	static bool DirectoryExists(std::string _directoryPath);
	static TList<std::string> GetDirectoriesInDirectoryRecursive(std::string _directoryPath);
	static TList<std::string> GetAllInDirectory(std::string _directoryPath);
	static bool CreateDirectory(std::string _directoryPath);
	static std::string ReadFromFile(std::string _filePath);
	static std::vector<std::string> ReadLinesFromFile(std::string _filePath);
	static bool WriteInFile(std::string _filePath, std::string _content);
	static bool WriteInFile(std::string _filePath, std::vector<std::string> _content, bool backToLine = true);
	static bool AppendInFile(std::string _filePath, std::string _content);
	static bool AppenInFileAtLine(std::string _filePath, std::string _content, int _line);
};
