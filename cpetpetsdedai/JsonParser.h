#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <json/json.h>



class JsonParser {
public:
	template<typename T>
	static T GetJsonValue(Json::Value& root, std::string key)
	{
		// std::ifstream file("Scenes/MenuScene.json");
		// Json::Value actualJson;
		// Json::Reader reader;
		//
		// reader.parse(file, actualJson);
		return T();
	}

	template<typename T>
	static void WriteJsonFile(std::string fileName, std::string key, T value)
	{
		std::fstream file;
		file.open(fileName, std::ios::out);
		if (file.is_open())
		{
			file << "TEEEST";
			file.close();
		}
	}

};
