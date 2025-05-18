VALUE
rb_bigmath_hypot(VALUE a, VALUE b, VALUE prec)
{
	if (rb_num_zero_p(rb_num_imag(a)) &&
	    rb_num_zero_p(rb_num_imag(b)))
		return hypot_branch(a, b, prec, hypot_mmm);
	else
		return hypot_branch(a, b, prec, hypot_l2norm);
}

