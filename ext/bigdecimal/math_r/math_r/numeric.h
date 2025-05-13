#ifndef INTERNAL_API_NUMERIC
#define INTERNAL_API_NUMERIC

/* API for Numeric */

VALUE rb_num_abs(VALUE x);

VALUE rb_num_uminus(VALUE x);

VALUE rb_num_real(VALUE z);
VALUE rb_num_imag(VALUE z);

bool rb_num_positive_p(VALUE z);
bool rb_num_negative_p(VALUE z);

bool rb_num_equal_p(VALUE lhs, VALUE rhs);
bool rb_num_notequal_p(VALUE lhs, VALUE rhs);
VALUE rb_num_cmpeql(VALUE lhs, VALUE rhs);

bool rb_num_zero_p(VALUE z);
bool rb_num_nonzero_p(VALUE z);
bool rb_num_real_p(VALUE z);
bool rb_num_finite_p(VALUE z);
int rb_num_infinite_p(VALUE z);
bool rb_num_nan_p(VALUE z);

bool rb_num_numeric_p(VALUE self);


/**
 * Rounds the argument +x+ to an arbitrary precision +prec+. <br>
 * It targets real numbers, but also supports Complex class. <br>
 * 
 */
VALUE rb_num_round(VALUE x, VALUE prec);

#define ARG_REAL        false
#define ARG_COMPLEX     true
#define ARG_RAWVALUE    false
#define ARG_RECIPROCAL  true

VALUE 
rb_num_canonicalize(VALUE x, VALUE prec, bool complex_form, bool inversion);

#define SIGN_PLUS false
#define SIGN_MINUS true

/**
 *  ```Ruby
 *  def rb_ImaginaryZ(z, signbit)
 *    if signbit
 *      -Complex::I * z
 *    else
 *       Complex::I * z
 *    end
 *  end
 *  ```
 */
VALUE rb_ImaginaryZ(VALUE z, bool signbit);

#define rb_funcall1(lhs, ops, rhs)  rb_funcall((lhs), (ops), 1, (rhs))

#endif /* INTERNAL_API_NUMERIC */
