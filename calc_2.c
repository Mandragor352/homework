#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXSTACK 100  //Размер стека
#define MAXEXPR 100   //Длина выражения

double stack[MAXSTACK];
int stackIndex = 0;    

//Добавление элемента 
void push(double value) {
    if (stackIndex < MAXSTACK) {
        stack[stackIndex++] = value;
    } else {
        printf("Ошибка: переполнение стека\n");
        exit(1);
    }
}

//Извлечение элемента
double pop() {
    if (stackIndex > 0) {
        return stack[--stackIndex];
    } else {
        printf("Ошибка: стек пуст\n");
        exit(1);
    }
}

//Проверка приоритета операторов
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

//Преобразование в обратную польскую нотацию
void infixToRPN(char* infix, char* postfix) {
    char stack[MAXSTACK];
    int stackIndex = 0;
    int postfixIndex = 0;

    for (int i = 0; i < strlen(infix); i++) {
        char token = infix[i];

        if (token == ' ') continue;

        if (isdigit(token)) {
            postfix[postfixIndex++] = token;
            
            if (!isdigit(infix[i + 1])) postfix[postfixIndex++] = ' ';
        }

        else if (token == '(') {
            stack[stackIndex++] = token;
        } 
        else if (token == ')') {
            while (stackIndex > 0 && stack[stackIndex - 1] != '(') {
                postfix[postfixIndex++] = stack[--stackIndex];
                postfix[postfixIndex++] = ' ';
            }
            stackIndex--; // Удаляем '(' из стека
        }
        // Если токен - оператор
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (stackIndex > 0 && precedence(stack[stackIndex - 1]) >= precedence(token)) {
                postfix[postfixIndex++] = stack[--stackIndex];
                postfix[postfixIndex++] = ' ';
            }
            stack[stackIndex++] = token;
        }
    }

    // Переносим оставшиеся операторы из стека в выходную строку
    while (stackIndex > 0) {
        postfix[postfixIndex++] = stack[--stackIndex];
        postfix[postfixIndex++] = ' ';
    }

    postfix[postfixIndex - 1] = '\0'; 
}

//Подсчёт всего
void evaluateRPN(char *expr) {
    char *token = expr;

    while (*token != '\0') {
        if (isdigit(*token) || (*token == '-' && isdigit(*(token + 1)))) {
            push(strtod(token, &token));
        } else if (*token == '+' || *token == '-' || *token == '*' || *token == '/') {

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

    printf("Введите выражение: ");
    fgets(infix, sizeof(infix), stdin);

    infixToRPN(infix, postfix);
    printf("Выражение в обратной польской нотации: %s\n", postfix);

    evaluateRPN(postfix);
    return 0;
}
