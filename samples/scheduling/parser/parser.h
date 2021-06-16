#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include "model/model.h"
#include "builder/builder.h"

class Parser
{
private:
public:
    static int ParseDefinition(Model& model, std::string& definition);
};

#endif