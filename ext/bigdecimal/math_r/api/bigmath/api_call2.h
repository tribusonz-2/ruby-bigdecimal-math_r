VALUE 
rb_bigmath_api_call2(VALUE x, VALUE y, VALUE prec, bigmath_func2 func_ptr)
{
	return func_ptr(x, y, prec);
}

