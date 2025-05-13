VALUE
rb_bigmath_api_call1(VALUE x, VALUE prec, bigmath_func1 func_ptr)
{
	return func_ptr(x, prec);
}
