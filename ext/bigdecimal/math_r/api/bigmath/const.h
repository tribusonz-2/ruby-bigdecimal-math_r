static VALUE
init_prec(VALUE prec)
{
	const ID double_fig = rb_intern("double_fig");
	VALUE fig, retval = Qnil;

	rb_check_precise(prec);

	fig = rb_funcall(rb_cBigDecimal, double_fig, 0);

	switch (NUM2INT(rb_dbl_cmp(NUM2DBL(prec), NUM2DBL(fig)))) {
	case -1:
		retval = fig;
		break;
	case 0:
	case 1:
		retval = prec;
	}

	return retval;
}

VALUE
rb_bigmath_const(const char *gv, VALUE (*func)(VALUE prec), VALUE prec)
{
	static long def_prec = DEF_PREC;
	VALUE x;

	x = rb_gv_get(gv);
	prec = init_prec(prec);
	if (def_prec < NUM2LONG(prec) || NIL_P(x))
	{
		if (def_prec < NUM2LONG(prec))
			def_prec = NUM2LONG(prec);
		x = func(LONG2FIX(def_prec));
		rb_gv_set(gv, x);
	}
        return rb_num_round(x, prec);
}
