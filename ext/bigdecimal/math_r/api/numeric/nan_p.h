bool
rb_num_nan_p(VALUE z)
{
	return rb_num_notequal_p(z, z);
}
