#include "parser.h"

#include <iostream>

using namespace std;

string parse(queue<STToken> tokens) {
    STExecScope sc = to_scope(tokens);
    for (int i = 0; i < sc.vals.size(); i++) {
        cout << "Val " << sc.vals[i].val << " (" << sc.vals[i].obj << ")" <<  endl;
    }
    for (int i = 0; i < sc.nodes.size(); i++) {
        cout << "Node " << sc.nodes[i].op << " ";
        cout << "(left: " << sc.nodes[i].left.ref;
        if (sc.nodes[i].left.type == STLeafRef::Value) {
            cout << " Value)";
        } else {
            cout << " Node)";
        }
        cout << "(right: " << sc.nodes[i].right.ref;
        if (sc.nodes[i].right.type == STLeafRef::Value) {                cout << " Value)";                                     } else {                                                        cout << " Node)";                                       }
        cout << endl;
    }
    return "";
}

void add_node(vector<STNode> &nodes, stack<int> &operands, string op) {
    int node_i = nodes.size();
    STLeaf left;
    left.ref = -1;
    STLeaf right;
    right.ref = -1;
    if (!operands.empty()) {
        left = { operands.top(), STLeafRef::Value };
        operands.pop();
    }
    if (!operands.empty()) {
        right = { left.ref, STLeafRef::Value };     
        left.ref = operands.top();
        operands.pop();                                            }
    if (left.ref == -1 && node_i > 0) {
        node_i -= 1;
        left = { node_i, STLeafRef::Node };
    }
    if (right.ref == -1 && node_i > 0) {
        node_i -= 1;                                                   right = { node_i, STLeafRef::Node };
    }
    
    nodes.push_back({ op, left, right });
    cout << "Creating node with " << op << endl;
}

int record_token(STToken token, STExecScope &sc) {
    switch (token.type) {
        case STTokenType::Integer:
            sc.vals.push_back({ token.val, "Integer" });
            break;
        case STTokenType::Float:
            sc.vals.push_back({ token.val, "Float" });
            break;
        case STTokenType::String:
            sc.vals.push_back({ token.val, "String" });
            break;
    }
    return sc.vals.size() - 1;
}

STExecScope to_scope(queue<STToken> tokens) {
    STExecScope sc;
    stack<STOperator> operators;
    stack<int> operands;

    while (!tokens.empty()) {
        STToken tk = tokens.front(); tokens.pop();
        if (tk.type == STTokenType::Operator) {
            STOperator op = ST_OPS[atoi(tk.val.c_str())];
            if (operators.empty()) {
                operators.push(op);
            } else {
                if (op.val == ")") {
                    while (operators.top().val != "(") {
                        add_node(sc.nodes, operands, operators.top().val);
                        operators.pop();
                    }
                    operators.pop();
                } else {
                    while (!operators.empty() && operators.top().prec > op.prec) {
                        add_node(sc.nodes, operands, operators.top().val);
                        operators.pop();
                    }
                    operators.push(op);
                }
            }
        } else {
            int index = record_token(tk, sc);
            operands.push(index);
        }
    }
    while (!operators.empty()) {
        add_node(sc.nodes, operands, operators.top().val);
        operators.pop();
    }

    return sc;
}



                    



            

/*
    for (int i = 0; i < raw.length(); i++) {
        int op_i = op_index(raw, i);
        if (op_i != -1) {
            if (operators.empty()) {
                operators.push(OPS[op_i]);
            } else {
                while (!operators.empty() && operators.top().prec > OPS[op_i].prec) {
                    expr += operators.top().val;
                    operators.pop();
                }
                operators.push(OPS[op_i]);
            }
        } else if (raw.at(i) == ')') {
            while (operators.top().val != "(") {
                expr += operators.top().val;
                operators.pop();
            }
            operators.pop();
        } else if (raw.at(i) != ' ') {
            expr.push_back(raw.at(i));
        }
    }
    while (!operators.empty()) {
        expr += operators.top().val;
        operators.pop();
    }
    return expr;
}
*/
