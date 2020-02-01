#include <iostream>
#include <memory>
#include <fstream>
#include <stdexcept>

#include "include/data/io_utils.hpp"

namespace io {

    bool fileExists(const std::string &fileName)
    {
        std::ifstream f(fileName.c_str());
        return f.good();
    }

    void checkFileExists(const std::string &name)
    {
        if (!fileExists(name))
        {
            throw std::invalid_argument("File does not exists: " + name);
        }
    }

    inline uint32_t readHeader(const std::unique_ptr<char[]> &buffer, size_t position)
    {
        auto header = reinterpret_cast<uint32_t *>(buffer.get());
        auto value = *(header + position);
        return (value << 24) | ((value << 8) & 0x00FF0000) | ((value >> 8) & 0X0000FF00) | (value >> 24);
    }

    inline std::unique_ptr<char[]> readBinaryFile(const std::string &path)
    {
        std::ifstream f;
        f.open(path, std::ios::in | std::ios::binary | std::ios::ate);
        if (!f)
        {
            std::cout << "Error opening file" << std::endl;
            return {};
        }
        auto size = f.tellg();
        std::unique_ptr<char[]> buffer(new char[size]);

        f.seekg(0, std::ios::beg);
        f.read(buffer.get(), size);
        f.close();
        return buffer;
    }

} // namespace io
