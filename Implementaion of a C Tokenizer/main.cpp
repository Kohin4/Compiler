#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <cctype>

using namespace std;


string keywordList[] = {
    "auto","break","case","char","const","continue","default","do","double","else",
    "enum","extern","float","for","goto","if","int","long","register","return",
    "short","signed","sizeof","static","struct","switch","typedef","union","unsigned",
    "void","volatile","while","inline","restrict","_Bool","_Complex","_Imaginary"
};

int keywordCount = sizeof(keywordList) / sizeof(keywordList[0]);


set<string> keywords;
set<string> identifiers;
set<string> constants;
set<string> operatorsSet;
set<string> symbols;


bool isKeyword(string word) {

    for (int i = 0; i < keywordCount; i++) {

        if (word == keywordList[i])
            return true;
    }

    return false;
}


bool isIdentifier(string word) {

    if (!(isalpha(word[0]) || word[0] == '_'))
        return false;

    for (char c : word) {

        if (!(isalnum(c) || c == '_'))
            return false;
    }

    return true;
}


bool isConstant(string word) {

    bool number = true;

    for (char c : word) {

        if (!isdigit(c) && c != '.') {
            number = false;
            break;
        }
    }

    if (number)
        return true;


    if ((word.front() == '"' && word.back() == '"') ||
        (word.front() == '\'' && word.back() == '\''))
        return true;

    return false;
}

bool isOperator(char c) {

    string ops = "+-*/%=<>!&|";

    return ops.find(c) != string::npos;
}


bool isSymbol(char c) {

    string sym = ";,(){}[]#";

    return sym.find(c) != string::npos;
}


void saveToken(string token) {

    if (token.empty())
        return;

    if (isKeyword(token))
        keywords.insert(token);

    else if (isIdentifier(token))
        identifiers.insert(token);

    else if (isConstant(token))
        constants.insert(token);
}


void tokenize(string code) {

    string token;

    for (int i = 0; i < code.size(); i++) {

        char ch = code[i];


        if (ch == '"' || ch == '\'') {

            saveToken(token);
            token.clear();

            char quote = ch;

            string temp;
            temp += ch;

            i++;

            while (i < code.size()) {

                temp += code[i];

                if (code[i] == quote)
                    break;

                i++;
            }

            constants.insert(temp);
        }


        else if (isOperator(ch)) {

            saveToken(token);
            token.clear();

            string op(1, ch);

            if (i + 1 < code.size()) {

                string two = op + code[i + 1];

                if (two == "==" || two == "!=" ||
                    two == "++" || two == "--" ||
                    two == ">=" || two == "<=" ||
                    two == "&&" || two == "||") {

                    operatorsSet.insert(two);
                    i++;
                    continue;
                }
            }

            operatorsSet.insert(op);
        }

        else if (isSymbol(ch)) {

            saveToken(token);
            token.clear();

            string sym(1, ch);
            symbols.insert(sym);
        }

        else if (isspace(ch)) {

            saveToken(token);
            token.clear();
        }

        else {

            token += ch;
        }
    }

    saveToken(token);
}

void showOutput() {

    auto print = [](string name, set<string> data) {

        cout << "\n" << name << " : ";

        for (string x : data)
            cout << x << " ";
    };

    print("Keywords", keywords);
    print("Identifiers", identifiers);
    print("Constants", constants);
    print("Operators", operatorsSet);
    print("Symbols", symbols);

    cout << endl;
}

int main() {

    ifstream file("input.c");

    if (!file) {

        cout << "input.c file not found!" << endl;
        return 0;
    }

    stringstream buffer;
    buffer << file.rdbuf();

    string code = buffer.str();

    tokenize(code);

    showOutput();

    return 0;
}
