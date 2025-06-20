#include <stdio.h>
#include <clocale>

#define MAX_SIZE 100

int isValid(char ch, int pos) {
    if (pos % 4 == 0) return ch >= '0' && ch <= '9';      // c - цифра
    if (pos % 4 == 1) return (ch >= '0' && ch <= '9') && ((ch - '0') % 2 == 0); // i - четная цифра
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'); // b - буква
}

void inputSet(char set[], int* size, const char* name) {
    printf("Введите элементы множества %s (тип cibb): ", name);
    char ch;
    *size = 0;

    while ((ch = getchar()) != '\n') {
        if (isValid(ch, *size % 4)) {
            int duplicate = 0;
            for (int i = 0; i < *size; i++) {
                if (set[i] == ch) {
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate && *size < MAX_SIZE) {
                set[(*size)++] = ch;
            }
        }
    }
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
        if (set[i] == elem) return 1;
    }
    return 0;
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

    return 0;
}