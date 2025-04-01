bool
rb_num_nan_p(VALUE z)
{
	return (!rb_num_finite_p(z) && !rb_num_infinite_p(z));
}
