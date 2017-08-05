#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <string>
#include <unordered_map>

#include "token.h"
#include "constants.h"

class Lexer
{
public:
    Lexer(std::string fileName, std::unordered_map<std::string, Token> &symbolTable);
    ~Lexer();

    // Функция возвращает следующий токен
    Token getNextToken();

    // Функция просматривает следующий токен,
    // и оставляет его для вызова getNextToken()
    Token lookNextToken();
    
private:
    std::ifstream file;
    // Ссылка на таблицу символов
    std::unordered_map<std::string, Token> &symbolTable;

    char leftBuffer[lexerBufferSize];
    char rightBuffer[lexerBufferSize];
    char * lexemeBegin;
    char * forward;

    int state;

    // Флаг устанавливается в true если достигнут конец обрабатываемого файла
    bool endFlag;

    bool isLooked;
    Token saveToken;

    // Функция прибавляет единицу к указателю lexemBegin
    // и если нужно переключает его на другой буффер
    void lexemeBeginPlusPlus();
};

#endif // LEXER_H
