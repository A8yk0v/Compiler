#include <iostream>
#include <unordered_map>
#include <utility>

#include "lexer.h"
#include "parser.h"
#include "nodeBase.h"

int main(int argc, char **argv)
{
    try
    {

        if (argc < 2)
        {
            std::cout << "Too few arguments" << std::endl;
            return 0;
        }

        // ---
        // формирование таблицы символов
//        std::vector<Token> symbolTable;
//        for (int i = 0; i < keyWordCount; ++i)
//            symbolTable.push_back( Token("keyWord", keyWords[i]) );
        std::unordered_map<std::string, Token/*, std::hash<std::string>*/> symbolTable;
        for (int i = 0; i < keyWordCount; ++i)
            symbolTable.insert(std::pair<std::string, Token>
                                  (std::string(keyWords[i]), Token("KeyWord", keyWords[i])));
        // ---

        Lexer lexer(argv[1]/*"test1.c"*/, symbolTable);
//        while (true)
//        {
//            Token T("!", "!");
//            T = lexer.getNextToken();
//            if ( T.name == "End" )
//                    break;
//            std::cout << "<" << T.type << ", " << T.name << "> " << std::endl;
//        }

        Parser parser(lexer, symbolTable);

        NodeBase *parserTree = parser.go();

        std::cout << symbolTable.size() << std::endl;
        std::cout << sizeof(symbolTable) << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
