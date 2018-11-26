#include <fstream>
#include <iomanip>
#include "Scanner.h"
#include "TokenScannerFactory.h"
#include <cstdlib>

using std::ifstream;
using std::cout;
using std::endl;

void testScanner() {
    ifstream fin;
    fin.open("in.smt");
    if (!fin.is_open()) {
        cout << "OPEN FILE FAILED!\n";
        exit(-1);
    }

    Scanner scanner(fin);
    cout <<"(" << scanner.line() << "," << scanner.col() << ") -> ";
    char ch = 0; 
    while (scanner.next()) {
        ch = scanner.curr();
        cout << ch << endl;
        cout <<"(" << scanner.line() << "," << scanner.col() << ") -> ";
    }
    cout << "EOF" << endl;
    cout << std::boolalpha << "EOF: " << scanner.iseof() << endl;
    cout << "CURSOR: " << scanner.line() << "," << scanner.col() << endl;
    fin.close();
}

void testTokenScanner() {
    ifstream fin;
    fin.open("in.smt");
    if (!fin.is_open()) {
        cout << "OPEN FILE FAILED!\n";
        exit(-1);
    }


    Scanner scanner(fin);

    TokenScanner::initNormalizedTable();
    TokenScannerFactory factory;

    TokenScanner* ts = nullptr;
    Token* result = nullptr;
    char sign = 0;
    while(scanner.skip()) {

        sign = TokenScanner::id(scanner.curr());
        ts = factory.getTokenScanner(sign);
        result = ts->scan(scanner);
        if (result->type() != EOF_TOKEN)
            result->display();
        cout << endl;
        delete ts;
        delete result;
    }

    fin.close();

}

int main()
{
    // testScanner(); 
    testTokenScanner();
    return 0;
}
