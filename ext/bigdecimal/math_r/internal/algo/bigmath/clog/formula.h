VALUE
clog_formula(VALUE z, VALUE prec)
{
	VALUE w;

	w = rb_Complex(
		rb_bigmath_log(rb_bigmath_cabs(z, prec), prec),
		rb_bigmath_carg(z, prec)
	);


	return rb_num_round(w, prec);
}
