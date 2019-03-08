#ifndef __COMFORTABLE_SWIPE__util_read_config_file__
#define __COMFORTABLE_SWIPE__util_read_config_file__

/*
Comfortable Swipe
by Rico Tiongson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <map> // std::map
#include <string> // std::string
#include <fstream> // std::ifstream
#include <iostream> // std::endl, std::getline
#include <sstream> // std::ostringstream
#include <cstdlib> // exit
#include <cctype> // std::isspace
#include <stdexcept> // std::runtime_error

namespace comfortable_swipe
{
    namespace util
    {
        /**
         * A utility method for reading the config file.
         *
         * @param filename (const char*) the path of the config file.
         */
        std::map<std::string, std::string> read_config_file(const char* filename)
        {

            std::map<std::string, std::string> conf;
            std::ifstream fin(filename, std::ios::in);

            if (!fin.is_open())
            {
                throw std::runtime_error("config file does not exist");
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
                            std::ostringstream stream;
                            stream << "error in conf file " << filename << std::endl;
                            stream << "multiple equal signs in line " << line_number << std::endl;
                            throw std::runtime_error(stream.str());
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
                    std::ostringstream stream;
                    stream << "error in conf file: " << filename << std::endl;
                    stream << "equal sign expected in line " << line_number << std::endl;
                    throw std::runtime_error(stream.str());
                }

                // equal sign found, add to tokens
                if (token[1].length() > 0)
                    conf[token[0]] = token[1];
            }

            return conf;
        }
    }
}

#endif /* __COMFORTABLE_SWIPE__util_read_config_file__ */
