#ifndef BASE_FORMAT_H
#define BASE_FORMAT_H
#include <fstream>
#include <string>
class baseFormat {
    public:
    baseFormat(std::string, bool);
    std::string read();
    int writeTo(baseFormat);
    int writeAll(baseFormat readFrom);
    protected:
    std::fstream file;
    private:
    bool write;

};
#endif