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
void InitVM_Logarithm(void);
void InitVM_Trigonometric(void);
void InitVM_ComplexPlane(void);
void InitVM_EulerF(void);
void InitVM_LogSqrt(void);
void InitVM_PowerRoot(void);
void InitVM_Solver(void);

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

	rb_mLogarithm = rb_define_module_under(rb_mBigMathR, "Logarithm");
	InitVM(Logarithm);

	rb_mTrigonometric = rb_define_module_under(rb_mBigMathR, "Trigonometric");
	InitVM(Trigonometric);

	rb_mComplexPlane = rb_define_module_under(rb_mBigMathR, "ComplexPlane");
	InitVM(ComplexPlane);

	rb_mEulerF = rb_define_module_under(rb_mBigMathR, "EulerF");
	InitVM(EulerF);

	rb_mLogSqrt = rb_define_module_under(rb_mBigMathR, "LogSqrt");
	InitVM(LogSqrt);

	rb_mPowerRoot = rb_define_module_under(rb_mBigMathR, "PowerRoot");
	InitVM(PowerRoot);

	rb_mSolver = rb_define_module_under(rb_mBigMathR, "Solver");
	InitVM(Solver);

}

