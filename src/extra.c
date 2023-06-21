#include "s21_decimal.h"

int s21_get_bit(s21_big_decimal value, int bit){
    unsigned int mask = 1u << (bit % 32);
    return (value.bits[bit/32] & mask) ? 1: 0; 
}

void s21_set_bit(s21_big_decimal *result, int bit, int value){
    unsigned int mask = 1u << (bit % 32);
    if(value) result->bits[bit/32] |=mask;
    else result->bits[bit/32] &= ~mask;
}

int s21_get_exp(s21_big_decimal value){
    unsigned int mask = 255 << 16;
    mask = value.bits[7] & mask;
    mask = mask << 1;
    mask = mask >> 17;
    return mask;
}

void s21_set_exp(s21_big_decimal *result, int new_exp){
    unsigned int mask = new_exp;
    int sign = s21_get_sign(*result);
    mask = mask << 16;
    result->bits[7] = 0;
    result->bits[7] |= mask;
    if(sign) s21_set_sign(result);
    result->exp = s21_get_exp(*result);
}


int s21_get_sign(s21_big_decimal value) { 
    unsigned int mask = value.bits[7] >> 31;   
    return (mask)? 1: 0;
}

void s21_set_sign(s21_big_decimal *value) { 
    unsigned int mask = 1u << 31;
    value->bits[7] |= mask; 
}


void s21_shift_right(s21_big_decimal *origin, int shift){
    s21_big_decimal value = *origin;
    int i = 0;
    for (; i < (32 * 7) - shift; i ++){
        s21_set_bit(&value, i, s21_get_bit(value, i + shift));
    }
    for(; i < 32 * 7; i++)
        s21_set_bit(&value, i, 0);
    *origin = value;
}

void s21_shift_left(s21_big_decimal *origin, int shift){
    s21_big_decimal value = *origin;
    int i = 32 * 7 - 1;
    for (; i > shift; i --){
        s21_set_bit(&value, i, s21_get_bit(value, i - shift));
    }
    for (i = i -1; i >= 0; i--)
        s21_set_bit(&value, i, 0);
    
    s21_set_exp(&value, 255);
    *origin = value;
}


// reserve working
// void s21_shift_right(s21_big_decimal *value){
//     int i = 0;
//     for (; i < (32 * 7) - 1; i ++){
//         s21_set_bit(value, i, s21_get_bit(*value, i + 1));
//     }
//     s21_set_bit(value, 7 * 32 -1, 0);
// }
// void s21_shift_left(s21_big_decimal *value){
//     int i = 32 * 7 - 1;
//     for (; i > 0; i --){
//         s21_set_bit(value, i, s21_get_bit(*value, i - 1));
//     }
//     s21_set_bit(value, 0, 0);
// }