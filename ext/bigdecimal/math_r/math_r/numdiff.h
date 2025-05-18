#ifndef INTERNAL_API_NUMDIFF
#define INTERNAL_API_NUMDIFF

/* API for Numerical Differentiation */

/**
 * Query if the condition for exiting the iterator has been reached.
 * It is use in numerical derivatives.
 */
bool rb_numdiff_condition_p(VALUE y, VALUE d, VALUE n, VALUE *m);

/**
 * Add BigDecimal#double_fig to the arbitrary precision number.
 * The precision must be greater than or equal to 1.
 */
VALUE rb_numdiff_make_n(VALUE prec);

#endif /* INTERNAL_API_NUMDIFF */
