/*******************************************************************************
	api.c -- API for Numeric

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/bigmath_r.h"

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
