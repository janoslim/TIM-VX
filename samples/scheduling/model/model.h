#ifndef MODEL_H
#define MODEL_H
#include <array>
class Layer
{
public:
    Layer(){}
    int iact[4];
    int oact[4];
    int operationType;
};

class Chunk
{
private:
    std::vector<Layer*> layer_vec;
public:
    Chunk(int _number){ number = _number; }
    ~Chunk()
    {
        for (auto layer : layer_vec) free(layer);
    }
    int number;
    void setLayer(Layer* layer_ptr)
    {
        layer_vec.push_back(layer_ptr);
    }
};

class Model
{
private:
    std::vector<Chunk*> chunk_vec;
public:
    std::string name;
    Model() {}
    ~Model()
    {
        for (auto chunk : chunk_vec) free(chunk);
    }
    void setName(std::string s) { name = s; }
    void setChunk(Chunk* chunk_ptr)
    {
        chunk_vec.push_back(chunk_ptr);
    }
};


#endif