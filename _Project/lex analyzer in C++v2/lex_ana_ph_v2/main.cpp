#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

int isKeyword(char lexeme[]) {
    char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default",
                             "do", "double", "else", "enum", "extern", "float", "for", "goto",
                             "if", "int", "long", "register", "return", "short", "signed",
                             "sizeof", "static", "struct", "switch", "typedef", "union",
                             "unsigned", "void", "cout", "while"};
    int i, flag = 0;

    for (i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], lexeme) == 0) {
            flag = 1;
            break;
        }
    }

    return flag;
}

int main() {
    char character, lexeme[15], numericBuffer[30], logicalOps[] = "><", mathOps[] = "+-*/=", numer[] = ".0123456789", other[] = ",;\(){}[]'':";

    ifstream file("Ak.txt");

    int charMark[1000] = {0};
    int i, j = 0, keywordCount = 0, identifierCount = 0, logicalOpCount = 0, mathOpCount = 0, numericValueCount = 0, otherCharCount = 0, numericBufferIndex = 0;
    
    vector<string> keywords;
    vector<char> identifiers;
    vector<char> logicalOperators;
    vector<char> mathOperators;
    vector<string> numericValues;
    vector<char> otherCharacters;

    if (!file.is_open()) {
        cout << "Error while opening the file\n";
        exit(0);
    }

    while (!file.eof()) {
        character = file.get();

        for (i = 0; i < 12; ++i) {
            if (character == other[i]) {
                int asciiValue = character;
                if (charMark[asciiValue] != 1) {
                    otherCharacters.push_back(character);
                    charMark[asciiValue] = 1;
                    ++otherCharCount;
                }
            }
        }

        for (i = 0; i < 5; ++i) {
            if (character == mathOps[i]) {
                int asciiValue = character;
                if (charMark[asciiValue] != 1) {
                    mathOperators.push_back(character);
                    charMark[asciiValue] = 1;
                    ++mathOpCount;
                }
            }
        }

        for (i = 0; i < 2; ++i) {
            if (character == logicalOps[i]) {
                int asciiValue = character;
                if (charMark[asciiValue] != 1) {
                    logicalOperators.push_back(character);
                    charMark[asciiValue] = 1;
                    ++logicalOpCount;
                }
            }
        }

        if (isdigit(character) || character == '.') {
            if (isdigit(character) || character == '.') {
                numericBuffer[numericBufferIndex++] = character;
            }

            if ((isspace(character) || character == ';') && (numericBufferIndex != 0)) {
                numericBuffer[numericBufferIndex] = '\0';
                numericBufferIndex = 0;
                char numericArray[30];
                strcpy(numericArray, numericBuffer);
                numericValues.push_back(numericArray);
                ++numericValueCount;
            }
        }

        if (isalnum(character)) {
            lexeme[j++] = character;
        } else if ((isspace(character) || character == '\n') && (j != 0)) {
            lexeme[j] = '\0';
            j = 0;

            if (isKeyword(lexeme) == 1) {
                keywords.push_back(lexeme);
                ++keywordCount;
            } else {
                if (lexeme[0] >= 97 && lexeme[0] <= 122) {
                    int asciiValue = lexeme[0];
                    if (charMark[asciiValue] != 1) {
                        identifiers.push_back(lexeme[0]);
                        ++identifierCount;
                        charMark[asciiValue] = 1;
                    }
                }
            }
        }
    }

    file.close();

    cout << "Keywords: ";
    for (int f = 0; f < keywordCount; ++f) {
        if (f == keywordCount - 1) {
            cout << keywords[f] << "\n";
        } else {
            cout << keywords[f] << ", ";
        }
    }

    cout << "Identifiers: ";
    for (int f = 0; f < identifierCount; ++f) {
        if (f == identifierCount - 1) {
            cout << identifiers[f] << "\n";
        } else {
            cout << identifiers[f] << ", ";
        }
    }

    cout << "Math Operators: ";
    for (int f = 0; f < mathOpCount; ++f) {
        if (f == mathOpCount - 1) {
            cout << mathOperators[f] << "\n";
        } else {
            cout << mathOperators[f] << ", ";
        }
    }

    cout << "Logical Operators: ";
    for (int f = 0; f < logicalOpCount; ++f) {
        if (f == logicalOpCount - 1) {
            cout << logicalOperators[f] << "\n";
        } else {
            cout << logicalOperators[f] << ", ";
        }
    }

    cout << "Numerical Values: ";
    for (int f = 0; f < numericValueCount; ++f) {
        if (f == numericValueCount - 1) {
            cout << numericValues[f] << "\n";
        } else {
            cout << numericValues[f] << ", ";
        }
    }

    cout << "Other Characters: ";
    for (int f = 0; f < otherCharCount; ++f) {
        if (f == otherCharCount - 1) {
            cout << otherCharacters[f] << "\n";
        } else {
            cout << otherCharacters[f] << " ";
        }
    }

    return 0;
}

