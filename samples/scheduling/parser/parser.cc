#include <fstream>
#include <sstream>

#include "parser/parser.h"

std::string getStringValueFromDefLine(std::string line);
int getIntValueFromDefLine(std::string line);

int Parser::ParseDefinition(Model& model, std::string& definition)
{
    // read definition file and parse
    std::ifstream definition_file(definition);
    std::string line;
    
    Chunk* temp_chunk;
    Layer* temp_layer;
    
    while (std::getline(definition_file, line))
    {
        // if start with #, or blank, pass
        if (line[0] == '#')
        { continue; }
        else if (line.empty())
        { continue; }
        // parse model
        else if (line.find("startmodel") != std::string::npos)
        {
            model.setName(getStringValueFromDefLine(line));
        }
        else if (line.find("endmodel") != std::string::npos)
        {
            return 0;
        }
        else if (line.find("startchunk") != std::string::npos)
        {
            temp_chunk = new Chunk(getIntValueFromDefLine(line));
        }
        else if (line.find("endchunk") != std::string::npos)
        {
            model.setChunk(temp_chunk);    
        }
        else if (line.find("startlayer") != std::string::npos)
        {
            temp_chunk = new Chunk(getIntValueFromDefLine(line));
        }
        else if (line.find("endlayer") != std::string::npos)
        {
            model.setChunk(temp_chunk);    
        }
        else if (line.find("iact") != std::string::npos)
        {   
        }
        else if (line.find("oact") != std::string::npos)
        {   
        }
        else if (line.find("dependency") != std::string::npos)
        {   
        }
    }
    return 0;
}

std::string getStringValueFromDefLine(std::string line)
{
    std::string answer;
    char delimiter = ':';
    answer = line.substr(1, line.find(delimiter));
    return answer;
}

int getIntValueFromDefLine(std::string line)
{
    std::string answer;
    char delimiter = ':';
    answer = line.substr(1, line.find(delimiter));
    return stoi(answer);
}