extern "C" {

typedef unsigned int   fp21;
typedef unsigned long  fp21x3;

static inline float convert_fp21_to_float(fp21 a)
{
    a <<= 11;
    float* _a=reinterpret_cast<float*>(&a);
    return _a[0];
}

static inline float convert_fp21x3_to_float3_x(fp21x3 a)
{
    return convert_fp21_to_float( ((fp21)((a >>  0) & 0x1fffff)) );
}

static inline float convert_fp21x3_to_float3_y(fp21x3 a)
{
    return convert_fp21_to_float( ((fp21)((a >> 21) & 0x1fffff)) );
}

static inline float convert_fp21x3_to_float3_z(fp21x3 a)
{
    return convert_fp21_to_float( ((fp21)((a >> 42) & 0x1fffff)) );
}

static inline fp21 convert_float_to_fp21_rz(float a)
{
    unsigned int _a = ((unsigned int*)(&a))[0]; 
    return (_a >> 11);
}

static inline fp21 convert_float_to_fp21_rn(float a)
{
    float a_rz = convert_fp21_to_float( convert_float_to_fp21_rz(a));
    a += (a - a_rz);
    return convert_float_to_fp21_rz(a);
}

static inline fp21 convert_float_to_fp21(float a)
{
    return convert_float_to_fp21_rn(a);
}

static inline fp21x3 convert_floatxyz_to_fp21x3(float a1, float a2, float a3)
{
    fp21x3 b = 0;
    b |= (unsigned long)convert_float_to_fp21(a1) <<  0;
    b |= (unsigned long)convert_float_to_fp21(a2) <<  21;
    b |= (unsigned long)convert_float_to_fp21(a3) <<  42;
    return b;
}

}
