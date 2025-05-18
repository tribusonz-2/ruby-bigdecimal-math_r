VALUE
rb_ImaginaryZ(VALUE z, bool signbit)
{
	VALUE real, imag;
	real = signbit ? rb_num_imag(z) : rb_num_uminus(rb_num_imag(z));
	imag = signbit ? rb_num_uminus(rb_num_real(z)) : rb_num_real(z);
	return rb_Complex(real, imag);
}
