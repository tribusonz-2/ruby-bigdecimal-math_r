#ifndef BIGMATH_MATHFUNC_H
#define BIGMATH_MATHFUNC_H

VALUE atan_branch(VALUE x, VALUE prec, bigmath_func1 cb);
VALUE atan_ser_euler(VALUE x, VALUE prec);
VALUE cabs_formula(VALUE x, VALUE prec);
VALUE carg_formula(VALUE x, VALUE prec);
VALUE ccbrt_formula(VALUE x, VALUE prec);
VALUE cpow_formula(VALUE x, VALUE y, VALUE prec);
VALUE csqrt_formula(VALUE x, VALUE prec);
VALUE cuberoot_newton(VALUE x, VALUE prec);
void escalb_edf(VALUE x, VALUE y, VALUE prec, VALUE *a, VALUE *b);
VALUE exp_edf(VALUE x, VALUE prec);
VALUE exp2_edf(VALUE x, VALUE prec);
VALUE expxt_edf(VALUE x, VALUE y, VALUE prec);
VALUE ipow_edf(VALUE x, VALUE y, VALUE prec);
VALUE l2norm_formula(VALUE x, VALUE prec);
VALUE log_branch(VALUE x, VALUE prec, bigmath_func1 cb);
VALUE log_builtin(VALUE x, VALUE prec);
VALUE log_edf(VALUE x, VALUE prec);
VALUE log_mercator(VALUE x, VALUE prec);
VALUE log_ser_mercator(VALUE x, VALUE prec);
VALUE log10_edf(VALUE x, VALUE prec);
VALUE log10_mercator(VALUE x, VALUE prec);
VALUE log2_edf(VALUE x, VALUE prec);
VALUE log2_mercator(VALUE x, VALUE prec);
VALUE logxt_edf(VALUE x, VALUE y, VALUE prec);
VALUE quadrant_formula(VALUE x, VALUE y, VALUE prec);
VALUE rcm10_edf(VALUE x, VALUE *reso);
VALUE rcm2_edf(VALUE x, VALUE *reso);
VALUE sqrt_branch(VALUE x, VALUE prec, bigmath_func1 cb);
VALUE sqrt_builtin(VALUE x, VALUE prec);
VALUE sqrt_newton(VALUE x, VALUE prec);

#endif /* BIGMATH_MATHFUNC_H */