#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>

/*
 * RPNCalculator
 * 逆波兰表示法计算器
 */
class RPNCalculator {
private:
    std::stack<double> stk;

public:
    // 入栈
    void push(double value) {
        stk.push(value);
    }

    // 出栈
    double pop() {
        if (stk.empty()) {
            throw std::runtime_error("错误：栈为空，无法取值");
        }
        double v = stk.top();
        stk.pop();
        return v;
    }

    // 执行运算
    void calculate(const std::string& op) {
        double b = pop();
        double a = pop();

        if (op == "+") {
            push(a + b);
        } else if (op == "-") {
            push(a - b);
        } else if (op == "*") {
            push(a * b);
        } else if (op == "/") {
            if (b == 0) {
                throw std::runtime_error("错误：除零");
            }
            push(a / b);
        } else {
            throw std::runtime_error("错误：未知操作符 " + op);
        }
    }

    // 解析并计算表达式
    double evaluate(const std::string& expr) {
        std::stringstream ss(expr);
        std::string token;

        // 清空栈（保证多次输入不互相影响）
        while (!stk.empty()) stk.pop();

        while (ss >> token) {
            if (token == "+" || token == "-" ||
                token == "*" || token == "/") {
                calculate(token);
            } else {
                try {
                    double value = std::stod(token);
                    push(value);
                } catch (...) {
                    throw std::runtime_error("错误：非法输入 " + token);
                }
            }
        }

        if (stk.size() != 1) {
            throw std::runtime_error("错误：表达式不合法，栈中剩余元素不为 1");
        }

        return pop();
    }
};

int main() {
    RPNCalculator calc;
    std::string input;

    std::cout << "C++ RPN 计算器\n";
    std::cout << "输入逆波兰表达式（例如: 1 2 +），输入 q 退出\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "q") {
            std::cout << "退出程序\n";
            break;
        }

        try {
            double result = calc.evaluate(input);
            std::cout << "结果: " << result << "\n";
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
        }
    }

    return 0;
}
