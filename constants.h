#ifndef CONSTANTS_H
#define CONSTANTS_H

// размера буффера чтения лексического анализатора
const char lexerBufferSize = 101;

// зарезервированные слова
const int keyWordCount = 7 /*7*/;
const char keyWords[][keyWordCount] = { "int", "char", /*"main",*/ "return", "if", "else", "while" };

#endif // CONSTANTS_H
