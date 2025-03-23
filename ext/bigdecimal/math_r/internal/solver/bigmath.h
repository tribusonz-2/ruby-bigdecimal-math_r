#ifndef INTERNAL_SOLVER_BIGMATH
#define INTERNAL_SOLVER_BIGMATH

/* API for BigMath */
VALUE rb_bigmath_pi(VALUE prec); // constant.c
VALUE rb_bigmath_e(VALUE prec); // constant.c
VALUE rb_bigmath_const_log2(VALUE prec); // constant.c
VALUE rb_bigmath_const_log10(VALUE prec); // constant.c
VALUE rb_bigmath_const_sqrt2(VALUE prec); // constant.c
VALUE rb_bigmath_const_sqrt3(VALUE prec); // constant.c

VALUE rb_bigmath_exp(VALUE x, VALUE prec); // edf.c
VALUE rb_bigmath_cexp(VALUE z, VALUE prec); // trigexp.c

VALUE rb_bigmath_log(VALUE x, VALUE prec); // edf.c
VALUE rb_bigmath_clog(VALUE z, VALUE prec); // logsqrt.c

VALUE rb_sincos_to_radian(VALUE x, VALUE prec, VALUE pi, VALUE *t); // trig.c
int rb_degree_sparg(VALUE t, VALUE prec, VALUE *sin, VALUE *cos); // trig.c
void rb_bigmath_sincos(VALUE x, VALUE prec, VALUE *sin, VALUE *cos); // trig.c

VALUE rb_bigmath_atan(VALUE x, VALUE prec); // logsqrt.c
VALUE rb_bigmath_quadrant(VALUE x, VALUE y, VALUE prec); // nucomp.c
VALUE rb_bigmath_hypot(VALUE a, VALUE b, VALUE prec); // nucomp.c

VALUE rb_bigmath_sqrt(VALUE x, VALUE prec); // power_root.c
VALUE rb_bigmath_csqrt(VALUE z, VALUE prec); // power_root.c

VALUE rb_bigmath_l2norm(VALUE vec, VALUE prec); // nucomp.c

VALUE rb_bigmath_cabs(VALUE z, VALUE prec); // nucomp.c
VALUE rb_bigmath_carg(VALUE z, VALUE prec); // nucomp.c
VALUE rb_bigmath_polar_to(VALUE z, VALUE prec); // nucomp.c
VALUE rb_bigmath_polar_from(VALUE r, VALUE theta, VALUE prec); // nucomp.c

VALUE rb_bigmath_round_inline(VALUE x, VALUE prec); // bigdecimal.c

#define ARG_REAL        false
#define ARG_COMPLEX     true
#define ARG_RAWVALUE    false
#define ARG_RECIPROCAL  true

VALUE rb_bigmath_canonicalize(VALUE x, VALUE prec, 
	bool complex_form, bool inversion);


#endif /* INTERNAL_SOLVER_BIGMATH */
