/*******************************************************************************
	math_r.c -- Entrypoint

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#define DEFINE_SYMBOL
#include "math_r/globals.h"
#include "math_r/bigmath.h"

void InitVM_Overrides(void);
void InitVM_Const(void);
void InitVM_EDF(void);
void InitVM_Exp(void);
void InitVM_Log(void);
void InitVM_Trig(void);
void InitVM_Hyperb(void);
void InitVM_ComplexPlane(void);
void InitVM_EulerF(void);
void InitVM_LogRep(void);
void InitVM_Power(void);
void InitVM_Erf(void);
void InitVM_GammaR(void);
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
	rb_gv_set(BIGMATH_PI, Qnil);
	rb_gv_set(BIGMATH_E, Qnil);
	rb_gv_set(BIGMATH_LOG2, Qnil);
	rb_gv_set(BIGMATH_LOG10, Qnil);
	rb_gv_set(BIGMATH_LOG_PI, Qnil);
	rb_gv_set(BIGMATH_SQRT2, Qnil);
	rb_gv_set(BIGMATH_SQRT3, Qnil);

	mf_exp = rb_intern_const("exp");
	mf_exp2 = rb_intern_const("exp2");
	mf_expm1 = rb_intern_const("expm1");

	mf_log = rb_intern_const("log");
	mf_log2 = rb_intern_const("log2");
	mf_log10 = rb_intern_const("log10");
	mf_log1p = rb_intern_const("log1p");

	mf_sqrt = rb_intern_const("sqrt");
	mf_cbrt = rb_intern_const("cbrt");

	mf_sin = rb_intern_const("sin");
	mf_cos = rb_intern_const("cos");
	mf_tan = rb_intern_const("tan");
	mf_csc = rb_intern_const("csc");
	mf_sec = rb_intern_const("sec");
	mf_cot = rb_intern_const("cot");

	mf_sinh = rb_intern_const("sinh");
	mf_cosh = rb_intern_const("cosh");
	mf_tanh = rb_intern_const("tanh");
	mf_csch = rb_intern_const("csch");
	mf_sech = rb_intern_const("sech");
	mf_coth = rb_intern_const("coth");

	mf_asin = rb_intern_const("asin");
	mf_acos = rb_intern_const("acos");
	mf_atan = rb_intern_const("atan");
	mf_acsc = rb_intern_const("acsc");
	mf_asec = rb_intern_const("asec");
	mf_acot = rb_intern_const("acot");

	mf_asinh = rb_intern_const("asinh");
	mf_acosh = rb_intern_const("acosh");
	mf_atanh = rb_intern_const("atanh");
	mf_acsch = rb_intern_const("acsch");
	mf_asech = rb_intern_const("asech");
	mf_acoth = rb_intern_const("acoth");

	rb_require("bigdecimal/math");
	rb_cBigDecimal = rb_const_get_at(rb_cObject, rb_intern("BigDecimal"));
	rb_mBigMath = rb_const_get_at(rb_cObject, rb_intern("BigMath"));

	rb_mBigMathR = rb_define_module("BigMathR");
	rb_mMathSolver = rb_define_module_under(rb_mBigMathR, "Solver");

	InitVM(Overrides);

	rb_mConst = rb_define_module_under(rb_mBigMathR, "Const");
	rb_mConstPI = rb_define_module_under(rb_mConst, "PI");
	rb_mConstE = rb_define_module_under(rb_mConst, "E");
	rb_mConstLOG2 = rb_define_module_under(rb_mConst, "LOG2");
	rb_mConstEulerGamma = rb_define_module_under(rb_mConst, "EulerGamma");
	InitVM(Const);

	rb_mEDF = rb_define_module_under(rb_mBigMathR, "EDF");
	InitVM(EDF);

	rb_mExp = rb_define_module_under(rb_mBigMathR, "Exp");
	InitVM(Exp);

	rb_mLog = rb_define_module_under(rb_mBigMathR, "Log");
	InitVM(Log);

	rb_mTrig = rb_define_module_under(rb_mBigMathR, "Trig");
	InitVM(Trig);

	rb_mHyperb = rb_define_module_under(rb_mBigMathR, "Hyperb");
	InitVM(Hyperb);

	rb_mComplexPlane = rb_define_module_under(rb_mBigMathR, "ComplexPlane");
	InitVM(ComplexPlane);

	rb_mEulerF = rb_define_module_under(rb_mBigMathR, "EulerF");
	InitVM(EulerF);

	rb_mLogRep = rb_define_module_under(rb_mBigMathR, "LogRep");
	InitVM(LogRep);

	rb_mPower = rb_define_module_under(rb_mBigMathR, "Power");
	InitVM(Power);

	rb_mErf = rb_define_module_under(rb_mBigMathR, "Erf");
	InitVM(Erf);

	rb_mGammaR = rb_define_module_under(rb_mBigMathR, "GammaR");
	InitVM(GammaR);

	rb_mSolver = rb_define_module_under(rb_mBigMathR, "Solver");
	InitVM(Solver);
}

