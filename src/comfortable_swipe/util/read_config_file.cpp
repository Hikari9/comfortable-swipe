#include <map> // std::map
#include <string> // std::string
#include <fstream> // std::ifstream
#include <iostream> // std::cerr, std::endl, std::getline
#include <cstdlib> // exit
#include <cctype> // std::isspace

namespace comfortable_swipe::util
{
    /**
     * A utility method for reading the config file.
     * 
     * @param filename (const char*) the path of the config file.
     */
    std::map<std::string, std::string> read_config_file(const char* filename)
    {
        
        std::map<std::string, std::string> conf;
        std::ifstream fin(filename);

        if (!fin.is_open())
        {
            std::cerr << "file \"" << filename << "\" does not exist!" << std::endl;
            exit(1);
        }

        static std::string line, token[2];
        int line_number = 0;
        
        while (std::getline(fin, line))
        {
            ++line_number;
            token[0].clear();
            token[1].clear();
            int length = line.length();
            int equal_flag = 0;
            
            // tokenize comfig config
            for (int i = 0; i < length; ++i)
            {
                if (line[i] == '#') // skip comments
                    break;
                if (line[i] == '=') // flag equal sign
                {
                    if (++equal_flag > 1)
                    {
                        std::cerr << "error in conf file " << filename << std::endl;
                        std::cerr << "multiple equal signs in line " << line_number << std::endl;
                        exit(1);
                    }
                }
                else if (!std::isspace(line[i]))
                {
                    // add to buffer
                    token[equal_flag].push_back(line[i]);
                }
            }

            // ignore empty lines
            if (equal_flag == 0 && token[0].length() == 0)
                continue;

            // no equal sign found in non-empty line
            if (equal_flag == 0)
            {
                std::cerr << "error in conf file: " << filename << std::endl;
                std::cerr << "equal sign expected in line " << line_number << std::endl;
                exit(1);
            }

            // equal sign found, add to tokens
            if (token[1].length() > 0)
                conf[token[0]] = token[1];
        }
        
        return conf;
    }
}
