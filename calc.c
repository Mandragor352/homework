#include <stdio.h>
#include <math.h>

// Функция для перевода градусов в радианы
double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0); // M_PI - константа для π
}

void menu() {
    printf("вУмный калькулятор\n");
    printf("Что он может:\n");
    printf("1. Сложение\n");
    printf("2. Вычитание\n");
    printf("3. Умножение\n");
    printf("4. Деление\n");
    printf("5. Возведение в квадрат\n");
    printf("6. Возведение в заданную степень\n");
    printf("7. Извлечение квадратного корня\n");
    printf("8. Извлечение корня степени a из числа b\n");
    printf("9. Косинус числа (в градусах)\n");
    printf("10. Синус числа (в градусах)\n");
    printf("11. Выход\n");
}

double calc(int choice, double a, double b) {
    switch (choice) {
        case 1: return a + b;
        case 2: return a - b;
        case 3: return a * b;
        case 4: 
            if (b == 0) {
                printf("Ошибка! На ноль делить нельзя.\n");
                return NAN; 
            }
            return a / b;
        case 5: return a * a;
        case 6: return pow(a, b);
        case 7:
            if (a < 0) {
                printf("Ошибка! Квадратный корень из отрицательного числа.\n");
                return NAN;
            }
            return sqrt(a);
        case 8:
            if (a == 0) {
                printf("Ошибка! Невозможно извлечь корень нулевой степени.\n");
                return NAN;
            }
            return pow(b, 1.0 / a);
        case 9: return cos(degrees_to_radians(a)); // Преобразуем градусы в радианы
        case 10: return sin(degrees_to_radians(a)); // Преобразуем градусы в радианы
        default:
            printf("Неверный выбор! Попробуйте снова.\n");
            return NAN;
    }
}

int main() {
    int choice;
    double a, b, result;

    while (1) {
        menu();
        printf("Выберите операцию: ");
        scanf("%d", &choice);

        if (choice == 11) {
            printf("Пока!\n");
            break;
        }

        // Обработка ввода в зависимости от выбора
        if (choice >= 1 && choice <= 4) {
            printf("Введите два числа: ");
            scanf("%lf %lf", &a, &b);
        } else if (choice == 6 || choice == 8) {
            printf("Введите основание (или степень корня) и число: ");
            scanf("%lf %lf", &a, &b);
        } else {
            printf("Введите число: ");
            scanf("%lf", &a);
            b = 0; 
        }

        result = calc(choice, a, b);

        if (!isnan(result)) { // Проверка верен ли результат 
            printf("Ответ: %.2lf\n", result);
        }

        printf("\n");
    }

    return 0;
}
