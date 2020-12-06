#define FRACTION (1<<14)

int sub_int_float(int, int);
int mul_int_float(int, int);
int add_float_int(int, int);
int div_float_int(int, int);
int mul_float_float(int, int);
int div_float_float(int, int);
int add_float_float(int, int);
int sub_float_float(int, int);

int sub_int_float(int i, int f){
    return i * FRACTION - f;
}

int mul_int_float(int i, int f){
    return i * f;
}

int add_float_int(int f, int i){
    return f + i * FRACTION;
}

int div_float_int(int f, int i){
    return f / i;
}

int mul_float_float(int f1, int f2){
    // Using 64bit data for avoid overflow.
    int64_t temp = f1;

    temp = temp * f2 / FRACTION;
    return (int)temp;
}

int div_float_float(int f1, int f2){
    int64_t temp = f1;

    temp = temp * FRACTION / f2;
    return (int)temp;
}

int add_float_float(int f1, int f2){
    return f1 + f2;
}

int sub_float_float(int f1, int f2){
    return f1 - f2;
}
