#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

//#define PARSE_DEBUG

enum method {none, split, tab, comma, space};

enum results {failed, operate, help};

struct request {
    bool verbose;
    std::string inputFile;
    method input;
    int outputCount;
    std::string* outputFiles;
    method* outputs;
};



results parseArgs(request &userRequest, int argc, char* argv[]) {
    struct methodAssoc {
        std::string longType;
        std::string shortType;
        method methodType;
    };

    const methodAssoc check[] = {{"", "", method::none}, {"--splitText", "-s", method::split}, {"--tabSeperated", "-t", method::tab}, {"--commaSeperated", "-c", method::comma}, {"--spaceSeperated", "-S", method::space}};
    #ifdef PARSE_DEBUG
    std::cout << argc << std::endl;
    #endif

    bool inputType = false;
    method input;
    bool inputName = false;
    std::string name;
    u_int64_t outputType = 0;
    u_int64_t outputName = 0;
    method* methods = (method*) malloc(sizeof(method) * argc);
    std::string* names = (std::string*) malloc(sizeof(std::string) * argc);
    for(int argIndex = 1; argIndex < argc; argIndex++) {
        #ifdef PARSE_DEBUG
        std::cout << argv[argIndex] << " ";
        #endif
        if(argv[argIndex][0] != '\0') {
            #ifdef PARSE_DEBUG
            std::cout << "Not null. ";
            #endif

            if(argv[argIndex][0] == '-') {
                #ifdef PARSE_DEBUG
                std::cout << "Is argument type. ";
                #endif

                for(methodAssoc typeCheck: check) {
                    if(argv[argIndex] == typeCheck.longType || argv[argIndex] == typeCheck.shortType) {
                        #ifdef PARSE_DEBUG
                        std::cout << "Matching type found.";
                        #endif

                        if(!inputType) {
                            inputType = true;
                            input = typeCheck.methodType;
                        } else {
                            methods[outputType] = typeCheck.methodType;
                            outputType++;
                        }
                        break;
                    }
                }
                #ifdef PARSE_DEBUG
                std::cout << std::endl;
                #endif

            } else {
                #ifdef PARSE_DEBUG
                std::cout << "File added" << std::endl;
                #endif

                if(!inputName) {
                    inputName = true;
                    name = argv[argIndex];
                } else {
                    names[outputName] = argv[argIndex];
                    outputName++;
                }
            }
        }
    }
    if(outputType != outputName || outputType == 0) {
        free(methods);
        free(names);
        return results::failed;
    }

    userRequest.input = input;
    userRequest.inputFile = name;

    userRequest.outputCount = outputType;
    userRequest.outputFiles = (std::string*) malloc(sizeof(std::string) * outputName);
    std::copy(names, names + outputName, userRequest.outputFiles);

    userRequest.outputs = (method*) malloc(sizeof(method) * outputType);
    std::copy(methods, methods + outputType, userRequest.outputs);

    free(methods);
    free(names);
    return results::operate;
}

int main(int argc, char* argv[]) {
    if(argc < 5) {
        std::cout << "Usage: --input-format input-file --output-format output-file" << std::endl;
        return 1;
    }
    request userRequest = {false, {}, method::none, 0, nullptr, nullptr};
    results parsed = parseArgs(userRequest, argc, argv);
    if(parsed == results::failed || parsed == results::help) {
        std::cout << "Usage: --input-format input-file --output-format output-file" << std::endl;
        return 1;
    }
    std::cout << "Input Type: " <<  userRequest.input << std::endl << "Input file name: " << userRequest.inputFile << std::endl << "Output Count: " << userRequest.outputCount << std::endl;
    return 0;
}

