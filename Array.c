#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


float min(float numbers[1000], int i, float epsilon){
    float cur;
    
    cur = numbers[0];
    for (int j = 1; j<= i; j++){
        
        if ( cur - numbers[j] > 0){
            cur = numbers[j];
        }
    }
    return cur;
}

float max(float numbers[1000], int i, float epsilon){
    float cur;
    
    cur = numbers[0];
    for (int j = 1; j<= i; j++){
        
        if ( cur - numbers[j] < 0){
            cur = numbers[j];
        }
    }
    return cur;
}

float average(float numbers[], int i){
    float sum = 0;
    for (int j=0; j<=i; j++){
        sum += numbers[j];
    }
    return sum/i;
}


float rms(float numbers[], int i){
    float sum = 0, aver;
    aver = average(numbers, i);
    for (int j=0; j<=i; j++){
        sum += pow((numbers[j] - aver), 2);
    }
    return sqrtf(sum/i);
}

int count_same_elemf(float numbers[], int i, float epsilon){
    int cur = 1;
    int max_cur = 1;

    for (int j=0; j<i-1; j++){
        if (fabsf(numbers[j] - numbers[j + 1]) < epsilon){
            cur += 1;
        }
        else {
            if (cur > max_cur){
                max_cur = cur;
            }    
        }
    }
    if (cur > max_cur){
        max_cur = cur;
    }
    return max_cur;
}


int compare(const void* a, const void*b, float epsilon){
    float x =  *(const float *)a;
    float y =  *(const float *)b;

    if (fabsf(x - y) < epsilon){
        return 0;
    }
    else if (x-y > 0) {
        return 1;
    }
    else {
        return -1;
    }
}



int monoton(float numbers[], int i, float epsilon){
    if (i < 2){return 0;}
    int cur_plus = 1, cur_min = 1;
    int max_cur = -1;

    // num[j] это первый элемент (for delete)
    for (int j=0; j<i-1; j++){
        if (compare(&numbers[j], &numbers[j+1], epsilon) == 0){
            cur_plus++;
            cur_min++;
        }


        else if (compare(&numbers[j], &numbers[j+1], epsilon) == -1) {
            if (cur_plus >= cur_min) {
                cur_plus++;
                cur_min = 1;
            }
            else{
                if(max_cur < cur_min){ 
                    max_cur = cur_min; 
                    
                }
                cur_plus = 2; 
                cur_min = 1;      
            }
        }

        else {
            if (cur_plus <= cur_min) {
                cur_min++;
                cur_plus = 1;
            }
            else{
                if(max_cur < cur_plus){ 
                    max_cur = cur_plus; 
                }
                cur_plus = 1; 
                cur_min = 2;
            }
        }
    }
    if (cur_plus > max_cur && cur_plus > cur_min) {
        max_cur = cur_plus;
    }
    else if (cur_min > max_cur && cur_min > cur_plus){
        max_cur = cur_min;
        }
    else if (cur_plus == cur_min && cur_plus > max_cur){ 
        max_cur = cur_plus;
    }
     return max_cur;
}
    
int compare_sort(const void* a, const void* b){
    float x =  *(const float *)a;
    float y =  *(const float *)b;
    if (x > y){
        return 1;
    }
    if (x < y){
        return -1;
    }
    return 0;   
}



float median(float numbers[], int i){
    float median;
    qsort(numbers, i, sizeof(float), compare_sort);

    if (i % 2 == 0){
        median = (numbers[i/2 - 1] + numbers[i/2])/2;
    }

    else {
        median = numbers[i / 2];
    }
    return median;
}


int main(void)
{   printf("Можно начинать ввод\n");
    // create array
    float numbers[1000];
    char code = '-', input_code = ' ';
    int i = 0, true_input=1;
    float epsilon = 0.0001;
    
    while (true_input == 1 && i <= 999){
        float input;
        if (scanf("%f", &input) == 1){
            numbers[i++] = input;
        }
        else {
            true_input = 0;
        }
    }
    //массив наполнен, i это число элементов в массиве
/*    printf("i = %d\n", i);
  printf("min = %f\n", min(numbers, i, epsilon));
    printf("max = %f\n", max(numbers, i, epsilon));
    printf("aver = %f\n", average(numbers, i));
    printf("rms = %f\n", rms(numbers, i)); 
    printf("rms = %f\n", rms(numbers, i));
    printf("same = %d\n", count_same_elemf(numbers, i, epsilon));
    printf("monoton = %d\n", monoton(numbers, i, epsilon));
    */
   printf("median = %f\n", median(numbers, i));
    return 0;
}





