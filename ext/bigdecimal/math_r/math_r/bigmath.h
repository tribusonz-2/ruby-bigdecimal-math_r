#ifndef INTERNAL_SOLVER_BIGMATH
#define INTERNAL_SOLVER_BIGMATH

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

/**
 * Rounds the argument +x+ to an arbitrary precision +prec+. <br>
 * It targets real numbers, but also supports Complex class. <br>
 * 
 */
VALUE rb_num_round(VALUE x, VALUE prec);

#define ARG_REAL        false
#define ARG_COMPLEX     true
#define ARG_RAWVALUE    false
#define ARG_RECIPROCAL  true

VALUE rb_num_canonicalize(VALUE x, VALUE prec, 
	bool complex_form, bool inversion);


#endif /* INTERNAL_SOLVER_BIGMATH */
