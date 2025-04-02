/*******************************************************************************
	api.c -- API for BigMathR

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"

#include "api/kernel/rb_BigDecimal.h"
#include "api/kernel/rb_BigDecimal1.h"
#include "api/kernel/rb_BigDecimal_flo.h"
#include "api/kernel/rb_ImaginaryZ.h"

#include "api/numeric/uminus.h"
#include "api/numeric/real.h"
#include "api/numeric/imag.h"
#include "api/numeric/positive_p.h"
#include "api/numeric/negative_p.h"
#include "api/numeric/equal_p.h"
#include "api/numeric/notequal_p.h"
#include "api/numeric/cmpeql.h"
#include "api/numeric/zero_p.h"
#include "api/numeric/nonzero_p.h"
#include "api/numeric/real_p.h"
#include "api/numeric/finite_p.h"
#include "api/numeric/infinite_p.h"
#include "api/numeric/nan_p.h"
#include "api/numeric/canonicalize.h"
#include "api/numeric/round.h"

#include "api/bigdecimal/check_precise.h"
#include "api/bigdecimal/zero.h"
#include "api/bigdecimal/minus_zero.h"
#include "api/bigdecimal/one.h"
#include "api/bigdecimal/minus_one.h"
#include "api/bigdecimal/infinity.h"
#include "api/bigdecimal/minus_infinity.h"
#include "api/bigdecimal/nan.h"
#include "api/bigdecimal/sign.h"

#include "api/bigmath/api_call1.h"
#include "api/bigmath/api_call2.h"

#include "api/numdiff/condition_p.h"
#include "api/numdiff/make_n.h"
