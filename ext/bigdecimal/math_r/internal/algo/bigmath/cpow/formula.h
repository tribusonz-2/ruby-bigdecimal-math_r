VALUE
cpow_formula(VALUE z, VALUE w, VALUE prec)
{
	VALUE a = Qundef, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	if (rb_num_positive_p(rb_num_real(z)) &&
	    rb_num_zero_p(rb_num_imag(z)) && rb_num_zero_p(rb_num_imag(w)))
	{
		a = pow_formula(rb_num_real(z), rb_num_real(w), n);
		a = rb_num_canonicalize(a, n, ARG_COMPLEX, ARG_RAWVALUE);
	}
	else
	{
		a = rb_bigmath_clog(z, n);
		a = rb_funcall1(w, '*', a);
		a = rb_bigmath_cexp(a, n);
	}
	return rb_num_round(a, prec);
}
