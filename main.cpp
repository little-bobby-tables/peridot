#include <iostream>
#include "parser.h"
#include "tokenizer.h"
#include "evaluator.h"

#include "lang/core.h"

using namespace std;

int main(void) {
    cout << "Nope 0.1" << endl;

    Lang::Core c;
    string line = "";
    while (true) {
        cout << "nope=> ";
        getline(cin, line);

        if (line == "exit") break;
        std::istringstream is(mystring); /* TODO: dirty! */
        c.parse(is);
    }

    /*

    STExecScope *sc = new STExecScope();
    Evaluator e(sc);
    Parser p(sc);

    string line = "";
    while (true) {
        e.clear_scope();
        cout << "nope=> ";
        getline(cin, line);
        if (line == "exit") break;
        std::queue<STToken> tks = tokenize(line);
        std::queue<STToken> dbg;
        while (!tks.empty()) {
            cout << "Token " << tks.front().val << endl;
            dbg.push(tks.front());
            tks.pop();
        }
        cout << line << endl;
        p.parse_to_scope(dbg);
        cout << e.eval().val << endl;
    }*/

    return 0;
}

