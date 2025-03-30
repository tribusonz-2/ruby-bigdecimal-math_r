#ifndef INTERNAL_SOLVER_NUMERIC
#define INTERNAL_SOLVER_NUMERIC

/* API for Numeric */

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

#endif /* INTERNAL_SOLVER_NUMERIC */
