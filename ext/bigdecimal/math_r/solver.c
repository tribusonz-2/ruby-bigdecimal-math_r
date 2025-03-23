/*******************************************************************************
	solver.c -- BigMathR::Solver

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "internal/solver/bigmath_r.h"

#define SYM(str) ID2SYM(rb_intern(str))


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
 *  @!attribute [r] exp
 *    @return [BigDecimal] Solve of hooked function +exp(x, prec)+
 *  @!attribute [r] exp2
 *    @return [BigDecimal] Solve of hooked function +exp2(x, prec)+
 *  @!attribute [r] cexp
 *    @return [Complex] Solve of hooked function +exp(x, prec)+
 *  @!attribute [r] cexp2
 *    @return [Complex] Solve of hooked function +exp2(x, prec)+
 *  @!attribute [r] sinh
 *    @return [BigDecimal] Solve of hooked function +sinh(x, prec)+
 *  @!attribute [r] cosh
 *    @return [BigDecimal] Solve of hooked function +cosh(x, prec)+
 *  @!attribute [r] tanh
 *    @return [BigDecimal] Solve of hooked function +tanh(x, prec)+
 *  @!attribute [r] csch
 *    @return [BigDecimal] Solve of hooked function +csch(x, prec)+
 *  @!attribute [r] sech
 *    @return [BigDecimal] Solve of hooked function +sech(x, prec)+
 *  @!attribute [r] coth
 *    @return [BigDecimal] Solve of hooked function +coth(x, prec)+
 *  @!attribute [r] csinh
 *    @return [Complex] Solve of hooked function +csinh(z, prec)+
 *  @!attribute [r] ccosh
 *    @return [Complex] Solve of hooked function +ccosh(z, prec)+
 *  @!attribute [r] ctanh
 *    @return [Complex] Solve of hooked function +ctanh(z, prec)+
 *  @!attribute [r] ccsch
 *    @return [Complex] Solve of hooked function +ccsch(z, prec)+
 *  @!attribute [r] csech
 *    @return [Complex] Solve of hooked function +csech(z, prec)+
 *  @!attribute [r] ccoth
 *    @return [Complex] Solve of hooked function +ccoth(z, prec)+
 */
void
InitVM_Solver(void)
{
	const ID method = rb_intern("method");

	rb_iv_set(rb_mMathSolver, "@exp",
		rb_funcall(rb_mEDF, method, 1, SYM("exp")));
	rb_iv_set(rb_mMathSolver, "@cexp",
		rb_funcall(rb_mTrigExp, method, 1, SYM("cexp")));

	rb_iv_set(rb_mMathSolver, "@log",
		rb_funcall(rb_mEDF, method, 1, SYM("log")));
	rb_iv_set(rb_mMathSolver, "@clog",
		rb_funcall(rb_mLogSqrt, method, 1, SYM("clog")));

	rb_iv_set(rb_mMathSolver, "@log2",
		rb_funcall(rb_mEDF, method, 1, SYM("log2")));
	rb_iv_set(rb_mMathSolver, "@clog2",
		rb_funcall(rb_mLogSqrt, method, 1, SYM("clog2")));

	rb_iv_set(rb_mMathSolver, "@log10",
		rb_funcall(rb_mEDF, method, 1, SYM("log10")));
	rb_iv_set(rb_mMathSolver, "@clog10",
		rb_funcall(rb_mLogSqrt, method, 1, SYM("clog10")));

	rb_iv_set(rb_mMathSolver, "@exp2",
		rb_funcall(rb_mEDF, method, 1, SYM("exp2")));
	rb_iv_set(rb_mMathSolver, "@cexp2",
		rb_funcall(rb_mTrigExp, method, 1, SYM("cexp2")));

	rb_iv_set(rb_mMathSolver, "@sin",
		rb_funcall(rb_mTrigonometric, method, 1, SYM("sin")));
	rb_iv_set(rb_mMathSolver, "@csin",
		rb_funcall(rb_mTrigExp, method, 1, SYM("csin")));

	rb_iv_set(rb_mMathSolver, "@cos",
		rb_funcall(rb_mTrigonometric, method, 1, SYM("cos")));
	rb_iv_set(rb_mMathSolver, "@ccos",
		rb_funcall(rb_mTrigExp, method, 1, SYM("ccos")));

	rb_iv_set(rb_mMathSolver, "@tan",
		rb_funcall(rb_mTrigonometric, method, 1, SYM("tan")));
	rb_iv_set(rb_mMathSolver, "@ctan",
		rb_funcall(rb_mTrigExp, method, 1, SYM("ctan")));

	rb_iv_set(rb_mMathSolver, "@csc",
		rb_funcall(rb_mTrigonometric, method, 1, SYM("csc")));
	rb_iv_set(rb_mMathSolver, "@ccsc",
		rb_funcall(rb_mTrigExp, method, 1, SYM("ccsc")));

	rb_iv_set(rb_mMathSolver, "@sec",
		rb_funcall(rb_mTrigonometric, method, 1, SYM("sec")));
	rb_iv_set(rb_mMathSolver, "@csec",
		rb_funcall(rb_mTrigExp, method, 1, SYM("csec")));

	rb_iv_set(rb_mMathSolver, "@cot",
		rb_funcall(rb_mTrigonometric, method, 1, SYM("cot")));
	rb_iv_set(rb_mMathSolver, "@ccot",
		rb_funcall(rb_mTrigExp, method, 1, SYM("ccot")));

	rb_iv_set(rb_mMathSolver, "@asin", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("asin")));
	rb_iv_set(rb_mMathSolver, "@casin", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("casin")));

	rb_iv_set(rb_mMathSolver, "@acos", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("acos")));
	rb_iv_set(rb_mMathSolver, "@cacos", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("cacos")));

	rb_iv_set(rb_mMathSolver, "@atan", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("atan")));
	rb_iv_set(rb_mMathSolver, "@catan", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("catan")));

	rb_iv_set(rb_mMathSolver, "@atan2", 
		rb_funcall(rb_mBigMathR, method, 1, SYM("atan2")));

	rb_iv_set(rb_mMathSolver, "@acsc", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("acsc")));
	rb_iv_set(rb_mMathSolver, "@cacsc", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("cacsc")));

	rb_iv_set(rb_mMathSolver, "@asec", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("asec")));
	rb_iv_set(rb_mMathSolver, "@casec", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("casec")));

	rb_iv_set(rb_mMathSolver, "@acot", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("acot")));
	rb_iv_set(rb_mMathSolver, "@cacot", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("cacot")));

	rb_iv_set(rb_mMathSolver, "@sinh",
		rb_funcall(rb_mTrigExp, method, 1, SYM("sinh")));
	rb_iv_set(rb_mMathSolver, "@csinh",
		rb_funcall(rb_mTrigExp, method, 1, SYM("csinh")));

	rb_iv_set(rb_mMathSolver, "@cosh",
		rb_funcall(rb_mTrigExp, method, 1, SYM("cosh")));
	rb_iv_set(rb_mMathSolver, "@ccosh",
		rb_funcall(rb_mTrigExp, method, 1, SYM("ccosh")));

	rb_iv_set(rb_mMathSolver, "@tanh",
		rb_funcall(rb_mTrigExp, method, 1, SYM("tanh")));
	rb_iv_set(rb_mMathSolver, "@ctanh",
		rb_funcall(rb_mTrigExp, method, 1, SYM("ctanh")));

	rb_iv_set(rb_mMathSolver, "@csch",
		rb_funcall(rb_mTrigExp, method, 1, SYM("csch")));
	rb_iv_set(rb_mMathSolver, "@ccsch",
		rb_funcall(rb_mTrigExp, method, 1, SYM("ccsch")));

	rb_iv_set(rb_mMathSolver, "@sech",
		rb_funcall(rb_mTrigExp, method, 1, SYM("sech")));
	rb_iv_set(rb_mMathSolver, "@csech",
		rb_funcall(rb_mTrigExp, method, 1, SYM("csech")));

	rb_iv_set(rb_mMathSolver, "@coth",
		rb_funcall(rb_mTrigExp, method, 1, SYM("coth")));
	rb_iv_set(rb_mMathSolver, "@ccoth",
		rb_funcall(rb_mTrigExp, method, 1, SYM("ccoth")));

	rb_iv_set(rb_mMathSolver, "@asinh", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("asinh")));
	rb_iv_set(rb_mMathSolver, "@casinh", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("casinh")));

	rb_iv_set(rb_mMathSolver, "@acosh", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("acosh")));
	rb_iv_set(rb_mMathSolver, "@cacosh", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("cacosh")));

	rb_iv_set(rb_mMathSolver, "@atanh", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("atanh")));
	rb_iv_set(rb_mMathSolver, "@catanh", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("catanh")));

	rb_iv_set(rb_mMathSolver, "@acsch", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("acsch")));
	rb_iv_set(rb_mMathSolver, "@cacsch", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("cacsch")));

	rb_iv_set(rb_mMathSolver, "@asech", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("asech")));
	rb_iv_set(rb_mMathSolver, "@casech", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("casech")));

	rb_iv_set(rb_mMathSolver, "@acoth", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("acoth")));
	rb_iv_set(rb_mMathSolver, "@cacoth", 
		rb_funcall(rb_mLogSqrt, method, 1, SYM("cacoth")));

	rb_iv_set(rb_mMathSolver, "@sqrt",
		rb_funcall(rb_mPowerRoot, method, 1, SYM("sqrt")));
	rb_iv_set(rb_mMathSolver, "@csqrt",
		rb_funcall(rb_mPowerRoot, method, 1, SYM("csqrt")));

	rb_iv_set(rb_mMathSolver, "@cbrt",
		rb_funcall(rb_mPowerRoot, method, 1, SYM("cuberoot")));
	rb_iv_set(rb_mMathSolver, "@ccbrt",
		rb_funcall(rb_mPowerRoot, method, 1, SYM("ccbrt")));

	rb_iv_set(rb_mMathSolver, "@cabs",
		rb_funcall(rb_mComplexPlane, method, 1, SYM("cabs")));

	rb_iv_set(rb_mMathSolver, "@carg",
		rb_funcall(rb_mComplexPlane, method, 1, SYM("carg")));

}
