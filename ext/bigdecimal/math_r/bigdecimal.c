/*******************************************************************************
	bigdecimal.c -- API for BigDecimal

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "internal/solver/bigmath_r.h"


void
rb_check_precise(VALUE prec)
{
	const ID leq = rb_intern("<=");
	if (TYPE(prec) == T_FIXNUM || TYPE(prec) == T_BIGNUM)
	{
		if (RTEST(rb_num_coerce_cmp(prec, INT2NUM(0), leq)))
			rb_raise(rb_eRangeError, "Zero or negative precision");
	}
	else
		rb_raise(rb_eTypeError, "precision must be an Integer");
}


VALUE
rb_big_zero(void)
{
	VALUE y = rb_BigDecimal1(INT2FIX(0));
	return y;
}


VALUE
rb_big_minus_zero(void)
{
	VALUE y = rb_BigDecimal1(rb_str_new_cstr("-0"));
	return y;
}


VALUE
rb_big_one(void)
{
	VALUE y = rb_BigDecimal1(INT2FIX(1));
	return y;
}


VALUE
rb_big_minus_one(void)
{
	VALUE y = rb_BigDecimal1(INT2FIX(-1));
	return y;
}


VALUE
rb_big_infinity(void)
{
	const ID _INFINITY = rb_intern("INFINITY");
	return rb_const_get_at(rb_cBigDecimal, _INFINITY);
}


VALUE
rb_big_minus_infinity(void)
{
	return rb_num_uminus(rb_big_infinity());
}


VALUE
rb_big_nan(void)
{
	const ID _NAN = rb_intern("NAN");
	return rb_const_get_at(rb_cBigDecimal, _NAN);
}


VALUE
rb_BigDecimal(VALUE x, VALUE prec)
{
	const ID BigDecimal = rb_intern("BigDecimal");
	return rb_funcall(rb_cObject, BigDecimal, 2, x, prec);
}


VALUE
rb_BigDecimal1(VALUE x)
{
	const ID BigDecimal = rb_intern("BigDecimal");
	return rb_funcall(rb_cObject, BigDecimal, 1, x);
}


VALUE
rb_BigDecimal_flo(VALUE x)
{
	const ID BigDecimal = rb_intern("BigDecimal");
	const ID DIG = rb_intern("DIG");
	VALUE FLOAT_DIG = rb_const_get_at(rb_cFloat, DIG);
	VALUE y = rb_funcall(rb_cObject, BigDecimal, 2, x, FLOAT_DIG);
	return y;
}


static VALUE
canonicalize_decimalize(VALUE x, VALUE prec)
{
	switch (TYPE(x)) {
	case T_FIXNUM:
	case T_BIGNUM:
		x = rb_BigDecimal1(x);
		break;
	case T_FLOAT:
		x = rb_BigDecimal_flo(x);
		break;
	case T_RATIONAL:
		x = rb_BigDecimal(x, prec);
		break;
	default:
		break;
	}
	return x;
}

static inline VALUE
canonicalize_iter(RB_BLOCK_CALL_FUNC_ARGLIST(val, _))
{
	const ID abs2 = rb_intern("abs2");
	return rb_funcall(val, abs2, 0);
}

VALUE
rb_bigmath_canonicalize(VALUE x, VALUE prec, bool complex_form, bool inversion)
{
	const ID sum = rb_intern("sum");
	const ID div = rb_intern("div");
retry:
	switch (TYPE(x)) {
	case T_FIXNUM:
	case T_BIGNUM:
		if (inversion)
			{ x = rb_Rational(INT2FIX(1), x); x = rb_BigDecimal(x, prec); }
		else
			x = rb_BigDecimal1(x);
		if (complex_form)
			x = rb_Complex(x, BIG_ZERO);
		break;
	case T_FLOAT:
		if (inversion)
			x = DBL2NUM(1 / NUM2DBL(x));
		x = rb_BigDecimal_flo(x);
		if (complex_form)
			x = rb_Complex(x, BIG_ZERO);
		break;
	case T_RATIONAL:
		if (inversion)
			x = rb_funcall1(INT2FIX(1), '/', x);
		x = rb_BigDecimal(x, prec);
		if (complex_form)
			x = rb_Complex(x, BIG_ZERO);
		break;
	case T_COMPLEX:
		if (rb_num_zero_p(x))
		{
			x = rb_num_real(x);
			goto retry;
		}
		else if (!complex_form && rb_num_nonzero_p(rb_num_imag(x)))
			rb_raise(rb_eTypeError, "not a Real");
		else if (
		    (!complex_form &&
		      rb_num_zero_p(rb_num_imag(x))) ||
		     (complex_form &&
		      rb_num_infinite_p(rb_num_real(x)) &&
		      rb_num_finite_p(rb_num_imag(x))))
		{
			x = rb_num_real(x);
			goto retry;
		}
		else if (complex_form && rb_num_infinite_p(rb_num_imag(x)))
		{
			if (rb_num_finite_p(rb_num_real(x)))
				x = rb_Complex(BIG_ZERO, BIG_ZERO);
			else
				x = rb_Complex(BIG_NAN, BIG_NAN);
		}
		else if (complex_form)
		{
			VALUE norm, real, imag;
			real = canonicalize_decimalize(rb_num_real(x), prec);
			imag = canonicalize_decimalize(rb_num_imag(x), prec);
			if (inversion)
			{
				norm = rb_block_call(
					rb_assoc_new(
					  rb_num_real(x), 
					  rb_num_imag(x)), 
					sum, 0, NULL,
					canonicalize_iter, prec);
				real = rb_funcall(real, div, 2, norm, prec);
				imag = rb_funcall(imag, div, 2, norm, prec);
				x = rb_Complex(real, rb_num_uminus(imag));
			}
			else
			{
				x = rb_Complex(real, imag);
			}
		}
		else
			x = rb_Complex(BIG_NAN, BIG_NAN);
		break;
	case T_NIL: case T_TRUE: case T_FALSE:
		rb_raise(rb_eTypeError,
			"can't convert %"PRIsVALUE" into Numeric", rb_inspect(x));
		break;
	default:
		if (rb_class_superclass(CLASS_OF(x)) != rb_cNumeric)
			rb_raise(rb_eTypeError,
				"can't convert %"PRIsVALUE" into Numeric", CLASS_OF(x));
		else if (CLASS_OF(x) == rb_cBigDecimal)
		{
			if (inversion)
				x = rb_funcall(BIG_ONE, div, 2, x, prec);
			if (complex_form)
				x = rb_Complex(x, BIG_ZERO);
		}
		break;
	}
	if (complex_form && rb_num_real_p(x))
		x = rb_Complex(x, BIG_ZERO);
	return x;
}


VALUE
rb_BigDecimal_sign(VALUE d)
{
        const ID sign = rb_intern("sign");
	if (TYPE(d) == T_FIXNUM || TYPE(d) == T_BIGNUM)
		d = rb_BigDecimal1(d);
	else if (CLASS_OF(d) != rb_cBigDecimal)
		rb_raise(rb_eTypeError, "not a BigDecimal: rb_BigDecimal_sign()");
        return rb_funcall(d, sign, 0);
}


static inline VALUE
decimal_round_iter(RB_BLOCK_CALL_FUNC_ARGLIST(val, prec))
{
	const ID exponent = rb_intern("exponent");
	const ID round = rb_intern("round");
	VALUE exp;
	if (TYPE(val) == T_FIXNUM || TYPE(val) == T_BIGNUM)
		return val;
	RUBY_ASSERT(CLASS_OF(val) != rb_cBigDecimal);
	switch (NUM2INT(rb_BigDecimal_sign(val))) {
	case 0: case 1: case -1: case 3: case -3:
		goto retval;
		break;
	default:
		break;
	}
	exp = rb_funcall(val, exponent, 0);
	switch (FIX2INT(rb_dbl_cmp(NUM2DBL(exp), 0.))) {
	case 1: // up to integer-part
		val = rb_funcall(val, round, 1,
			LONG2NUM(NUM2LONG(prec)-NUM2LONG(exp)));
		break;
	case 0:
	case -1: // down to fraction-part
		val = rb_funcall(val, round, 1, prec);
		break;
	}
retval:
	return val;
}

VALUE
rb_bigmath_round_inline(VALUE x, VALUE prec)
{
	const ID map = rb_intern("map");
	VALUE arglist = rb_ary_new();
	if (rb_num_real_p(x))
	{
		rb_ary_store(arglist, 0, rb_num_real(x));
		arglist = rb_block_call(arglist, map, 0, NULL,
			decimal_round_iter, prec);

		x = rb_ary_entry(arglist, 0);
	}
	else
	{
		rb_ary_store(arglist, 0, rb_num_real(x));
		rb_ary_store(arglist, 1, rb_num_imag(x));
		arglist = rb_block_call(arglist, map, 0, NULL,
			decimal_round_iter, prec);
		x = rb_Complex(
			rb_ary_entry(arglist, 0),
			rb_ary_entry(arglist, 1));
	}
	return x;
}

bool
rb_numdiff_condition_p(VALUE y, VALUE d, VALUE n, VALUE *m)
{
	const ID exponent = rb_intern("exponent");
	const ID abs = rb_intern("abs");
	*m = rb_funcall(n, '-', 1, 
	       rb_funcall(
	         rb_funcall(
	           rb_funcall(y, exponent, 0), '-', 1, 
	           rb_funcall(d, exponent, 0)
	         ), abs, 0
	       )
	     );
	return rb_num_nonzero_p(d) && RTEST(rb_num_coerce_cmp(*m, INT2FIX(0), '>'));
}

VALUE
rb_numdiff_make_n(VALUE prec)
{
	const ID double_fig = rb_intern("double_fig");
	VALUE n;
	rb_check_precise(prec);
	n = rb_funcall(rb_funcall(rb_cBigDecimal, double_fig, 0), '+', 1, prec);
	return n;
}

void
rb_numdiff_keep_fig(VALUE *m)
{
	const ID double_fig = rb_intern("double_fig");
	VALUE dbl_fig = rb_funcall(rb_cBigDecimal, double_fig, 0);
	if (RTEST(rb_num_coerce_cmp(*m, dbl_fig, '<')))
		*m = dbl_fig;
}
