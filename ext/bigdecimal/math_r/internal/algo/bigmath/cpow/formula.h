VALUE
cpow_formula(VALUE z, VALUE w, VALUE prec)
{
	VALUE a = Qundef;

	rb_check_precise(prec);

	if (rb_num_positive_p(rb_num_real(z)) &&
	    rb_num_zero_p(rb_num_imag(z)) && rb_num_zero_p(rb_num_imag(w)))
	{
		a = pow_formula(rb_num_real(z), rb_num_real(w), prec);
		a = rb_num_canonicalize(a, prec, ARG_COMPLEX, ARG_RAWVALUE);
	}
	else
	{
		a = rb_bigmath_clog(z, prec);
		a = rb_funcall1(w, '*', a);
		a = rb_bigmath_cexp(a, prec);
	}
	return a;
}
