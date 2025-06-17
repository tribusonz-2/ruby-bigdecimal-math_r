/*******************************************************************************
	gamma_beta.c -- Gamma and Beta Functions

	Author: tribusonz
	Lisence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"

#if 0
VALUE gammar_q(VALUE, VALUE, VALUE, VALUE);


VALUE
gammar_p(VALUE a, VALUE x, VALUE loggamma_a, VALUE prec)
{
	const ID add = rb_intern("add");
	const ID geq = rb_intern(">=");
	VALUE zero = BIG_ZERO, one = BIG_ONE, result, term, previous, big_k;
	VALUE n;
	a = rb_num_canonicalize(a, prec, ARG_REAL, ARG_RAWVALUE);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	loggamma_a = rb_num_canonicalize(loggamma_a, prec, ARG_REAL, ARG_RAWVALUE);

	if (RTEST(rb_num_coerce_cmp(x, rb_funcall1(one, '+', a), geq)))
		return rb_funcall1(one, '-', gammar_q(a, x, loggamma_a, prec));

	if (rb_num_zero_p(x))
		return zero;

	n = rb_numdiff_make_n(prec);

	// result = term = exp(a * log(x, n) - x - loggamma_a, n) / a;
	term = rb_funcall1(a, '*', rb_bigmath_log(x, n));
	term = rb_funcall1(term, '-', x);
	term = rb_funcall1(term, '-', loggamma_a);
	term = rb_bigmath_exp(term, n);
	term = rb_funcall1(term, '/', a);
	result = term;

	big_k = one;

	for (int k = 1; k <= 1000; k++)
	{
		VALUE d = rb_funcall1(x, '/', rb_funcall1(a, '+', big_k));
		term = rb_funcall1(term, '*', d);
		previous = result; result = rb_funcall(result, add, 2, term, n);
		if (rb_num_equal_p(result, previous))
			goto retval;
		big_k = rb_funcall1(big_k, '+', one);
	}
	rb_warn("gammar_p(): can't converge.");
retval:
	RB_GC_GUARD(a);
	RB_GC_GUARD(x);
	RB_GC_GUARD(loggamma_a);
	RB_GC_GUARD(zero);
	RB_GC_GUARD(one);
	RB_GC_GUARD(result);
	RB_GC_GUARD(term);
	RB_GC_GUARD(previous);
	return result;
}

VALUE
gammar_q(VALUE a, VALUE x, VALUE loggamma_a, VALUE prec)
{
	const ID add = rb_intern("add");
	const ID div = rb_intern("div");
	VALUE one = BIG_ONE, two = rb_BigDecimal1(INT2FIX(2)), 
	      big_k, la, lb, w, result, temp, previous;
	VALUE n;
	a = rb_num_canonicalize(a, prec, ARG_REAL, ARG_RAWVALUE);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	loggamma_a = rb_num_canonicalize(loggamma_a, prec, ARG_REAL, ARG_RAWVALUE);
	
	if (RTEST(rb_num_coerce_cmp(x, rb_funcall1(one, '+', a), '<')))
		return rb_funcall1(one, '-', gammar_p(a, x, loggamma_a, prec));
	
	n = rb_numdiff_make_n(prec);
	la = one; lb = rb_funcall1(one, '+', rb_funcall1(x, '-', a)); // Laguerreの多項式
	// w = exp(a * log(x, prec) - x - loggamma_a, n);
	w = rb_funcall1(a, '*', rb_bigmath_log(x, prec));
	w = rb_funcall1(w, '-', x);
	w = rb_funcall1(w, '-', loggamma_a);
	w = rb_bigmath_exp(w, prec);
	result = rb_funcall1(w, '/', lb);
	big_k = two;
	for (int k = 2; k <= 1000; k++)
	{
		// temp = ((k - one - a) * (lb - la) + (k + x) * lb).div(k, n);
		temp = rb_funcall1(k, '-', rb_funcall1(one, '-', a));
		temp = rb_funcall1(temp, '*', rb_funcall1(lb, '-', la));
		temp = rb_funcall1(temp, '+', rb_funcall1(rb_funcall1(k, '+', x), '*', lb));
		temp = rb_funcall(temp, div, 2, big_k, n);

		la = lb; lb = temp;
		// w *= (k - one - a) / k;
		temp = rb_funcall1(rb_funcall1(big_k, '-', one), '-', a);
		w = rb_funcall1(w, '*', rb_funcall1(temp, '/', big_k));

		// temp = w / (la * lb);
		temp = rb_funcall1(w, '/', rb_funcall1(la, '*', lb));

		previous = result; result = rb_funcall(result, add, 2, temp, n);
		if (rb_num_equal_p(result, previous))
			goto retval;
		big_k = rb_funcall1(big_k, '+', one);
	}
	rb_warn("gammar_q(): can't converge.");
retval:
	RB_GC_GUARD(a);
	RB_GC_GUARD(x);
	RB_GC_GUARD(loggamma_a);
	RB_GC_GUARD(one);
	RB_GC_GUARD(two);
	RB_GC_GUARD(big_k);
	RB_GC_GUARD(la);
	RB_GC_GUARD(lb);
	RB_GC_GUARD(w);
	RB_GC_GUARD(result);
	RB_GC_GUARD(temp);
	RB_GC_GUARD(previous);
	return result;
}

// TODO: -1 <= x <= 1 以外はエラーが出る: `erf': undefined method `-' for nil (NoMethodError)
VALUE
erf_gammar(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE half = rb_BigDecimal1(rb_str_new_cstr("0.5"));
	VALUE two = rb_BigDecimal1(INT2FIX(2));
	VALUE log_pi_2 = rb_funcall(
		rb_bigmath_const_log_pi(prec), div, 2, two, prec);
	VALUE y = gammar_p(half, rb_funcall1(x, '*', x), log_pi_2, prec);
	if (rb_num_negative_p(x))  y = rb_num_uminus(y);
	return rb_num_round(y, prec);
}

VALUE
erf_branch(VALUE x, VALUE prec, bigmath_func1 erf_cb)
{
	VALUE y = Qundef;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (erf_cb == NULL)
		return BIG_NAN;
	if (!rb_num_finite_p(x))
	{
		if (rb_num_nan_p(x))
			y = BIG_NAN;
		else
		{
			switch (rb_num_infinite_p(x)) {
			case -1:
				y = BIG_MINUS_ONE;
				break;
			case 1:
				y = BIG_ONE;
				break;
			}
		}
	}
	if (y == Qundef)
		y = erf_cb(x, prec);
	return y;
}

// TODO: -1 <= x <= 1 以外はエラーが出る: `erf': undefined method `-' for nil (NoMethodError)
VALUE
erfc_gammar(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE half = rb_BigDecimal1(rb_str_new_cstr("0.5"));
	VALUE two = rb_BigDecimal1(INT2FIX(2));
	VALUE log_pi_2 = rb_funcall(
		rb_bigmath_const_log_pi(prec), div, 2, two, prec);
	VALUE y;
	if (!rb_num_negative_p(x))
		y = gammar_q(half, rb_funcall1(x, '*', x), log_pi_2, prec);
	else
	{
		y = gammar_p(half, rb_funcall1(x, '*', x), log_pi_2, prec);
		y = rb_funcall1(BIG_ONE, '+', y);
	}
	return rb_num_round(y, prec);
}

VALUE
erfc_branch(VALUE x, VALUE prec, bigmath_func1 erfc_cb)
{
	VALUE y = Qundef;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (erfc_cb == NULL)
		return BIG_NAN;
	if (!rb_num_finite_p(x))
	{
		if (rb_num_nan_p(x))
			y = BIG_NAN;
		else
		{
			switch (rb_num_infinite_p(x)) {
			case -1:
				y = rb_BigDecimal1(INT2FIX(2));
				break;
			case 1:
				y = BIG_ZERO;
				break;
			}
		}
	}
	if (y == Qundef)
		y = erfc_cb(x, prec);
	return y;
}




static VALUE
__impl_gammabeta_erf(VALUE unused_obj, VALUE x, VALUE prec)
{
	return erf_branch(x, prec, erf_gammar);
}


static VALUE
__impl_gammabeta_erfc(VALUE unused_obj, VALUE x, VALUE prec)
{
	return erfc_branch(x, prec, erfc_gammar);
}


// TODO: eps-16の誤差がある。
// |erf(1) - 0.84270079294971474562456763838456194738845892814039e0|
// 結果: 1.237166529966980473119076080698259... × 10^-16
// |erfc(1) - 0.15729920705028525437543236161543805261154107185961e0|
// 結果: 1.2371665299669804731190760806982591... × 10^-16

#endif

void
InitVM_GammaBeta(void)
{
#if 0
	rb_define_module_function(rb_mGammaR, "erf", __impl_gammabeta_erf, 2);
	rb_define_module_function(rb_mGammaR, "erfc", __impl_gammabeta_erfc, 2);
#endif
}
