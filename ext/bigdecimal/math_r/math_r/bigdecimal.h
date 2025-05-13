#ifndef INTERNAL_API_BIGDECIMAL
#define INTERNAL_API_BIGDECIMAL

/* API for BigDecimal */
void rb_check_precise(VALUE prec);

VALUE rb_big_zero(void);
#define BIG_ZERO rb_big_zero()
VALUE rb_big_minus_zero(void);
#define BIG_MINUS_ZERO rb_big_minus_zero()

VALUE rb_big_one(void);
#define BIG_ONE rb_big_one()
VALUE rb_big_minus_one(void);
#define BIG_MINUS_ONE rb_big_minus_one()

VALUE rb_big_infinity(void);
#define BIG_INF rb_big_infinity()
VALUE rb_big_minus_infinity(void);
#define BIG_MINUS_INF rb_big_minus_infinity()

VALUE rb_big_nan(void);
#define BIG_NAN rb_big_nan()

VALUE rb_BigDecimal(VALUE x, VALUE prec);
VALUE rb_BigDecimal1(VALUE x);
VALUE rb_BigDecimal_flo(VALUE x);
VALUE rb_BigDecimal_sign(VALUE d);

#endif /* INTERNAL_API_BIGDECIMAL */
