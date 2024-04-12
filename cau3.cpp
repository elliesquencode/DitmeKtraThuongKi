#include <stdio.h>
#include <stdlib.h>

// Định nghĩa hàm đọc dữ liệu từ file và trả về mảng động chứa các số nguyên
int *readFile(const char *filename, int *length)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Không thể mở file %s\n", filename);
        exit(1);
    }

    // Đọc số lượng phần tử từ dòng đầu tiên
    fscanf(file, "%d", length);
    int *numbers = (int *)malloc((*length) * sizeof(int));

    // Đọc từng số nguyên
    for (int i = 0; i < *length; i++)
    {
        fscanf(file, "%d", &numbers[i]);
    }

    fclose(file);
    return numbers;
}

// Định nghĩa hàm ghi mảng vào file
void writeFile(const char *filename, int *numbers, int length)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Không thể mở file %s\n", filename);
        exit(1);
    }

    // Ghi số lượng phần tử vào dòng đầu tiên
    fprintf(file, "%d\n", length);

    // Ghi từng số nguyên vào file, cách nhau bởi khoảng trắng
    for (int i = 0; i < length; i++)
    {
        fprintf(file, "%d ", numbers[i]);
    }

    fclose(file);
}

// Hàm so sánh cho hàm qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Hàm kết hợp và sắp xếp mảng tăng dần
int *mergeAndSort(int *arr1, int len1, int *arr2, int len2, int *resultLength)
{
    // Kết hợp hai mảng
    int *merged = (int *)malloc((len1 + len2) * sizeof(int));
    for (int i = 0; i < len1; i++)
    {
        merged[i] = arr1[i];
    }
    for (int i = 0; i < len2; i++)
    {
        int found = 0;
        for (int j = 0; j < len1; j++)
        {
            if (arr2[i] == arr1[j])
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            merged[len1++] = arr2[i];
        }
    }

    // Sắp xếp mảng kết quả tăng dần
    qsort(merged, len1, sizeof(int), compare);
    *resultLength = len1;
    return merged;
}

// Hàm merge file
void mergeFiles(const char *filename1, const char *filename2)
{
    int *arr1, *arr2;
    int len1, len2;
    arr1 = readFile(filename1, &len1);
    arr2 = readFile(filename2, &len2);

    // Kết hợp và sắp xếp mảng
    int resultLength;
    int *merged = mergeAndSort(arr1, len1, arr2, len2, &resultLength);

    // Xuất kết quả ra màn hình
    printf("%d\n", resultLength);
    for (int i = 0; i < resultLength; i++)
    {
        printf("%d ", merged[i]);
    }
    printf("\n");

    // Giải phóng bộ nhớ
    free(arr1);
    free(arr2);
    free(merged);
}

int main()
{
    const char *fsource1 = "F10.txt";
    const char *fsource2 = "E10.txt";

    mergeFiles(fsource1, fsource2);

    return 0;
}
