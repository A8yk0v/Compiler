#include "lexer.h"

// Test
#include <iostream>

Lexer::Lexer(std::string fileName, std::unordered_map<std::string, Token> &sTable)
    : file(fileName.c_str(), std::fstream::binary), symbolTable(sTable), state(0), endFlag(false),
      isLooked(false), saveToken("!","!")
{
    if ( !file )
    {
        // Ошибка открытия файл
        //throw "error - File not found";
        throw std::invalid_argument( std::string("Compiler - File not found") );
    }

    file.read(leftBuffer, lexerBufferSize-1);
    leftBuffer[file.gcount()] = '\0';

    lexemeBegin = leftBuffer;
    forward = leftBuffer;
}

Lexer::~Lexer()
{
}

void Lexer::lexemeBeginPlusPlus()
{
    lexemeBegin++;
    // lexemeBegin в конце первого буффера?
    if ( lexemeBegin == leftBuffer+lexerBufferSize-1 )
    {
        // Тогда направляем на второй буффер
        lexemeBegin = rightBuffer;
    }
    // lexemeBegin в конце второго буффера?
    if ( lexemeBegin == rightBuffer+lexerBufferSize-1 )
    {
        // Тогда направляем на первый буффер
        lexemeBegin = leftBuffer;
    }
}

Token Lexer::getNextToken()
{        
    // Файл уже был прочитан?
    if ( endFlag )
        // Фиктивный токен
        return Token("End", "End");

    if (isLooked)
    {
        isLooked = false;
        return saveToken;
    }

    while ( true )
    {
        // forward в конце первого буффера?
        if ( forward == leftBuffer+lexerBufferSize-1 )
        {
            // Тогда загружаем второй буффер
            file.read(rightBuffer, lexerBufferSize-1);
            rightBuffer[file.gcount()] = '\0';
            forward = rightBuffer;
        }
        // forward в конце второго буффера?
        if ( forward == rightBuffer+lexerBufferSize-1 )
        {
            // Тогда загружаем первый буффер
            file.read(leftBuffer, lexerBufferSize-1);
            leftBuffer[file.gcount()] = '\0';
            forward = leftBuffer;
        }

        // Конец в ходного потока?
        if ( *forward == '\0' && forward != rightBuffer+lexerBufferSize && forward != leftBuffer+lexerBufferSize)
        {
            break;
            //throw 1;
        }

        switch (state)
        {
            case 0:
                if ( isalpha(*forward) )
                {
                    state = 1;
                    forward++;
                    break;
                }
                if ( isdigit(*forward) )
                {
                    state = 3;
                    forward++;
                    break;
                }
                if ( *forward == '"' )
                {
                    state = 5;
                    forward++;
                    lexemeBeginPlusPlus();
                    break;
                }
                if ( *forward == '*' || *forward == '+' || *forward == '-' )
                {
                    state = 7;
                    forward++;
                    break;
                }
                 if ( *forward == '(' || *forward == ')' || *forward == '{' || *forward == '}' || *forward == ';' )
                {
                    state = 8;
                    //forward++;
                    break;
                }
                if ( *forward == '=' )
                {
                    state = 9;
                    forward++;
                    break;
                }
                if ( *forward == '/' )
                {
                    state = 18;
                    forward++;
                    break;
                }

                // Символ неопределен, двигаемся по входному потоку
                forward++;
                lexemeBeginPlusPlus();
                break;

            // Состояния 1-2 обработка идентификатора
            case 1:
                if ( isalnum(*forward) || *forward == '_' )
                     forward++;
                else
                      state = 2;
                break;
            case 2:
            {
                std::string lexema;
                while ( lexemeBegin != forward )
                {
                     lexema.push_back(*lexemeBegin);
                     lexemeBeginPlusPlus();
                }
                state = 0;

                auto TokenFind = symbolTable.find(lexema);
                if (TokenFind == symbolTable.end() )
                {
                    //symbolTable.insert(std::pair<std::string, Token>
                    //                       (std::string(keyWords[i]), Token("KeyWord", keyWords[i])));
                    symbolTable.insert(std::pair<std::string, Token>
                                                  (std::string(lexema), Token("id", lexema)));
                    return Token("id", lexema);
                }

                return Token(TokenFind->second.type, TokenFind->first);
            }

            // Состояния 3-4 обработка числовой натуральной константы
            case 3:
                if ( isdigit(*forward) )
                    forward++;
                else
                    state = 4;
                break;
            case 4:
            {
                std::string lexema;
                while ( lexemeBegin != forward )
                {
                    lexema.push_back(*lexemeBegin);
                    lexemeBeginPlusPlus();
                }
                state = 0;
                return Token("number", lexema);
            }

            // Состояния 5-6 обработка строковых литералов
            case 5:
                if ( *forward == '"' )
                    state = 6;
                forward++;
                break;
            case 6:
            {
                std::string lexema;
                while ( lexemeBegin != forward-1 )
                {
                    lexema.push_back(*lexemeBegin);
                    lexemeBeginPlusPlus();
                }
                lexemeBegin = forward;
                state = 0;
                return Token("literal", lexema);
            }

            // Состояние 7 обрабатывет лексемы: +, -, *, /
            case 7:
            {
                std::string lexema;
                lexema.push_back(*(forward-1));
                state = 0;
                lexemeBegin = forward;
                return Token("operator", lexema);
            }

            // Состояние 8 обрабатывает лексемы: (, ), {, }, ;
            case 8:
            {
                std::string lexema;
                lexema.push_back(*forward);
                state = 0;
                lexemeBegin = ++forward;
                return Token("operator", lexema);
            }

            // Состояния 9-11 обработка лексем = и ==
            case 9:
                if ( *forward == '=' )
                     state = 10;
                else
                     state = 11;
                break;
            case 10:
                forward++;
                lexemeBegin = forward;
                state = 0;
                return Token("comparison", "==");
            case 11:
                lexemeBegin = forward;
                state = 0;
                return Token("operator", "=");

            // Состояния 18-23 обработка комментариев //... и /*...*/
            case 18:
                if ( *forward == '/' )
                    state = 19;
                else if ( *forward == '*' )
                    state = 21;
                else
                {
                    state = 7;
                    break;
                }
                forward++;
                break;
            case 19:
                if ( *forward == '\n' )
                    state = 20;
                else
                    forward++;
                break;
            case 20:
                state = 0;
                lexemeBegin = forward;
                break;

            case 21:
                if ( *forward == '*' )
                    state = 22;
                forward++;
                break;
            case 22:
                if ( *forward == '/' )
                    state = 23;
                else
                    state = 21;
                forward++;
                break;
            case 23:
                state = 0;
                lexemeBegin = forward;
                break;
        }
    }

    // Достигнут конец файла
    endFlag = true;
    // Фиктивный токен
    return Token("End", "End");
}

Token Lexer::lookNextToken()
{
    if (!isLooked)
    {
        saveToken = getNextToken();
        isLooked = true;
        return saveToken;
    }
    //else
    return saveToken;
}
