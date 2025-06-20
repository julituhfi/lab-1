#include <stdio.h>
#include <ctype.h>
#include <clocale>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define TRUE 1
#define FALSE 0


int isValid(char ch, int pos) {
    int pattern_pos = pos % 4;

    switch (pattern_pos) {
    case 0:
        return isdigit(ch);
    case 1:
        return isdigit(ch) && ((ch - '0') % 2 == 0);
    case 2:
    case 3:
        return isalpha(ch);
    default:
        return FALSE;
    }
}


int validatePattern(const char set[], int size) {
    for (int i = 0; i < size; i++) {
        if (!isValid(set[i], i)) {
            printf("Ошибка! Символ '%c' на позиции %d не соответствует шаблону cibb\n",
                set[i], i + 1);
            return FALSE;
        }
    }
    return TRUE;
}

void inputSet(char set[], int* size, const char* name) {
    char input[MAX_SIZE * 2];
    int attempt = 0;

    while (attempt < 3) {
        printf("Введите элементы множества %s (шаблон cibb - цифра, четная цифра, буква, буква): ", name);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Ошибка чтения ввода!\n");
            continue;
        }


        input[strcspn(input, "\n")] = '\0';

        *size = 0;
        int error = FALSE;


        for (int i = 0; input[i] != '\0' && *size < MAX_SIZE; i++) {
            if (input[i] == ' ') continue;


            if (!isValid(input[*size], *size)) {
                printf("Ошибка! Символ '%c' на позиции %d не соответствует шаблону cibb\n",
                    input[i], *size + 1);
                error = TRUE;
                break;
            }


            int duplicate = FALSE;
            for (int j = 0; j < *size; j++) {
                if (set[j] == input[i]) {
                    printf("Ошибка! Дубликат символа '%c'\n", input[i]);
                    duplicate = TRUE;
                    break;
                }
            }

            if (duplicate) {
                error = TRUE;
                break;
            }

            set[(*size)++] = input[i];
        }

        if (!error && *size > 0) {
            if (validatePattern(set, *size)) {
                return;
            }
        }

        attempt++;
        printf("Неверный ввод! Попытка %d из 3\n", attempt);


        *size = 0;
    }

    printf("Превышено количество попыток ввода. Программа завершена.\n");
    exit(1);
}

void printSet(const char set[], int size) {
    printf("{ ");
    for (int i = 0; i < size; i++) {
        printf("%c ", set[i]);
    }
    printf("}");
}

int contains(const char set[], int size, char elem) {
    for (int i = 0; i < size; i++) {
        if (set[i] == elem) return TRUE;
    }
    return FALSE;
}

void setUnion(const char A[], int sizeA, const char B[], int sizeB, char result[], int* sizeResult) {
    *sizeResult = 0;
    for (int i = 0; i < sizeA; i++) {
        result[(*sizeResult)++] = A[i];
    }
    for (int i = 0; i < sizeB; i++) {
        if (!contains(A, sizeA, B[i])) {
            result[(*sizeResult)++] = B[i];
        }
    }
}

void setIntersection(const char A[], int sizeA, const char B[], int sizeB, char result[], int* sizeResult) {
    *sizeResult = 0;
    for (int i = 0; i < sizeA; i++) {
        if (contains(B, sizeB, A[i])) {
            result[(*sizeResult)++] = A[i];
        }
    }
}

void setDifference(const char A[], int sizeA, const char B[], int sizeB, char result[], int* sizeResult) {
    *sizeResult = 0;
    for (int i = 0; i < sizeA; i++) {
        if (!contains(B, sizeB, A[i])) {
            result[(*sizeResult)++] = A[i];
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    char A[MAX_SIZE], B[MAX_SIZE];
    int sizeA, sizeB;

    inputSet(A, &sizeA, "A");
    inputSet(B, &sizeB, "B");

    printf("\nМножество A: ");
    printSet(A, sizeA);
    printf("\nМножество B: ");
    printSet(B, sizeB);

    char unionSet[MAX_SIZE], intersection[MAX_SIZE];
    char diffAB[MAX_SIZE], diffBA[MAX_SIZE], symDiff[MAX_SIZE];
    int sizeUnion, sizeIntersection, sizeDiffAB, sizeDiffBA, sizeSymDiff;

    setUnion(A, sizeA, B, sizeB, unionSet, &sizeUnion);
    setIntersection(A, sizeA, B, sizeB, intersection, &sizeIntersection);
    setDifference(A, sizeA, B, sizeB, diffAB, &sizeDiffAB);
    setDifference(B, sizeB, A, sizeA, diffBA, &sizeDiffBA);
    setUnion(diffAB, sizeDiffAB, diffBA, sizeDiffBA, symDiff, &sizeSymDiff);

    printf("\n\nРезультаты операций:");
    printf("\nОбъединение A ∪ B: ");
    printSet(unionSet, sizeUnion);

    printf("\nПересечение A ∩ B: ");
    printSet(intersection, sizeIntersection);

    printf("\nРазность A \\ B: ");
    printSet(diffAB, sizeDiffAB);

    printf("\nРазность B \\ A: ");
    printSet(diffBA, sizeDiffBA);

    printf("\nСимметрическая разность A △ B: ");
    printSet(symDiff, sizeSymDiff);

    printf("\n");
    return 0;
}
