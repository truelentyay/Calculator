#ifndef INPUT_H
#define INPUT_H
#include <string>

class Input
{
public:
    Input(std::string str);
    std::string takeExpressionFromPos();
    char takeOperationFromPos();
    void setPos(size_t pos);
    size_t getPos();
    std::string getStr();
    void setStr(std::string str);
    char getFormat();

private:
    std::string m_str;
    size_t m_pos;
    char m_format;
};

#endif // INPUT_H
