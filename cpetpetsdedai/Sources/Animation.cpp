#include "../Headers/Animation.h"

Animation::Animation(std::string _name, std::string _animationPath, float _duration, bool _loop)
{
    // This structure would distinguish a file from a
    // directory
    struct stat sb;
 
    // Looping until all the items of the directory are
    // exhausted
    for (const auto& entry : std::filesystem::directory_iterator(_animationPath))
    {
 
        // Converting the path to const char * in the
        // subsequent lines
        std::filesystem::path outfilename = entry.path();
        std::string outfilename_str = outfilename.string();
        const char* path = outfilename_str.c_str();
 
        // Testing whether the path points to a
        // non-directory or not If it does, displays path
        if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
        {
            std ::cout << path << std::endl;
        }
    }
}
