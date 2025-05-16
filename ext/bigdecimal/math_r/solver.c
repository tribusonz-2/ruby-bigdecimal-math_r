/*******************************************************************************
	solver.c -- BigMathR::Solver

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"

bigmath_func1 cb_exp;
bigmath_func1 cb_cexp;
bigmath_func1 cb_exp2;
bigmath_func1 cb_cexp2;
bigmath_func1 cb_log;
bigmath_func1 cb_clog;
bigmath_func1 cb_log2;
bigmath_func1 cb_clog2;
bigmath_func1 cb_log10;
bigmath_func1 cb_clog10;
bigmath_func1 cb_log1p;
bigmath_func1 cb_clog1p;

bigmath_func1 cb_sin;
bigmath_func1 cb_csin;
bigmath_func1 cb_cos;
bigmath_func1 cb_ccos;
bigmath_func1 cb_tan;
bigmath_func1 cb_ctan;
bigmath_func1 cb_csc;
bigmath_func1 cb_ccsc;
bigmath_func1 cb_sec;
bigmath_func1 cb_csec;
bigmath_func1 cb_cot;
bigmath_func1 cb_ccot;

bigmath_func1 cb_asin;
bigmath_func1 cb_casin;
bigmath_func1 cb_acos;
bigmath_func1 cb_cacos;
bigmath_func1 cb_atan;
bigmath_func1 cb_catan;
bigmath_func1 cb_acsc;
bigmath_func1 cb_cacsc;
bigmath_func1 cb_asec;
bigmath_func1 cb_casec;
bigmath_func1 cb_acot;
bigmath_func1 cb_cacot;

bigmath_func1 cb_sinh;
bigmath_func1 cb_csinh;
bigmath_func1 cb_cosh;
bigmath_func1 cb_ccosh;
bigmath_func1 cb_tanh;
bigmath_func1 cb_ctanh;
bigmath_func1 cb_csch;
bigmath_func1 cb_ccsch;
bigmath_func1 cb_sech;
bigmath_func1 cb_csech;
bigmath_func1 cb_coth;
bigmath_func1 cb_ccoth;

bigmath_func1 cb_asinh;
bigmath_func1 cb_casinh;
bigmath_func1 cb_acosh;
bigmath_func1 cb_cacosh;
bigmath_func1 cb_atanh;
bigmath_func1 cb_catanh;
bigmath_func1 cb_acsch;
bigmath_func1 cb_cacsch;
bigmath_func1 cb_asech;
bigmath_func1 cb_casech;
bigmath_func1 cb_acoth;
bigmath_func1 cb_cacoth;



static bool
domain_p(VALUE range, VALUE x)
{
	const ID cover_p = rb_intern("cover?");
	VALUE ans = rb_funcall(range, cover_p, 1, x);
	return ans == Qtrue ? true : false;
}

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
solver_exp(ID func, VALUE z, VALUE prec)
{
	const ID funcs[4] = { mf_exp, mf_exp2 };
	VALUE w = Qundef;
	rb_id_includes(2, funcs, func);
	CHECK_NUMARG(z);
	rb_check_precise(prec);
	if (!rb_num_finite_p(z))
	{
		if (func == mf_exp)
			w = cexp_branch(z, prec, cb_cexp);
		else if (func == mf_exp2)
			w = cexp2_branch(z, prec, cb_cexp2);
		if (rb_num_real_p(z) && rb_num_positive_p(z))
			w = rb_num_real(w);
	}
	if (w == Qundef)
	{
		VALUE r = Qundef, theta = Qundef;
//		if (rb_num_real_p(z))
		{
			if (func == mf_exp)
				r = exp_branch(rb_num_real(z), prec, cb_exp);
			else if (func == mf_exp2)
				r = exp2_branch(rb_num_real(z), prec, cb_exp2);
		}
//		else if (rb_num_zero_p(rb_num_real(z)))
		{
			VALUE t, v_sin, v_cos;
			theta = rb_num_imag(z);
			if (func == mf_exp2)
			{
				theta = rb_funcall1(theta, '*', rb_bigmath_const_log2(prec));
			}
			theta = rb_bigmath_to_rad(theta, prec, &t);
			if (-1 == rb_bigmath_degree_sparg(t, prec, &v_sin, &v_cos))
				rb_bigmath_sincos(theta, prec, &v_sin, &v_cos);
			theta = rb_Complex(v_cos, v_sin);
		}
		w = rb_funcall1(r, '*', theta); w = rb_num_round(w, prec);
	}
	return w;

}

/**
 * This is a public API for exponential solver.
 * 
 * @param func [Symbol] The name of the target function. [:exp, :exp2]
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Target function name no match found.
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 */
static VALUE
__impl_solver_exp(VALUE unused_obj, VALUE func, VALUE z, VALUE prec)
{
	return solver_exp(SYM2ID(func), z, prec);
}

/**
 *  Computes exponential function of +z+.
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
__impl_bigmath_exp(VALUE unused_obj, VALUE z, VALUE prec)
{
	return solver_exp(mf_exp, z, prec);
}

/**
 *  Computes base-2 (binary) exponent of +z+.
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
__impl_bigmath_exp2(VALUE unused_obj, VALUE z, VALUE prec)
{
	return solver_exp(mf_exp2, z, prec);
}


static VALUE
solver_log(ID func, VALUE z, VALUE prec)
{
	const ID funcs[4] = { mf_log, mf_log2, mf_log10, mf_log1p };
	VALUE w = Qundef;
	rb_id_includes(4, funcs, func);
	CHECK_NUMARG(z);
	rb_check_precise(prec);
	if (!rb_num_finite_p(z))
	{
		if (func == mf_log)
			w = clog_branch(z, prec, cb_clog);
		else if (func == mf_log1p)
			w = clog1p_branch(z, prec, cb_clog1p);
		else if (func == mf_log2)
			w = clog_branch(z, prec, cb_clog2);
		else if (func == mf_log10)
			w = clog_branch(z, prec, cb_clog10);
		if (rb_num_real_p(z) && rb_num_positive_p(z))
			w = rb_num_real(w);
	}
	if (w == Qundef)
	{
		if (rb_num_real_p(z) && !rb_num_negative_p(z))
		{
			if (func == mf_log)
				w = log_branch(z, prec, cb_log);
			else if (func == mf_log1p)
				w = log1p_branch(z, prec, cb_log1p);
			else if (func == mf_log2)
				w = log2_branch(z, prec, cb_log2);
			else if (func == mf_log10)
				w = log10_branch(z, prec, cb_log10);
		}
		else
		{
			if (func == mf_log)
				w = clog_branch(z, prec, cb_clog);
			else if (func == mf_log1p)
				w = clog1p_branch(z, prec, cb_clog1p);
			else if (func == mf_log2)
				w = clog_branch(z, prec, cb_clog2);
			else if (func == mf_log10)
				w = clog_branch(z, prec, cb_clog10);
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
__impl_solver_log(VALUE unused_obj, VALUE func, VALUE z, VALUE prec)
{
	return solver_log(SYM2ID(func), z, prec);
}

/**
 * @overload log(z, prec)
 *  Computes the Natural logarithm of +z+.

 *  @param z [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +z+ is not a numeric class.
 *  @since 0.1.0
 * @overload log(z, b, prec)
 *  Computes the Natural logarithm of +z+ on base +b+.
 *  
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
	VALUE z = Qundef, b = Qundef, prec = Qundef;
	rb_check_arity(argc, 2, 3);
	switch (argc) {
	case 2:
		rb_scan_args(argc, argv, "20", &z, &prec);
		z = solver_log(mf_log, z, prec);
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
			z = solver_log(mf_log, z, prec);
			b = solver_log(mf_log, b, prec);
			z = rb_funcall1(z, '/', b);
			z = rb_num_round(z, prec);
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
	return solver_log(mf_log1p, z, prec);
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
	return solver_log(mf_log2, z, prec);
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
	return solver_log(mf_log10, z, prec);
}

static VALUE
solver_trig(ID func, VALUE z, VALUE prec)
{
	const ID funcs[6] = { mf_sin, mf_cos, mf_tan, mf_csc, mf_sec, mf_cot };
	VALUE w = Qundef;
	rb_id_includes(6, funcs, func);
	CHECK_NUMARG(z);
	rb_check_precise(prec);
	
	if (!rb_num_finite_p(z))
	{
		if (func == mf_sin)
			w = csin_branch(z, prec, cb_csin);
		else if (func == mf_cos)
			w = ccos_branch(z, prec, cb_ccos);
		else if (func == mf_tan)
			w = ctan_branch(z, prec, cb_ctan);
		else if (func == mf_csc)
			w = ccsc_branch(z, prec, cb_ccsc);
		else if (func == mf_sec)
			w = csec_branch(z, prec, cb_csec);
		else if (func == mf_cot)
			w = ccot_branch(z, prec, cb_ccot);
	}
	if (w == Qundef)
	{
		if (rb_num_real_p(z) || rb_num_zero_p(rb_num_imag(z)))
		{
			if (func == mf_sin)
				w = sin_branch(z, prec, cb_sin);
			else if (func == mf_cos)
				w = cos_branch(z, prec, cb_cos);
			else if (func == mf_tan)
				w = tan_branch(z, prec, cb_tan);
			else if (func == mf_csc)
				w = csc_branch(z, prec, cb_csc);
			else if (func == mf_sec)
				w = sec_branch(z, prec, cb_sec);
			else if (func == mf_cot)
				w = cot_branch(z, prec, cb_cot);
		}
		else if (rb_num_real_p(z) || rb_num_zero_p(rb_num_real(z)))
		{
			if (func == mf_sin)
			{
				w = sinh_branch(rb_num_imag(z), prec, cb_sinh);
				w = rb_ImaginaryZ(w, SIGN_PLUS);
			}
			else if (func == mf_cos)
			{
				w = cosh_branch(rb_num_imag(z), prec, cb_cosh);
				w = rb_Complex(w, BIG_ZERO);
			}
			else if (func == mf_tan)
			{
				w = tanh_branch(rb_num_imag(z), prec, cb_tanh);
				w = rb_ImaginaryZ(w, SIGN_PLUS);
			}
			else if (func == mf_csc)
			{
				w = csch_branch(rb_num_imag(z), prec, cb_csch);
				w = rb_ImaginaryZ(w, SIGN_MINUS);
			}
			else if (func == mf_sec)
			{
				w = sech_branch(z, prec, cb_sech);
				w = rb_Complex(w, BIG_ZERO);
			}
			else if (func == mf_cot)
			{
				w = coth_branch(z, prec, cb_coth);
				w = rb_ImaginaryZ(w, SIGN_MINUS);
			}
			if (rb_num_real(z))
				w = rb_Complex(w, BIG_ZERO);
		}
		else
		{
			if (func == mf_sin)
				w = csin_branch(z, prec, cb_csin);
			else if (func == mf_cos)
				w = ccos_branch(z, prec, cb_ccos);
			else if (func == mf_tan)
				w = ctan_branch(z, prec, cb_ctan);
			else if (func == mf_csc)
				w = ccsc_branch(z, prec, cb_ccsc);
			else if (func == mf_sec)
				w = csec_branch(z, prec, cb_csec);
			else if (func == mf_cot)
				w = ccot_branch(z, prec, cb_ccot);
		}
	}
	if (rb_num_real(z) && rb_num_zero_p(rb_num_imag(z)))
		w = rb_num_real(w);
	return w;
}

/**
 * This is a public API for trigonometric solver.
 * 
 * @param func [Symbol] The name of the target function. [:sin, :cos, :tan, :csc, :sec, :cot]
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Target function name no match found.
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 */
static VALUE
__impl_solver_trig(VALUE unused_obj, VALUE func, VALUE z, VALUE prec)
{
	return solver_trig(SYM2ID(func), z, prec);
}

/**
 *  Computes sine of +z+.
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
__impl_bigmath_sin(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_trig(mf_sin, x, prec);
}

/**
 *  Computes cosine of +z+.
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
__impl_bigmath_cos(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_trig(mf_cos, x, prec);
}

/**
 *  Computes tangent of +z+.
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
__impl_bigmath_tan(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_trig(mf_tan, x, prec);
}

/**
 *  Computes cosecant of +z+.
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
__impl_bigmath_csc(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_trig(mf_csc, x, prec);
}

/**
 *  Computes secant of +z+.
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
__impl_bigmath_sec(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_trig(mf_sec, x, prec);
}

/**
 *  Computes cotangent of +z+.
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
__impl_bigmath_cot(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_trig(mf_cot, x, prec);
}

static VALUE
solver_hyperb(ID func, VALUE z, VALUE prec)
{
	const ID funcs[6] = { mf_sinh, mf_cosh, mf_tanh, mf_csch, mf_sech, mf_coth };
	VALUE w = Qundef;
	rb_id_includes(6, funcs, func);
	CHECK_NUMARG(z);
	rb_check_precise(prec);
	
	if (!rb_num_finite_p(z))
	{
		if (func == mf_sinh)
			w = csinh_branch(z, prec, cb_csinh);
		else if (func == mf_cosh)
			w = ccosh_branch(z, prec, cb_ccosh);
		else if (func == mf_tanh)
			w = ctanh_branch(z, prec, cb_ctanh);
		else if (func == mf_csch)
			w = ccsch_branch(z, prec, cb_ccsch);
		else if (func == mf_sech)
			w = csech_branch(z, prec, cb_csech);
		else if (func == mf_coth)
			w = ccoth_branch(z, prec, cb_ccoth);
	}
	if (w == Qundef)
	{
		if (rb_num_real_p(z) || rb_num_zero_p(rb_num_imag(z)))
		{
			if (func == mf_sinh)
				w = sinh_branch(z, prec, cb_sinh);
			else if (func == mf_cosh)
				w = cosh_branch(z, prec, cb_cosh);
			else if (func == mf_tanh)
				w = tanh_branch(z, prec, cb_tanh);
			else if (func == mf_csch)
				w = csch_branch(z, prec, cb_csch);
			else if (func == mf_sech)
				w = sech_branch(z, prec, cb_sech);
			else if (func == mf_coth)
				w = coth_branch(z, prec, cb_coth);
		}
		else if (rb_num_real_p(z) || rb_num_zero_p(rb_num_real(z)))
		{
			if (func == mf_sinh)
			{
				w = sin_branch(rb_num_imag(z), prec, cb_sin);
				w = rb_ImaginaryZ(w, SIGN_PLUS);
			}
			else if (func == mf_cosh)
			{
				w = cos_branch(rb_num_imag(z), prec, cb_cos);
				w = rb_Complex(w, BIG_ZERO);
			}
			else if (func == mf_tanh)
			{
				w = tan_branch(rb_num_imag(z), prec, cb_tan);
				w = rb_ImaginaryZ(w, SIGN_PLUS);
			}
			else if (func == mf_csch)
			{
				w = csc_branch(rb_num_imag(z), prec, cb_csc);
				w = rb_ImaginaryZ(w, SIGN_MINUS);
			}
			else if (func == mf_sech)
			{
				w = sec_branch(z, prec, cb_sec);
				w = rb_Complex(w, BIG_ZERO);
			}
			else if (func == mf_coth)
			{
				w = cot_branch(z, prec, cb_cot);
				w = rb_ImaginaryZ(w, SIGN_MINUS);
			}
			if (rb_num_real(z))
				w = rb_Complex(w, BIG_ZERO);
		}
		else
		{
			if (func == mf_sinh)
				w = csinh_branch(z, prec, cb_csinh);
			else if (func == mf_cosh)
				w = ccosh_branch(z, prec, cb_ccosh);
			else if (func == mf_tanh)
				w = ctanh_branch(z, prec, cb_ctanh);
			else if (func == mf_csch)
				w = ccsch_branch(z, prec, cb_ccsch);
			else if (func == mf_sech)
				w = csech_branch(z, prec, cb_csech);
			else if (func == mf_coth)
				w = ccoth_branch(z, prec, cb_ccoth);
		}
	}
	if (rb_num_real(z) && rb_num_zero_p(rb_num_imag(z)))
		w = rb_num_real(w);
	return w;
}

/**
 * This is a public API for hyperbolic solver.
 * 
 * @param func [Symbol] The name of the target function. [:sinh, :cosh, :tanh, :csch, :sech, :coth]
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Target function name no match found.
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 */
static VALUE
__impl_solver_hyperb(VALUE unused_obj, VALUE func, VALUE z, VALUE prec)
{
	return solver_hyperb(SYM2ID(func), z, prec);
}

/**
 *  Computes hyperbolic sine of +z+.
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
__impl_bigmath_sinh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_hyperb(mf_sinh, x, prec);
}

/**
 *  Computes hyperbolic cosine of +z+.
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
__impl_bigmath_cosh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_hyperb(mf_cosh, x, prec);
}

/**
 *  Computes hyperbolic tangent of +z+.
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
__impl_bigmath_tanh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_hyperb(mf_tanh, x, prec);
}

/**
 *  Computes hyperbolic cosecant of +z+.
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
__impl_bigmath_csch(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_hyperb(mf_csch, x, prec);
}

/**
 *  Computes hyperbolic secant of +z+.
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
__impl_bigmath_sech(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_hyperb(mf_sech, x, prec);
}

/**
 *  Computes hyperbolic cotangent of +z+.
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
__impl_bigmath_coth(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_hyperb(mf_coth, x, prec);
}


static VALUE
solver_triginv(ID func, VALUE z, VALUE prec)
{
	const ID funcs[6] = { mf_asin, mf_acos, mf_atan, mf_acsc, mf_asec, mf_acot };
	VALUE w = Qundef;
	rb_id_includes(6, funcs, func);
	CHECK_NUMARG(z);
	rb_check_precise(prec);
	
	if (!rb_num_finite_p(z))
	{
		if (func == mf_asin)
			w = casin_branch(z, prec, cb_casin);
		else if (func == mf_acos)
			w = cacos_branch(z, prec, cb_cacos);
		else if (func == mf_atan)
			w = catan_branch(z, prec, cb_catan);
		else if (func == mf_acsc)
			w = cacsc_branch(z, prec, cb_cacsc);
		else if (func == mf_asec)
			w = casec_branch(z, prec, cb_casec);
		else if (func == mf_acot)
			w = cacot_branch(z, prec, cb_cacot);
	}
	if (w == Qundef)
	{
		if (rb_num_real_p(z) || rb_num_zero_p(rb_num_imag(z)))
		{
			if (func == mf_asin)
			{
				VALUE domain = rb_range_new(INT2FIX(-1), INT2FIX(1), 0);
				if (domain_p(domain, z))
					w = asin_branch(z, prec, cb_asin);
				else
					w = asin_edom(z, prec);
			}
			else if (func == mf_acos)
			{
				VALUE domain = rb_range_new(INT2FIX(-1), INT2FIX(1), 0);
				if (domain_p(domain, z))
					w = acos_branch(z, prec, cb_acos);
				else
					w = acos_edom(z, prec);
			}
			else if (func == mf_atan)
					w = atan_branch(z, prec, cb_atan);
			else if (func == mf_acsc)
			{
				VALUE m_domain = rb_range_new(BIG_MINUS_INF, BIG_MINUS_ONE, 0);
				VALUE p_domain = rb_range_new(BIG_ONE, BIG_INF, 0);
				if (domain_p(m_domain, z) || domain_p(p_domain, z))
					w = acsc_branch(z, prec, cb_acsc);
				else
					w = acsc_edom(z, prec);
			}
			else if (func == mf_asec)
			{
				VALUE m_domain = rb_range_new(BIG_MINUS_INF, BIG_MINUS_ONE, 0);
				VALUE p_domain = rb_range_new(BIG_ONE, BIG_INF, 0);
				if (domain_p(m_domain, z) || domain_p(p_domain, z))
					w = asec_branch(z, prec, cb_asec);
				else
					w = asec_edom(z, prec);
			}
			else if (func == mf_acot)
				w = acot_branch(z, prec, cb_acot);
		}
		else
		{
			if (func == mf_asin)
				w = casin_branch(z, prec, cb_casin);
			else if (func == mf_acos)
				w = cacos_branch(z, prec, cb_cacos);
			else if (func == mf_atan)
				w = catan_branch(z, prec, cb_catan);
			else if (func == mf_acsc)
				w = cacsc_branch(z, prec, cb_cacsc);
			else if (func == mf_asec)
				w = casec_branch(z, prec, cb_casec);
			else if (func == mf_acot)
				w = cacot_branch(z, prec, cb_cacot);
		}
	}
	if (rb_num_real(z) && rb_num_zero_p(rb_num_imag(w)))
		w = rb_num_real(w);
	return w;
}

/**
 * This is a public API for inverse trigonometric solver.
 * 
 * @param func [Symbol] The name of the target function. [:asin, :acos, :atan, :acsc, :asec, :acot]
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Target function name no match found.
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 */
static VALUE
__impl_solver_triginv(VALUE unused_obj, VALUE func, VALUE z, VALUE prec)
{
	return solver_triginv(SYM2ID(func), z, prec);
}

/**
 *  Computes inverse sine of +z+.
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
__impl_bigmath_asin(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_triginv(mf_asin, x, prec);
}

/**
 *  Computes inverse cosine of +z+.
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
__impl_bigmath_acos(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_triginv(mf_acos, x, prec);
}

/**
 * @overload atan(z, prec)
 *  Computes the inverse tangent +z+.
 *  @param z [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +z+ is not a numeric class.
 *  @since 0.1.0
 *  @example
 *   BigMathR.atan(1, 20)
 *   #=> 0.78539816339744830963e0
 *   BigMathR.atan(1+1i, 20)
 *   #=> (0.10172219678978513677e1+0.40235947810852509365e0i)
 * @overload atan(z, w, prec)
 *  Consider where the value is in quadrant XY and computes the inverse tangent of +w/z+.
 *  <br>
 *  This function is equivalent to +atan2(y, x)+, but the arguments are in a different order.
 *  @param z [Numeric] Numerical argument, as Quadrant XY of X
 *  @param w [Numeric] Numerical argument, as Quadrant XY of Y
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +z+ or +w+ is not a numeric class.
 *  @since 0.1.0
 *  @example
 *   BigMathR.atan(1, 2, 20)
 *   #=> 0.11071487177940905031e1
 *   BigMathR.atan(3i, 2i, 20)
 *   #=> (0.58800260354756755124e0+0i)
 */
static VALUE
__impl_bigmath_atan(int argc, VALUE *argv, VALUE unused_obj)
{
	VALUE z = Qundef, w = Qundef, prec = Qundef;
	
	rb_check_arity(argc, 2, 3);
	switch (argc) {
	case 2:
		rb_scan_args(argc, argv, "20", &z, &prec);
		CHECK_NUMARG(z);
		rb_check_precise(prec);
		z = solver_triginv(mf_atan, z, prec);
		break;
	case 3:
		rb_scan_args(argc, argv, "30", &z, &w, &prec);
		CHECK_NUMARG(z);
		CHECK_NUMARG(w);
		rb_check_precise(prec);
		z = rb_bigmath_quadrant(z, w, prec);
		break;
	}
	return z;
}

/**
 *  Computes inverse cosecant of +z+.
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
__impl_bigmath_acsc(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_triginv(mf_acsc, x, prec);
}

/**
 *  Computes inverse secant of +z+.
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
__impl_bigmath_asec(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_triginv(mf_asec, x, prec);
}

/**
 *  Computes inverse cotangent of +z+.
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
__impl_bigmath_acot(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_triginv(mf_acot, x, prec);
}

static VALUE
solver_hyperbinv(ID func, VALUE z, VALUE prec)
{
	const ID funcs[6] = { mf_asinh, mf_acosh, mf_atanh, 
	                      mf_acsch, mf_asech, mf_acoth };
	VALUE w = Qundef;
	rb_id_includes(6, funcs, func);
	CHECK_NUMARG(z);
	rb_check_precise(prec);
	
	if (!rb_num_finite_p(z))
	{
		if (func == mf_asinh)
			w = casinh_branch(z, prec, cb_casinh);
		else if (func == mf_acosh)
			w = cacosh_branch(z, prec, cb_cacosh);
		else if (func == mf_atanh)
			w = catanh_branch(z, prec, cb_catanh);
		else if (func == mf_acsch)
			w = cacsch_branch(z, prec, cb_cacsch);
		else if (func == mf_asech)
			w = casech_branch(z, prec, cb_casech);
		else if (func == mf_acoth)
			w = cacoth_branch(z, prec, cb_cacoth);
	}
	if (w == Qundef)
	{
		if (rb_num_real_p(z) || rb_num_zero_p(rb_num_imag(z)))
		{
			if (func == mf_asinh)
			{
				w = asinh_branch(z, prec, cb_asinh);
			}
			else if (func == mf_acosh)
			{
				VALUE m_domain = rb_range_new(BIG_MINUS_INF, BIG_MINUS_ONE, 0);
				VALUE p_domain = rb_range_new(BIG_ONE, BIG_INF, 0);
				if (domain_p(p_domain, z))
					w = acosh_branch(z, prec, cb_acosh);
				else if (domain_p(m_domain, z))
				{
					z = rb_num_abs(z);
					w = acosh_branch(z, prec, cb_acosh);
					w = rb_Complex(w, rb_bigmath_const_pi(prec));
				}
				else
					w = acosh_edom(z, prec);
			}
			else if (func == mf_atanh)
			{
				VALUE domain = rb_range_new(INT2FIX(-1), INT2FIX(1), 0);
				if (domain_p(domain, z))
					w = atanh_branch(z, prec, cb_atanh);
				else
					w = atanh_edom(z, prec);
			}
			else if (func == mf_acsch)
			{
				w = acsch_branch(z, prec, cb_acsch);
			}
			else if (func == mf_asech)
			{
				VALUE m_domain = rb_range_new(BIG_MINUS_ONE, BIG_ZERO, 0);
				VALUE p_domain = rb_range_new(BIG_ZERO, BIG_ONE, 0);
				if (domain_p(p_domain, z))
					w = asech_branch(z, prec, cb_asech);
				else if (domain_p(m_domain, z))
				{
					w = asech_branch(z, prec, cb_asech);
					w = rb_Complex(w, rb_bigmath_const_pi(prec));
				}
				else
					w = asech_edom(z, prec);
			}
			else if (func == mf_acoth)
			{
				VALUE m_domain = rb_range_new(BIG_MINUS_INF, BIG_MINUS_ONE, 0);
				VALUE p_domain = rb_range_new(BIG_ONE, BIG_INF, 0);
				if (domain_p(m_domain, z) || domain_p(p_domain, z))
					w = acoth_branch(z, prec, cb_acoth);
				else
					w = acoth_edom(z, prec);
			}
		}
		else
		{
			if (func == mf_asinh)
				w = casinh_branch(z, prec, cb_casinh);
			else if (func == mf_acosh)
				w = cacosh_branch(z, prec, cb_cacosh);
			else if (func == mf_atanh)
				w = catanh_branch(z, prec, cb_catanh);
			else if (func == mf_acsch)
				w = cacsch_branch(z, prec, cb_cacsch);
			else if (func == mf_asech)
				w = casech_branch(z, prec, cb_casech);
			else if (func == mf_acoth)
				w = cacoth_branch(z, prec, cb_cacoth);
		}
	}
	if (rb_num_real(z) && rb_num_zero_p(rb_num_imag(w)))
		w = rb_num_real(w);
	return w;
}

/**
 * This is a public API for inverse hyperbolic solver.
 * 
 * @param func [Symbol] The name of the target function. [:asinh, :acosh, :atanh, :acsch, :asech, :acoth]
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Target function name no match found.
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 */
static VALUE
__impl_solver_hyperbinv(VALUE unused_obj, VALUE func, VALUE z, VALUE prec)
{
	return solver_hyperbinv(SYM2ID(func), z, prec);
}

/**
 *  Computes inverse hyperbolic sine of +z+.
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
__impl_bigmath_asinh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_hyperbinv(mf_asinh, x, prec);
}

/**
 *  Computes inverse hyperbolic cosine of +z+.
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
__impl_bigmath_acosh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_hyperbinv(mf_acosh, x, prec);
}

/**
 *  Computes inverse hyperbolic tangent of +z+.
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
__impl_bigmath_atanh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_hyperbinv(mf_atanh, x, prec);
}

/**
 *  Computes inverse hyperbolic cosecant of +z+.
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
__impl_bigmath_acsch(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_hyperbinv(mf_acsch, x, prec);
}

/**
 *  Computes inverse hyperbolic secant of +z+.
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
__impl_bigmath_asech(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_hyperbinv(mf_asech, x, prec);
}

/**
 *  Computes inverse hyperbolic cotangent of +z+.
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
__impl_bigmath_acoth(VALUE unused_obj, VALUE x, VALUE prec)
{
	return solver_hyperbinv(mf_acoth, x, prec);
}

static VALUE
__impl_bigmath_sqrt(VALUE unused_obj, VALUE x, VALUE prec)
{
	VALUE y = Qundef;
	if (rb_num_real_p(x))
	{
		x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
		if (rb_num_negative_p(x))
			y = sqrt_edom(x, prec);
		else
			y = sqrt_newton(x, prec);
	}
	else
	{
		x = rb_num_canonicalize(x, prec, ARG_COMPLEX, ARG_RAWVALUE);
		y = csqrt_formula(x, prec);
	}
	return y;
}

static VALUE
__impl_bigmath_cbrt(VALUE unused_obj, VALUE x, VALUE prec)
{
	VALUE y = Qundef;
	if (rb_num_real_p(x))
	{
		x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
		if (rb_num_negative_p(x))
		{
			x = rb_num_uminus(x);
			y = cuberoot_newton(x, prec);
			y = rb_num_uminus(y);
		}
		else
			y = cuberoot_newton(x, prec);
	}
	else
	{
		x = rb_num_canonicalize(x, prec, ARG_COMPLEX, ARG_RAWVALUE);
		y = csqrt_formula(x, prec);
	}
	return y;
}


/**
 *  Document-module: BigMathR::Solver
 *  
 *  A module that provides a solver for mathematical functions.
 *  It is used internally.
 */
void
InitVM_Solver(void)
{
	cb_exp = exp_edf;
	cb_cexp = cexp_eulerf;
	cb_exp2 = exp2_edf;
	cb_cexp2 = cexp2_eulerf;

	cb_log = log_edf;
	cb_log2 = log2_edf;
	cb_log10 = log10_edf;
	cb_log1p = log1p_ser_mercator;
	cb_clog = clog_formula;
	cb_clog2 = clog2_formula;
	cb_clog10 = clog10_formula;
	cb_clog1p = log1p_ser_mercator;

	cb_sin = sin_ser;
	cb_cos = cos_ser;
	cb_tan = tan_ser;
	cb_csc = csc_ser;
	cb_sec = sec_ser;
	cb_cot = cot_ser;

	cb_csin = csin_eulerf;
	cb_ccos = ccos_eulerf;
	cb_ctan = ctan_eulerf;
	cb_ccsc = ccsc_eulerf;
	cb_csec = csec_eulerf;
	cb_ccot = ccot_eulerf;

	cb_sinh = sinh_formula;
	cb_cosh = cosh_formula;
	cb_tanh = tanh_formula;
	cb_csch = csch_formula;
	cb_sech = sech_formula;
	cb_coth = coth_formula;

	cb_csinh = csinh_eulerf;
	cb_ccosh = ccosh_eulerf;
	cb_ctanh = ctanh_eulerf;
	cb_ccsch = ccsch_eulerf;
	cb_csech = csech_eulerf;
	cb_ccoth = ccoth_eulerf;

	cb_asin = asin_logrep;
	cb_acos = acos_logrep;
	cb_atan = atan_logrep;
	cb_acsc = acsc_logrep;
	cb_asec = asec_logrep;
	cb_acot = acot_logrep;

	cb_casin = casin_logrep;
	cb_cacos = cacos_logrep;
	cb_catan = catan_logrep;
	cb_cacsc = cacsc_logrep;
	cb_casec = casec_logrep;
	cb_cacot = cacot_logrep;

	cb_asinh = asinh_logrep;
	cb_acosh = acosh_logrep;
	cb_atanh = atanh_logrep;
	cb_acsch = acsch_logrep;
	cb_asech = asech_logrep;
	cb_acoth = acoth_logrep;

	cb_casinh = casinh_logrep;
	cb_cacosh = cacosh_logrep;
	cb_catanh = catanh_logrep;
	cb_cacsch = cacsch_logrep;
	cb_casech = casech_logrep;
	cb_cacoth = cacoth_logrep;

	rb_define_singleton_method(rb_mSolver, "exp", __impl_solver_exp, 3);

	rb_define_singleton_method(rb_mBigMathR, "exp", __impl_bigmath_exp, 2);
	rb_define_singleton_method(rb_mBigMathR, "exp2", __impl_bigmath_exp2, 2);

	rb_define_singleton_method(rb_mSolver, "log", __impl_solver_log, 3);

	rb_define_singleton_method(rb_mBigMathR, "log", __impl_bigmath_log, -1);
	rb_define_singleton_method(rb_mBigMathR, "log1p", __impl_bigmath_log1p, 2);
	rb_define_singleton_method(rb_mBigMathR, "log2", __impl_bigmath_log2, 2);
	rb_define_singleton_method(rb_mBigMathR, "log10", __impl_bigmath_log10, 2);

	rb_define_singleton_method(rb_mSolver, "trig", __impl_solver_trig, 3);

	rb_define_singleton_method(rb_mBigMathR, "sin", __impl_bigmath_sin, 2);
	rb_define_singleton_method(rb_mBigMathR, "cos", __impl_bigmath_cos, 2);
	rb_define_singleton_method(rb_mBigMathR, "tan", __impl_bigmath_tan, 2);
	rb_define_singleton_method(rb_mBigMathR, "csc", __impl_bigmath_csc, 2);
	rb_define_singleton_method(rb_mBigMathR, "sec", __impl_bigmath_sec, 2);
	rb_define_singleton_method(rb_mBigMathR, "cot", __impl_bigmath_cot, 2);

	rb_define_singleton_method(rb_mSolver, "hyperb", __impl_solver_hyperb, 3);

	rb_define_singleton_method(rb_mBigMathR, "sinh", __impl_bigmath_sinh, 2);
	rb_define_singleton_method(rb_mBigMathR, "cosh", __impl_bigmath_cosh, 2);
	rb_define_singleton_method(rb_mBigMathR, "tanh", __impl_bigmath_tanh, 2);
	rb_define_singleton_method(rb_mBigMathR, "csch", __impl_bigmath_csch, 2);
	rb_define_singleton_method(rb_mBigMathR, "sech", __impl_bigmath_sech, 2);
	rb_define_singleton_method(rb_mBigMathR, "coth", __impl_bigmath_coth, 2);

	rb_define_singleton_method(rb_mSolver, "triginv", __impl_solver_triginv, 3);

	rb_define_singleton_method(rb_mBigMathR, "asin", __impl_bigmath_asin, 2);
	rb_define_singleton_method(rb_mBigMathR, "acos", __impl_bigmath_acos, 2);
	rb_define_singleton_method(rb_mBigMathR, "atan", __impl_bigmath_atan, -1);
	rb_define_singleton_method(rb_mBigMathR, "acsc", __impl_bigmath_acsc, 2);
	rb_define_singleton_method(rb_mBigMathR, "asec", __impl_bigmath_asec, 2);
	rb_define_singleton_method(rb_mBigMathR, "acot", __impl_bigmath_acot, 2);

	rb_define_singleton_method(rb_mSolver, "hyperbinv", __impl_solver_hyperbinv, 3);

	rb_define_singleton_method(rb_mBigMathR, "asinh", __impl_bigmath_asinh, 2);
	rb_define_singleton_method(rb_mBigMathR, "acosh", __impl_bigmath_acosh, 2);
	rb_define_singleton_method(rb_mBigMathR, "atanh", __impl_bigmath_atanh, 2);
	rb_define_singleton_method(rb_mBigMathR, "acsch", __impl_bigmath_acsch, 2);
	rb_define_singleton_method(rb_mBigMathR, "asech", __impl_bigmath_asech, 2);
	rb_define_singleton_method(rb_mBigMathR, "acoth", __impl_bigmath_acoth, 2);

	rb_define_singleton_method(rb_mBigMathR, "sqrt", __impl_bigmath_sqrt, 2);
	rb_define_singleton_method(rb_mBigMathR, "cbrt", __impl_bigmath_cbrt, 2);
}
