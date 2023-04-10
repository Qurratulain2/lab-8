Question 1
//Header Definitions
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILE_NAME 100

//Structure Definitions
typedef struct address_t {
    int A;
    int B;
    int C;
    int ID;
    char nickname[500];
} ipAddress;

//Function Declarations
int localnet(ipAddress a[], ipAddress b[]);

//Main Program
int main() {

    ipAddress addresses[500]; // array with structured IP addresses

    char filename[] = "C:\\Users\\qurra\\OneDrive\\Desktop\\datafile.txt"; // path to data file

    int count = 0;

    #pragma region //data extraction

    FILE* dataFile;
    dataFile = fopen(filename, "r");

    if (dataFile == NULL)
    {
        system("CLS");
        printf("Could Not Find/Open File Named '%s' \n", filename);
        return 0;
    }

    //read in IP addresses and nicknames
    while (fscanf(dataFile, "%d.%d.%d.%d %s", &addresses[count].A, &addresses[count].B, &addresses[count].C, &addresses[count].ID, addresses[count].nickname) == 5) {
        count++;
    }

    fclose(dataFile);

    #pragma endregion

    //print out list of all IP addresses and nicknames
    printf("Full List of IP Addresses and Nicknames:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %d.%d.%d.%d \t %s\n", i + 1, addresses[i].A, addresses[i].B, addresses[i].C, addresses[i].ID, addresses[i].nickname);
    }

    //identify all pairs of computers from the same locality
    printf("\nPairs of Computers on Same Locality:\n");
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (addresses[i].A == addresses[j].A && addresses[i].B == addresses[j].B) {
                printf("Servers %s and %s are on the same local network.\n", addresses[i].nickname, addresses[j].nickname);
            }
        }
    }

    return 0;
}








Question 2: 

#include <stdio.h>
#include "mylibrary.h"
#define ROWS 10
#define COLS 10

int main() {
    float arr[ROWS][COLS];
    FILE *fp;
    int i, j;
    float result;
    // Read data from file into array
    fp = fopen("L8_real.txt", "r");
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            fscanf(fp, "%f", &arr[i][j]);
        }
    }
    fclose(fp);

    // Calculate and write results to binary file
    fp = fopen("results.bin", "wb");
    result = sumdiag(arr);
    fwrite(&result, sizeof(float), 1, fp);
    result = sumall(arr);
    fwrite(&result, sizeof(float), 1, fp);
    result = avright(arr);
    fwrite(&result, sizeof(float), 1, fp);
    result = corners(arr);
    fwrite(&result, sizeof(float), 1, fp);
    result = largeanti(arr);
    fwrite(&result, sizeof(float), 1, fp);
    fclose(fp);

    // Read results from binary file and display
    fp = fopen("results.bin", "rb");
    fread(&result, sizeof(float), 1, fp);
    printf("The sum of the main diagonal is %.1f.\n", result);
    fread(&result, sizeof(float), 1, fp);
    printf("The sum of all the numbers is %.1f.\n", result);
    fread(&result, sizeof(float), 1, fp);
    printf("The average of the rightmost column is %.1f.\n", result);
    fread(&result, sizeof(float), 1, fp);
    printf("The sum of the four corners is %.1f.\n", result);
    fread(&result, sizeof(float), 1, fp);
    printf("The largest number in the antidiagonal is %.1f.\n", result);
    fclose(fp);

    return 0;
}





Library

#ifndef MYLIBRARY_H
#define MYLIBRARY_H

#include <stddef.h>

float sumdiag(const float arr[10][10]) {
    float sum = 0.0f;
    for (size_t i = 0; i < 10; i++) {
        sum += arr[i][i];
    }
    return sum;
}

float sumall(const float arr[10][10]) {
    float sum = 0.0f;
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j+=4) {
            sum += arr[i][j];
        }
    }
    return sum;
}

float avright(const float arr[10][10]) {
    float sum = 0.0f;
    for (size_t i = 0; i < 10; i++) {
        sum += arr[i][9];
    }
    return sum / 10.0f;
}

float corners(const float arr[10][10]) {
    return arr[0][0] + arr[0][9] + arr[9][0] + arr[9][9];
}

float largeanti(const float arr[10][10]) {
    float largest = arr[0][9];
    for (size_t i = 1; i < 10; i++) {
        size_t j = 9 - i;
        if (arr[i][j] > largest) {
            largest = arr[i][j];
        }
    }
    return largest;
}

#endif



 
Output:


q1
