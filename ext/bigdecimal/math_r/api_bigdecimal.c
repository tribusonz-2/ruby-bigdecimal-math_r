/*******************************************************************************
	api_bigdecimal.c -- API for BigDecimal

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"

#include "api/kernel/rb_BigDecimal.h"
#include "api/kernel/rb_BigDecimal1.h"
#include "api/kernel/rb_BigDecimal_flo.h"

#include "api/bigdecimal/check_precise.h"
#include "api/bigdecimal/zero.h"
#include "api/bigdecimal/minus_zero.h"
#include "api/bigdecimal/one.h"
#include "api/bigdecimal/minus_one.h"
#include "api/bigdecimal/infinity.h"
#include "api/bigdecimal/minus_infinity.h"
#include "api/bigdecimal/nan.h"
#include "api/bigdecimal/sign.h"

#include "api/numeric/canonicalize.h"
#include "api/numeric/round.h"

#include "api/numdiff/condition_p.h"
#include "api/numdiff/make_n.h"
#include "api/numdiff/keep_fig.h"
