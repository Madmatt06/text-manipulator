#include "baseFormat.h"
#include <fstream>

baseFormat::baseFormat(std::string file, bool write) {
    baseFormat::write = write;
    if(write) {
        baseFormat::file.open(file, std::ios::out);
    } else {
        baseFormat::file.open(file, std::ios::in);
    }
}

std::string baseFormat::read() {
    return "";
}

int baseFormat::writeTo(baseFormat readFrom) {
    if(!write) {
        return 1;
    }
    return 0;
}

int baseFormat::writeAll(baseFormat readFrom) {
    if(!write) {
        return 1;
    }
    return 0;
}