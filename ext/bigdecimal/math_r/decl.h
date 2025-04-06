#ifndef BIGMATH_MATHFUNC_H
#define BIGMATH_MATHFUNC_H

VALUE atan_branch(VALUE, VALUE);
VALUE atan_ser_euler(VALUE, VALUE);
VALUE cabs_formula(VALUE, VALUE);
VALUE carg_formula(VALUE, VALUE);
VALUE ccbrt_formula(VALUE, VALUE);
VALUE cpow_formula(VALUE, VALUE, VALUE);
VALUE csqrt_formula(VALUE, VALUE);
VALUE cuberoot_newton(VALUE, VALUE);
VALUE ipow_edf(VALUE, VALUE, VALUE);
VALUE l2norm_formula(VALUE, VALUE);
VALUE quadrant_formula(VALUE, VALUE, VALUE);
VALUE sqrt_builtin(VALUE, VALUE);
VALUE sqrt_newton(VALUE, VALUE);

#endif /* BIGMATH_MATHFUNC_H */