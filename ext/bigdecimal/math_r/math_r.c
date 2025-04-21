/*******************************************************************************
	math_r.c -- Entrypoint

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#define DEFINE_SYMBOL
#include "math_r/globals.h"

void InitVM_Constant(void);
void InitVM_EDF(void);
void InitVM_Log(void);
void InitVM_Trig(void);
void InitVM_ComplexPlane(void);
void InitVM_EulerF(void);
void InitVM_LogSqrt(void);
void InitVM_PowerRoot(void);
void InitVM_GammaR(void);
void InitVM_Solver(void);

#include "math_r/numeric.h"

/**
 * The #nan? method for primitive. Always return false.
 * 
 * @example
 *  1.nan? #=> false
 * @return [false] Whether self is Not a Number(NaN).
 */
static VALUE
numeric_nan_p(VALUE self)
{
	return Qfalse;
}

/**
 * Calculates "i z" so inverts the real and imaginary maps of +z+.
 * 
 * @example
 *  Complex.imaginary_z(1+2i) #=> (-2+1i)
 *  -Complex.imaginary_z(1+2i) #=> (2-1i)
 * @param z [Numeric] Numerical argument
 * @return [Complex] Solve
 */
static VALUE
__impl_nucomp_s_imaginary_z(VALUE self, VALUE z)
{
	return rb_ImaginaryZ(z, SIGN_PLUS);
}

/**
 * Document-module:  BigMathR
 * 
 * Refined BigMath module.
 * It is a total solution for mathematics that also supports complex numbers.
 *  
 * Reference::
 * Utsukusii Suugaku wo egaku π, ｅ, to Euler no teisuu γ (Japanese) - WAKAHARA Tatsuhiko (Kohdan-sha Editorial)
 */
void
Init_math_r(void)
{
	rb_require("bigdecimal/math");
	rb_cBigDecimal = rb_const_get_at(rb_cObject, rb_intern("BigDecimal"));
	rb_mBigMath = rb_const_get_at(rb_cObject, rb_intern("BigMath"));

	rb_mBigMathR = rb_define_module("BigMathR");
	rb_mMathSolver = rb_define_module_under(rb_mBigMathR, "Solver");

	InitVM(Constant);

	rb_mEDF = rb_define_module_under(rb_mBigMathR, "EDF");
	InitVM(EDF);

	rb_mLog = rb_define_module_under(rb_mBigMathR, "Log");
	InitVM(Log);

	rb_mTrig = rb_define_module_under(rb_mBigMathR, "Trig");
	InitVM(Trig);

	rb_mComplexPlane = rb_define_module_under(rb_mBigMathR, "ComplexPlane");
	InitVM(ComplexPlane);

	rb_mEulerF = rb_define_module_under(rb_mBigMathR, "EulerF");
	InitVM(EulerF);

	rb_mLogSqrt = rb_define_module_under(rb_mBigMathR, "LogSqrt");
	InitVM(LogSqrt);

	rb_mPowerRoot = rb_define_module_under(rb_mBigMathR, "PowerRoot");
	InitVM(PowerRoot);

	rb_mGammaR = rb_define_module_under(rb_mBigMathR, "GammaR");
	InitVM(GammaR);

	rb_mSolver = rb_define_module_under(rb_mBigMathR, "Solver");
	InitVM(Solver);

	rb_define_method(rb_cNumeric, "nan?", numeric_nan_p, 0);
	rb_define_singleton_method(rb_cComplex, "imaginary_z", __impl_nucomp_s_imaginary_z, 1);
}

