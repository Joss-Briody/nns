#include <iostream>
#include <memory>
#include <fstream>
#include <stdexcept>

#ifndef _IO_UTILS_H
#define _IO_UTILS_H

namespace io {

    bool fileExists(const std::string &fileName);

    void checkFileExists(const std::string &name);

    inline uint32_t readHeader(const std::unique_ptr<char[]> &buffer, size_t position);

    inline std::unique_ptr<char[]> readBinaryFile(const std::string &path);

}

#include "src/data/io_utils.tpp"
#endif