/*******************************************************************************
	solver.c -- BigMathR::Solver

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"

static ID mf_log;
static ID mf_log2;
static ID mf_log10;
static ID mf_log1p;

bigmath_func1 cb_log;
bigmath_func1 cb_clog;
bigmath_func1 cb_log2;
bigmath_func1 cb_clog2;
bigmath_func1 cb_log10;
bigmath_func1 cb_clog10;


static void
rb_id_includes(int n, const ID *funcs, ID func)
{
	bool func_match = false;
	for (int i = 0; i < n; i++)
	{
		if (funcs[i] == func)
		{
			func_match = true;
			break;
		}
	}
	if (!func_match)
		rb_raise(rb_eArgError,
			"no includes function: %"PRIsVALUE"", ID2SYM(func));
}

#define CHECK_NUMARG(x) \
  if (!rb_num_numeric_p(x)) {\
    VALUE self; \
    switch(TYPE(x)) { \
    case T_NIL: case T_TRUE: case T_FALSE: \
      self = rb_inspect(x); \
      break; \
    default: \
      self = CLASS_OF(x); \
      break; \
    } \
    rb_raise(rb_eTypeError, \
      "can't convert %"PRIsVALUE" into Numeric", self); \
  }


static VALUE
solver_logarithm(ID func, VALUE z, VALUE prec)
{
	const ID funcs[4] = { mf_log, mf_log2, mf_log10, mf_log1p };
	VALUE w = Qundef;
	rb_id_includes(4, funcs, func);
	CHECK_NUMARG(z);
	rb_check_precise(prec);
	if (!rb_num_finite_p(z))
	{
		if (rb_num_nan_p(z))
			w = rb_num_real_p(z) ? 
				BIG_NAN : rb_Complex(BIG_NAN, BIG_NAN);
		else
		{
			if (func == mf_log || func == mf_log1p)
				w = clog_branch(z, prec, cb_clog);
			else if (func == mf_log2)
				w = clog_branch(z, prec, cb_clog2);
			else if (func == mf_log10)
				w = clog_branch(z, prec, cb_clog10);
			if (rb_num_real_p(z) && rb_num_positive_p(z))
				w = rb_num_real(w);
		}
	}
	if (w == Qundef)
	{
		if (rb_num_real_p(z) && !rb_num_negative_p(z))
		{
			if (func == mf_log)
				w = log_branch(z, prec, cb_log);
			else if (func == mf_log2)
				w = log_branch(z, prec, cb_log2);
			else if (func == mf_log10)
				w = log_branch(z, prec, cb_log10);
			else if (func == mf_log1p)
			{
				z = rb_funcall1(z, '+', BIG_ONE);
				w = log_branch(z, prec, cb_log);
			}
		}
		else
		{
			if (func == mf_log)
				w = clog_branch(z, prec, cb_clog);
			else if (func == mf_log2)
				w = clog_branch(z, prec, cb_clog2);
			else if (func == mf_log10)
				w = clog_branch(z, prec, cb_clog10);
			else if (func == mf_log1p)
			{
				z = rb_funcall1(z, '+', BIG_ONE);
				w = clog_branch(z, prec, cb_clog);
			}
		}
	}
	return w;
}

/**
 * This is a public API for logarithmic solver.
 * 
 * @param func [Symbol] The name of the target function. [:log, :log1p, :log2, :log10]
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Target function name no match found.
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 */
static VALUE
__impl_solver_logarithm(VALUE unused_obj, VALUE func, VALUE z, VALUE prec)
{
	return solver_logarithm(SYM2ID(func), z, prec);
}

/**
 *  Computes Natural logarithm of +z+.
 *  
 *  @overload log(z, prec)
 *  @overload log(z, b, prec)
 *  @param z [Numeric] Numerical argument
 *  @param b [Numeric] The base. Specified a real number
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +z+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
__impl_bigmath_log(int argc, VALUE *argv, VALUE unused_obj)
{
	const ID div = rb_intern("div");
	VALUE z = Qundef, b = Qundef, prec = Qundef;
	rb_check_arity(argc, 2, 3);
	switch (argc) {
	case 2:
		rb_scan_args(argc, argv, "20", &z, &prec);
		z = solver_logarithm(mf_log, z, prec);
		break;
	case 3:
		rb_scan_args(argc, argv, "30", &z, &b, &prec);
		rb_check_precise(prec);
		CHECK_NUMARG(z);
		b = rb_num_canonicalize(b, prec, ARG_REAL, ARG_RAWVALUE);
		if (rb_num_nan_p(b))
			z = rb_num_real_p(z) && !rb_num_negative_p(z) ?
				BIG_NAN : rb_Complex(BIG_NAN, BIG_NAN);
		else if (rb_num_infinite_p(b))
			z = rb_num_real_p(z) && !rb_num_negative_p(z) ? 
				BIG_ZERO : rb_Complex(BIG_ZERO, BIG_ZERO);
		else if (rb_num_zero_p(b))
			z = rb_num_zero_p(z) ?
				rb_num_real_p(z) ?
					BIG_NAN : 
					rb_Complex(BIG_NAN, BIG_NAN) :
				rb_num_real_p(z) && !rb_num_negative_p(z) ? 
					BIG_ZERO : 
					rb_Complex(BIG_ZERO, BIG_ZERO);
		else if (rb_num_equal_p(b, BIG_ONE))
			z = rb_Complex(BIG_INF, BIG_INF);
		else
		{
			z = solver_logarithm(mf_log, z, prec);
			b = solver_logarithm(mf_log, b, prec);
			if (rb_num_real_p(b))
				z = rb_funcall(z, div, 2, b, prec);
			else
			{
				z = rb_funcall1(z, '/', b);
				z = rb_num_round(z, prec);
			}
		}
		break;
	}
	return z;
}

/**
 *  Computes natural logarithm of 1 plus +z+.
 *  
 *  @param z [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +z+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
__impl_bigmath_log1p(VALUE unused_obj, VALUE z, VALUE prec)
{
	return solver_logarithm(mf_log1p, z, prec);
}

/**
 *  Computes binary logarithm of +z+.
 *  
 *  @param z [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +z+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
__impl_bigmath_log2(VALUE unused_obj, VALUE z, VALUE prec)
{
	return solver_logarithm(mf_log2, z, prec);
}

/**
 *  Computes common logarithm of +z+.
 *  
 *  @param z [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +z+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
__impl_bigmath_log10(VALUE unused_obj, VALUE z, VALUE prec)
{
	return solver_logarithm(mf_log10, z, prec);
}


/**
 *  Computes hyperbolic sine of +x+.
 *  
 *  @param x [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */

/**
 *  Computes hyperbolic cosine of +x+.
 *  
 *  @param x [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */

/**
 *  Computes hyperbolic tangent of +x+.
 *  
 *  @param x [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */
 
/**
 *  Computes hyperbolic cosecant of +x+.
 *  
 *  @param x [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */

/**
 *  Computes hyperbolic secant of +x+.
 *  
 *  @param x [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */

/**
 *  Computes hyperbolic cotangent of +x+.
 *  @param x [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */



/**
 *  Document-module: BigMathR::Solver
 *  
 *  A module that provides a solver for mathematical functions.
 *  It is used internally.
 */
void
InitVM_Solver(void)
{
	mf_log = rb_intern_const("log");
	mf_log2 = rb_intern_const("log2");
	mf_log10 = rb_intern_const("log10");
	mf_log1p = rb_intern_const("log1p");

	cb_log = log_edf;
	cb_log2 = log2_edf;
	cb_log10 = log10_edf;
	cb_clog = clog_formula;
	cb_clog2 = clog2_formula;
	cb_clog10 = clog10_formula;

	rb_define_singleton_method(rb_mSolver, "logarithm", __impl_solver_logarithm, 3);

	rb_define_singleton_method(rb_mBigMathR, "log", __impl_bigmath_log, -1);
	rb_define_singleton_method(rb_mBigMathR, "log1p", __impl_bigmath_log1p, 2);
	rb_define_singleton_method(rb_mBigMathR, "log2", __impl_bigmath_log2, 2);
	rb_define_singleton_method(rb_mBigMathR, "log10", __impl_bigmath_log10, 2);

}
