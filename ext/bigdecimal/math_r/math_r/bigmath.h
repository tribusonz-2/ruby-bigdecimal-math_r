#ifndef INTERNAL_API_BIGMATH
#define INTERNAL_API_BIGMATH

/* API for BigMath */
#define DEF_PREC 1000
#define BIGMATH_PI     "$M_PI"
#define BIGMATH_E      "$M_E"
#define BIGMATH_EulerGamma "$M_EulerGamma"
#define BIGMATH_LOG2   "$M_LOG2"
#define BIGMATH_LOG10  "$M_LOG10"
#define BIGMATH_LOG_PI "$M_LOG_PI"
#define BIGMATH_SQRT2  "$M_SQRT2"
#define BIGMATH_SQRT3  "$M_SQRT3"

typedef VALUE (*bigmath_func1)(VALUE x, VALUE prec);
VALUE rb_bigmath_api_call1(VALUE x, VALUE prec, bigmath_func1 func_ptr);

typedef VALUE (*bigmath_func2)(VALUE x, VALUE y, VALUE prec);
VALUE rb_bigmath_api_call2(VALUE x, VALUE y, VALUE prec, bigmath_func2 func_ptr);

VALUE rb_bigmath_const(const char *gv, VALUE (*func)(VALUE prec), VALUE prec);
VALUE rb_bigmath_const_pi(VALUE prec);
VALUE rb_bigmath_const_log_pi(VALUE prec);
VALUE rb_bigmath_const_e(VALUE prec);
VALUE rb_bigmath_const_euler_gamma(VALUE prec);
VALUE rb_bigmath_const_log2(VALUE prec);
VALUE rb_bigmath_const_log10(VALUE prec);
VALUE rb_bigmath_const_sqrt2(VALUE prec);
VALUE rb_bigmath_const_sqrt3(VALUE prec);

VALUE rb_bigmath_exp(VALUE x, VALUE prec);
VALUE rb_bigmath_cexp(VALUE z, VALUE prec);
VALUE rb_bigmath_expxt(VALUE x, VALUE t, VALUE prec);

VALUE rb_bigmath_log(VALUE x, VALUE prec);
VALUE rb_bigmath_clog(VALUE z, VALUE prec);

VALUE rb_bigmath_pow(VALUE x, VALUE y, VALUE prec);
VALUE rb_bigmath_cpow(VALUE z, VALUE w, VALUE prec);
VALUE rb_bigmath_ipow(VALUE x, VALUE n, VALUE exp);

void rb_bigmath_escalb(VALUE a, VALUE x, VALUE prec, VALUE *exp, VALUE *fra);

void rb_bigmath_sincos(VALUE x, VALUE prec, VALUE *sin, VALUE *cos);
int rb_bigmath_degree_sparg(VALUE t, VALUE prec, VALUE *sin, VALUE *cos);
VALUE rb_bigmath_to_rad(VALUE x, VALUE prec, VALUE *t);

VALUE rb_bigmath_atan(VALUE x, VALUE prec);
VALUE rb_bigmath_atan_adopt(VALUE x, VALUE prec, bigmath_func1 atan_cb);

VALUE rb_bigmath_quadrant(VALUE x, VALUE y, VALUE prec);

VALUE rb_bigmath_hypot(VALUE a, VALUE b, VALUE prec);

VALUE rb_bigmath_sqrt(VALUE x, VALUE prec);
VALUE rb_bigmath_csqrt(VALUE z, VALUE prec);

VALUE rb_bigmath_l2norm(VALUE vec, VALUE prec);

VALUE rb_bigmath_cabs(VALUE z, VALUE prec);
VALUE rb_bigmath_carg(VALUE z, VALUE prec);

#endif /* INTERNAL_API_BIGMATH */
