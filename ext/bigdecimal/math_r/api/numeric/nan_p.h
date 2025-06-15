bool
rb_num_nan_p(VALUE z)
{
	if (rb_num_real_p(z))
		return rb_num_notequal_p(z, z);
	else
		return !rb_num_finite_p(z) && !rb_num_infinite_p(z);
}
