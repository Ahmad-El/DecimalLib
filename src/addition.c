#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
    s21_big_decimal first = {0}, second = {0};
    s21_copy_decimal(value_1, &first);
    s21_copy_decimal(value_2, &second);


    for (int i = 32 * 8 -1; i >= 0; i--){
        printf("%d", s21_get_bit(first, i));
        if(i % 32 == 0) printf(" ");
    }
    printf("\n");
    printf("exponent = %d\n", first.exp);    
    printf("sign = %d\n", first.sign);    
    printf("\n");
    s21_shift_right(&first, 5);
    for (int i = 32 * 8 -1; i >= 0; i--){
        printf("%d", s21_get_bit(first, i));
        if(i % 32 == 0) printf(" ");
    }
    printf("\n");
    printf("exponent = %d\n", first.exp);    
    printf("sign = %d\n", first.sign);    
    printf("\n");
    s21_shift_left(&first, 5);
    for (int i = 32 * 8 -1; i >= 0; i--){
        printf("%d", s21_get_bit(first, i));
        if(i % 32 == 0) printf(" ");
    }    
    printf("\n");
    printf("exponent = %d\n", first.exp);    
    printf("sign = %d\n", first.sign);   
    printf("\n");

}

// int s21_normalize(s21_decimal *first, s21_decimal *second){
//     int exp1 = s21_get_exp(*first);
//     int exp2 = s21_get_exp(*second);
//     if(exp1 > exp2){
//         s21_multiply_by_ten(second);
//     }
// }


void s21_copy_decimal(s21_decimal import, s21_big_decimal *export){
    for(int i = 0; i < 3; i ++)
        export->bits[i] = import.bits[i];
    export->bits[7] = import.bits[3];
    export->exp = s21_get_exp(*export);
    export->sign = s21_get_sign(*export);
}
