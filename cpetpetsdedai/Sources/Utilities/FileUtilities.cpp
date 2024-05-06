#pragma once
#include "../../Headers/Utilities/FileUtilities.h"
#include <fstream>

bool FileUtilities::FileExists(std::string _filePath)
{
    return std::filesystem::exists(_filePath);
}

bool FileUtilities::DirectoryExists(std::string _directoryPath)
{
    struct stat sb;
    if (stat(_directoryPath.c_str(), &sb) == 0)
    {
        return true;      
    }
    else
    {
        return false;
    }
}

bool FileUtilities::CreateDirectory(std::string _directoryPath)
{
    if (!DirectoryExists(_directoryPath))
    {
        return std::filesystem::create_directory(_directoryPath);
    }
    return false;
}


std::string FileUtilities::ReadFromFile(std::string _filePath)
{
    std::fstream file;
    file.open(_filePath, std::ios::in);
    if (file.is_open())
    {
        std::string content;
        std::string line;
        while (std::getline(file, line))
        {
            content += line + "\n";
        }
        file.close();
        return content;
    }
    return "";
}

std::vector<std::string> FileUtilities::ReadLinesFromFile(std::string _filePath)
{
    std::vector<std::string> lines;
    std::fstream file;
    file.open(_filePath, std::ios::in);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}


bool FileUtilities::WriteInFile(std::string _filePath, std::string _content)
{
    std::fstream file;
    file.open(_filePath, std::ios::out);
    if (file.is_open())
    {
        file << _content;
        file.close();
        return true;
    }
    return false;
}

bool FileUtilities::WriteInFile(std::string _filePath, std::vector<std::string> _content, bool backToLine)
{
    std::string content;
    for (std::string line : _content)
    {
        content += line;
        if (backToLine)
        {
            content += "\n";
        }
    }
    return WriteInFile(_filePath, content);
}


bool FileUtilities::AppendInFile(std::string _filePath, std::string _content)
{
    std::fstream file;
    file.open(_filePath, std::ios::app);
    if (file.is_open())
    {
        file << _content;
        file.close();
        return true;
    }
    return false;
}

bool FileUtilities::AppenInFileAtLine(std::string _filePath, std::string _content, int _line)
{
    std::vector<std::string> lines = ReadLinesFromFile(_filePath);
    if (_line < lines.size())
    {
        lines.insert(lines.begin() + _line, _content);
        std::string content;
        for (std::string line : lines)
        {
            content += line + "\n";
        }
        return WriteInFile(_filePath, content);
    }
    return false;
}
