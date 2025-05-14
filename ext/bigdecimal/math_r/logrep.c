/*******************************************************************************
	logrep.c -- Logarithm Representations

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"


/**
 * Computes the inverse sine of +x+.
 * 
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::LogRep.asin(BigDecimal('0.001'), 20) # Series expansion
 *  #=> 0.100000150000562503e-2
 *  BigMathR::LogRep.asin(BigDecimal('0.5'), 20) # Logarithmic reprensentation
 *  #=> 0.52359877559829887308e0
 * @since 0.1.0
 */
static VALUE
__impl_logrep_asin(VALUE unused_obj, VALUE x, VALUE prec)
{
	return asin_branch(x, prec, asin_logrep);
}


/**
 * Computes the inverse cosine of +x+.
 * 
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::LogRep.acos(BigDecimal('0.001'), 20) # Series expansion
 *  #=> 0.15697963252948909942e1
 *  BigMathR::LogRep.acos(BigDecimal('0.5'), 20) # Logarithmic reprensentation
 *  #=> 0.10471975511965977462e1
 * @since 0.1.0
 */
static VALUE
__impl_logrep_acos(VALUE unused_obj, VALUE x, VALUE prec)
{
	return acos_branch(x, prec, acos_logrep);
}

/**
 * Computes the inverse tangent of +x+.
 * 
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  -BigMathR::LogRep.atan(-1, 20).mult(4, 20)
 *  #=> 0.31415926535897932385e1
 * @since 0.1.0
 */
static VALUE
__impl_logrep_atan(VALUE unused_obj, VALUE x, VALUE prec)
{
	return atan_branch(x, prec, atan_logrep);
}

/**
 * Computes the inverse cosecant of +x+.
 * 
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::LogRep.acsc(2, 20)
 *  #=> 0.52359877559829887308e0
 * @since 0.1.0
 */
static VALUE
__impl_logrep_acsc(VALUE unused_obj, VALUE x, VALUE prec)
{
	return acsc_branch(x, prec, acsc_logrep);
}

/**
 * Computes the inverse secant of +x+.
 * 
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::LogRep.asec(2, 20)
 *  #=> 0.10471975511965977462e1
 * @since 0.1.0
 */
static VALUE
__impl_logrep_asec(VALUE unused_obj, VALUE x, VALUE prec)
{
	return asec_branch(x, prec, asec_logrep);
}

/**
 * Computes the inverse cotangent of +x+.
 * 
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::LogRep.acot(1, 20) * 4
 *  #=> 0.314159265358979323852e1
 * @since 0.1.0
 */
static VALUE
__impl_logrep_acot(VALUE unused_obj, VALUE x, VALUE prec)
{
	return acot_branch(x, prec, acot_logrep);
}

/**
 * Computes inverse hyperbolic cotangent of +x+.
 * 
 * @example
 *  BigMathR::LogRep.asinh(1/2000r, 20) # Series expansion
 *  #=> 0.49999997916666901e-3
 *  BigMathR::LogRep.asinh(1, 20) # Logarithmic representation
 *  #=> 0.88137358701954302523e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
__impl_logrep_asinh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return asinh_branch(x, prec, asinh_logrep);
}

/**
 * Computes inverse hyperbolic cosine of +x+.
 * 
 * @example
 *  BigMathR::LogSqrt.acosh(2, 20) # Logarithmic presentation
 *  #=> 0.13169578969248167086e1
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_acosh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return acosh_branch(x, prec, acosh_logrep);
}

/**
 * Computes inverse hyperbolic tangent of +x+.
 * 
 * @example
 *  BigMathR::LogRep.atanh(1/3r, 20) # Series expansion
 *  #=> 0.3465735902799726547e0
 *  BigMathR::LogRep.atanh(9999/10000r, 20) # Logarithmic representation
 *  #=> 0.49517187756430431886e1
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_atanh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return atanh_branch(x, prec, atanh_logrep);
}

/**
 * Computes inverse hyperbolic cosecant of +x+.
 * 
 * @example
 *  BigMathR::LogRep.acsch(1, 20)
 *  #=> 0.88137358701954302523e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_acsch(VALUE unused_obj, VALUE x, VALUE prec)
{
	return acsch_branch(x, prec, acsch_logrep);
}

/**
 * Computes inverse hyperbolic secant of +x+.
 * 
 * @example
 *  BigMathR::LogRep.asech(1/2r, 20)
 *  #=> 0.13169578969248167087e1
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_asech(VALUE unused_obj, VALUE x, VALUE prec)
{
	return asech_branch(x, prec, asech_logrep);
}

/**
 * Computes inverse hyperbolic cotangent of +x+.
 * 
 * @example
 *  BigMathR::LogRep.acoth(2, 20)
 *  #=> 0.54930614433405484568e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_acoth(VALUE unused_obj, VALUE x, VALUE prec)
{
	return acoth_branch(x, prec, acoth_logrep);
}

/**
 * Computes complex inverse sine of +z+.
 * 
 * @example
 *  BigMathR::LogRep.casin(1+1i, 20)
 *  #=> (0.6662394324925152551e0+0.1061275061905035652e1i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_casin(VALUE unused_obj, VALUE z, VALUE prec)
{
	return casin_branch(z, prec, casin_logrep);
}

/**
 * Computes complex inverse cosine of +z+.
 * 
 * @example
 *  BigMathR::LogRep.cacos(1+1i, 20)
 *  #=> (0.9045568943023813642e0-0.1061275061905035652e1i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_cacos(VALUE unused_obj, VALUE z, VALUE prec)
{
	return cacos_branch(z, prec, cacos_logrep);
}

/**
 * Computes complex inverse tangent of +z+.
 * 
 * @example
 *  BigMathR::LogRep.catan(1+1i, 20)
 *  #=> (0.10172219678978513678e1+0.40235947810852509365e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_catan(VALUE unused_obj, VALUE z, VALUE prec)
{
	return catan_branch(z, prec, catan_logrep);
}

/**
 * Computes complex inverse cosecant of +z+.
 * 
 * @example
 *  BigMathR::LogRep.cacsc(1+1i, 20)
 *  #=> (0.45227844715119068206e0-0.53063753095251782602e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_cacsc(VALUE unused_obj, VALUE z, VALUE prec)
{
	return cacsc_branch(z, prec, cacsc_logrep);
}

/**
 * Computes complex inverse secant of +z+.
 * 
 * @example
 *  BigMathR::LogRep.casec(1+1i, 20)
 *  #=> (0.11185178796437059372e1+0.53063753095251782602e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_casec(VALUE unused_obj, VALUE z, VALUE prec)
{
	return casec_branch(z, prec, casec_logrep);
}

/**
 * Computes complex inverse cotangent of +z+.
 * 
 * @example
 *  BigMathR::LogRep.cacot(1+1i, 20)
 *  #=> (0.55357435889704525152e0-0.40235947810852509365e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_cacot(VALUE unused_obj, VALUE z, VALUE prec)
{
	return cacot_branch(z, prec, cacot_logrep);
}

/**
 * Computes complex inverse hyperbolic sine of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.casinh(1+1i, 20)
 *  #=> (0.1061275061905035652e1+0.6662394324925152551e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_casinh(VALUE unused_obj, VALUE z, VALUE prec)
{
	return casinh_branch(z, prec, casinh_logrep);
}

/**
 * Computes complex inverse hyperbolic cosine of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.cacosh(1+1i, 20)
 *  #=> (0.1061275061905035652e1+0.9045568943023813642e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_cacosh(VALUE unused_obj, VALUE z, VALUE prec)
{
	return cacosh_branch(z, prec, cacosh_logrep);
}

/**
 * Computes complex inverse hyperbolic tangent of +z+.
 * 
 * @example
 *  BigMathR::LogRep.catanh(1+1i, 20)
 *  #=> (0.40235947810852509365e0+0.10172219678978513678e1i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_catanh(VALUE unused_obj, VALUE z, VALUE prec)
{
	return catanh_branch(z, prec, catanh_logrep);
}

/**
 * Computes complex inverse hyperbolic cosecant of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.cacsch(1+1i, 20)
 *  #=> (0.53063753095251782602e0-0.45227844715119068206e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_cacsch(VALUE unused_obj, VALUE z, VALUE prec)
{
	return cacsch_branch(z, prec, cacsch_logrep);
}

/**
 * Computes complex inverse hyperbolic secant of +z+.
 * 
 * @example
 *  BigMathR::LogRep.casech(1+1i, 20)
 *  #=> (0.53063753095251782602e0-0.11185178796437059372e1i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_casech(VALUE unused_obj, VALUE z, VALUE prec)
{
	return casech_branch(z, prec, casech_logrep);
}

/**
 * Computes complex inverse hyperbolic cotangent of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.cacoth(1+1i, 20)
 *  #=> (0.40235947810852509365e0-0.55357435889704525152e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_logrep_cacoth(VALUE unused_obj, VALUE z, VALUE prec)
{
	return cacoth_branch(z, prec, cacoth_logrep);
}


/**
 *  Document-module:  BigMathR::LogRep
 *  
 *  A module that provides the logarithmic representations. 
 *  It is used internally.
 *  <br>
 *  == Synopsis
 *  The function names defined are the same as those in the C/C++ standard.
 *  <br>
 *  - Inverse sine:                 +:asin+  +:casin+ <br>
 *  - Inverse cosine:               +:acos+  +:cacos+ <br>
 *  - Inverse tangent:              +:atan+  +:catan+ <br>
 *  - Inverse hyperbolic sine:      +:asinh+ +:casinh+ <br>
 *  - Inverse hyperbolic cosine:    +:acosh+ +:cacosh+ <br>
 *  - Inverse hyperbolic tangent:   +:atanh+ +:catanh+ <br>
 *  Follow, the name defined in C/C++ standard though, the function names are different.
 *  <br>
 *  - Inverse cosecant:             +:acsc+  +:cacsc+ <br>
 *  - Inverse secant:               +:asec+  +:casec+ <br>
 *  - Inverse cotangent:            +:acot+  +:cacot+ <br>
 *  - Inverse hyperbolic cosecant:  +:acsch+ +:cacsch+ <br>
 *  - Inverse hyperbolic secant:    +:asech+ +:casech+ <br>
 *  - Inverse hyperbolic cotangent: +:acoth+ +:cacoth+ <br>
 *  Reference::
 *  {https://mathworld.wolfram.com/NaturalLogarithm.html Wolfram Mathworld - Natural Logarithm}
 */

void
InitVM_LogRep(void)
{
	rb_define_module_function(rb_mLogRep, "asin", __impl_logrep_asin, 2);
	rb_define_module_function(rb_mLogRep, "acos", __impl_logrep_acos, 2);
	rb_define_module_function(rb_mLogRep, "atan", __impl_logrep_atan, 2);
	rb_define_module_function(rb_mLogRep, "acsc", __impl_logrep_acsc, 2);
	rb_define_module_function(rb_mLogRep, "asec", __impl_logrep_asec, 2);
	rb_define_module_function(rb_mLogRep, "acot", __impl_logrep_acot, 2);

	rb_define_module_function(rb_mLogRep, "asinh", __impl_logrep_asinh, 2);
	rb_define_module_function(rb_mLogRep, "acosh", __impl_logrep_acosh, 2);
	rb_define_module_function(rb_mLogRep, "atanh", __impl_logrep_atanh, 2);
	rb_define_module_function(rb_mLogRep, "acsch", __impl_logrep_acsch, 2);
	rb_define_module_function(rb_mLogRep, "asech", __impl_logrep_asech, 2);
	rb_define_module_function(rb_mLogRep, "acoth", __impl_logrep_acoth, 2);

	rb_define_module_function(rb_mLogRep, "casin", __impl_logrep_casin, 2);
	rb_define_module_function(rb_mLogRep, "cacos", __impl_logrep_cacos, 2);
	rb_define_module_function(rb_mLogRep, "catan", __impl_logrep_catan, 2);
	rb_define_module_function(rb_mLogRep, "cacsc", __impl_logrep_cacsc, 2);
	rb_define_module_function(rb_mLogRep, "casec", __impl_logrep_casec, 2);
	rb_define_module_function(rb_mLogRep, "cacot", __impl_logrep_cacot, 2);

	rb_define_module_function(rb_mLogRep, "casinh", __impl_logrep_casinh, 2);
	rb_define_module_function(rb_mLogRep, "cacosh", __impl_logrep_cacosh, 2);
	rb_define_module_function(rb_mLogRep, "catanh", __impl_logrep_catanh, 2);
	rb_define_module_function(rb_mLogRep, "cacsch", __impl_logrep_cacsch, 2);
	rb_define_module_function(rb_mLogRep, "casech", __impl_logrep_casech, 2);
	rb_define_module_function(rb_mLogRep, "cacoth", __impl_logrep_cacoth, 2);

}
