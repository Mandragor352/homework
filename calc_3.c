#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXSTACK 100  // Размер стека
#define MAXEXPR 100   // Длина выражения

double stack[MAXSTACK];
int stackIndex = 0;    

// Добавление элемента 
void push(double value) {
    if (stackIndex < MAXSTACK) {
        stack[stackIndex++] = value;
    } else {
        printf("Ошибка: переполнение стека\n");
        exit(1);
    }
}

// Извлечение элемента
double pop() {
    if (stackIndex > 0) {
        return stack[--stackIndex];
    } else {
        printf("Ошибка: стек пуст\n");
        exit(1);
    }
}

// Проверка приоритета операторов
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Проверка на корректность выражения
int isValidExpression(const char* infix) {
    int balance = 0; // Для проверки баланса скобок
    int wasOperator = 1; // Последний символ был оператором или скобкой

    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isspace(token)) continue; // Игнорируем пробелы

        if (isdigit(token)) {
            wasOperator = 0; // Последний символ - не оператор
        } else if (token == '(') {
            balance++;
            wasOperator = 1; // Последний символ - открывающая скобка
        } else if (token == ')') {
            balance--;
            if (balance < 0) return 0; 
            wasOperator = 1; // Последний символ - закрывающая скобка
        } else if (strchr("+-*/", token)) {
            if (!wasOperator) return 0; 
            wasOperator = 1; 
        } else {
            return 0; // Неизвестный символ
        }
    }

    return balance == 0 && !wasOperator; // Все скобки закрыты и не закончилось оператором
}

// Преобразование в обратную польскую нотацию
void infixToRPN(const char* infix, char* postfix) {
    char stack[MAXSTACK];
    int stackIndex = 0;
    int postfixIndex = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isspace(token)) continue;

        if (isdigit(token)) {
            postfix[postfixIndex++] = token; 
            if (!isdigit(infix[i + 1])) postfix[postfixIndex++] = ' ';
        } else if (token == '(') {
            stack[stackIndex++] = token; 
        } else if (token == ')') {
            
            while (stackIndex > 0 && stack[stackIndex - 1] != '(') {
                postfix[postfixIndex++] = stack[--stackIndex];
                postfix[postfixIndex++] = ' ';
            }
            if (stackIndex > 0) stackIndex--; 
        } else if (strchr("+-*/", token)) {
           
            while (stackIndex > 0 && precedence(stack[stackIndex - 1]) >= precedence(token)) {
                postfix[postfixIndex++] = stack[--stackIndex];
                postfix[postfixIndex++] = ' ';
            }
            stack[stackIndex++] = token;
        }
    }

    // Переносим оставшиеся операторы из стека в постфиксное выражение
    while (stackIndex > 0) {
        postfix[postfixIndex++] = stack[--stackIndex];
        postfix[postfixIndex++] = ' ';
    }

    postfix[postfixIndex - 1] = '\0'; // Завершаем строку
}

// Подсчет всего
void evaluateRPN(const char *expr) {
    const char *token = expr;

    while (*token != '\0') {
        if (isdigit(*token) || (*token == '-' && isdigit(*(token + 1)))) {
            push(strtod(token, (char**)&token));
        } else if (strchr("+-*/", *token)) {
            double operand2 = pop();
            double operand1 = pop();

            switch (*token) {
                case '+': push(operand1 + operand2); break;
                case '-': push(operand1 - operand2); break;
                case '*': push(operand1 * operand2); break;
                case '/':
                    if (operand2 != 0) {
                        push(operand1 / operand2);
                    } else {
                        printf("Ошибка: деление на ноль\n");
                        exit(1);
                    }
                    break;
            }
            token++;
        } else {
            token++;
        }
    }

    printf("Результат: %f\n", pop());
}

int main() {
    char infix[MAXEXPR];
    char postfix[MAXEXPR];

    printf("вУмный калькулятор 1.3\n");

    printf("Считает не сложные выражения.\n");
    printf("Введите выражение: ");
    fgets(infix, sizeof(infix), stdin);

    // Проверка на корректность выражения
    if (!isValidExpression(infix)) {
        printf("Ошибка: некорректное выражение\n");
        return 1;
    }

    infixToRPN(infix, postfix);
    printf("Выражение в обратной польской нотации: %s\n", postfix);

    evaluateRPN(postfix);
    return 0;
}
