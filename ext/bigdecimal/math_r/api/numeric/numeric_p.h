bool
rb_num_numeric_p(VALUE self)
{
	return rb_class_superclass(CLASS_OF(self)) == rb_cNumeric;
}
