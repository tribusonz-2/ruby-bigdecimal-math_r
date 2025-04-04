#ifndef INTERNAL_API_BIGMATH
#define INTERNAL_API_BIGMATH

/* API for BigMath */
VALUE rb_bigmath_const_pi(VALUE prec);
VALUE rb_bigmath_const_e(VALUE prec);
VALUE rb_bigmath_const_log2(VALUE prec);
VALUE rb_bigmath_const_log10(VALUE prec);
VALUE rb_bigmath_const_sqrt2(VALUE prec);
VALUE rb_bigmath_const_sqrt3(VALUE prec);

VALUE rb_bigmath_exp(VALUE x, VALUE prec);
VALUE rb_bigmath_cexp(VALUE z, VALUE prec);

VALUE rb_bigmath_log(VALUE x, VALUE prec);
VALUE rb_bigmath_clog(VALUE z, VALUE prec);

VALUE rb_bigmath_pow(VALUE x, VALUE y, VALUE prec);
VALUE rb_bigmath_cpow(VALUE z, VALUE w, VALUE prec);

VALUE rb_sincos_to_radian(VALUE x, VALUE prec, VALUE pi, VALUE *t);
int rb_degree_sparg(VALUE t, VALUE prec, VALUE *sin, VALUE *cos);
void rb_bigmath_sincos(VALUE x, VALUE prec, VALUE *sin, VALUE *cos);

VALUE rb_bigmath_atan(VALUE x, VALUE prec);
VALUE rb_bigmath_quadrant(VALUE x, VALUE y, VALUE prec);
VALUE rb_bigmath_hypot(VALUE a, VALUE b, VALUE prec);

VALUE rb_bigmath_sqrt(VALUE x, VALUE prec);
VALUE rb_bigmath_csqrt(VALUE z, VALUE prec);

VALUE rb_bigmath_l2norm(VALUE vec, VALUE prec);

VALUE rb_bigmath_cabs(VALUE z, VALUE prec);
VALUE rb_bigmath_carg(VALUE z, VALUE prec);

typedef VALUE (*bigmath_func1)(VALUE x, VALUE prec);

VALUE rb_bigmath_api_call1(VALUE x, VALUE prec, bigmath_func1 func_ptr);

typedef VALUE (*bigmath_func2)(VALUE x, VALUE y, VALUE prec);

VALUE rb_bigmath_api_call2(VALUE x, VALUE y, VALUE prec, bigmath_func2 func_ptr);

#endif /* INTERNAL_API_BIGMATH */
