# frozen_string_literal: true

require 'mkmf'

ARG1 = {"x"=>"VALUE", "prec"=>"VALUE"}
ARG2 = {"x"=>"VALUE", "y"=>"VALUE", "prec"=>"VALUE"}
ARG1SCALAR2 = {"x"=>"VALUE", "prec"=>"VALUE", "*a"=>"VALUE", "*b"=>"VALUE"}
ARG2SCALAR2 = {"x"=>"VALUE", "y"=>"VALUE", "prec"=>"VALUE", "*a"=>"VALUE", "*b"=>"VALUE"}
ARG_RCM = {"x"=>"VALUE", "*reso"=>"VALUE"}
ARG_TRIG = {"func"=>"ID", "theta"=>"VALUE", "prec"=>"VALUE"}
ARG_PREC = {"prec"=>"VALUE"}

VALUE = "VALUE"
VOID = "void"

MATHFUNCS = {
  "exp" => [VALUE, ARG1], "cexp" => [VALUE, ARG1],
  "exp2" => [VALUE, ARG1], "cexp2" => [VALUE, ARG1],
  "expm1" => [VALUE, ARG1], "cexpm1" => [VALUE, ARG1],
  "expxt" => [VALUE, ARG2],
  "log" => [VALUE, ARG1], "clog" => [VALUE, ARG1], 
  "log1p" => [VALUE, ARG1], "clog1p" => [VALUE, ARG1], 
  "log2" => [VALUE, ARG1], "clog2" => [VALUE, ARG1],
  "log10" => [VALUE, ARG1], "clog10" => [VALUE, ARG1], 
  "logxt" => [VALUE, ARG2],
  "rcm2" => [VALUE, ARG_RCM], "rcm10" => [VALUE, ARG_RCM],
  "sincos" => [VOID, ARG1SCALAR2],
  "sin" => [VALUE, ARG1],  "csin" => [VALUE, ARG1], 
  "cos" => [VALUE, ARG1],  "ccos" => [VALUE, ARG1],
  "tan" => [VALUE, ARG1],  "ctan" => [VALUE, ARG1],
  "csc" => [VALUE, ARG1],  "ccsc" => [VALUE, ARG1],
  "sec" => [VALUE, ARG1],  "csec" => [VALUE, ARG1],
  "cot" => [VALUE, ARG1],  "ccot" => [VALUE, ARG1],
  "sinhcosh" => [VOID, ARG1SCALAR2],
  "sinh" => [VALUE, ARG1],  "csinh" => [VALUE, ARG1], 
  "cosh" => [VALUE, ARG1],  "ccosh" => [VALUE, ARG1],
  "tanh" => [VALUE, ARG1],  "ctanh" => [VALUE, ARG1],
  "csch" => [VALUE, ARG1],  "ccsch" => [VALUE, ARG1],
  "sech" => [VALUE, ARG1],  "csech" => [VALUE, ARG1],
  "coth" => [VALUE, ARG1],  "ccoth" => [VALUE, ARG1],
  "asin" => [VALUE, ARG1],  "casin" => [VALUE, ARG1],
  "acos" => [VALUE, ARG1],  "cacos" => [VALUE, ARG1],
  "atan" => [VALUE, ARG1],  "catan" => [VALUE, ARG1],
  "acsc" => [VALUE, ARG1],  "cacsc" => [VALUE, ARG1],
  "asec" => [VALUE, ARG1],  "casec" => [VALUE, ARG1],
  "acot" => [VALUE, ARG1],  "cacot" => [VALUE, ARG1],
  "asinh" => [VALUE, ARG1],  "casinh" => [VALUE, ARG1],
  "acosh" => [VALUE, ARG1],  "cacosh" => [VALUE, ARG1],
  "atanh" => [VALUE, ARG1],  "catanh" => [VALUE, ARG1],
  "acsch" => [VALUE, ARG1],  "cacsch" => [VALUE, ARG1],
  "asech" => [VALUE, ARG1],  "casech" => [VALUE, ARG1],
  "acoth" => [VALUE, ARG1],  "cacoth" => [VALUE, ARG1],
  "trig" => [VALUE, ARG_TRIG],
  "hypot" => [VALUE, ARG2],
  "sqrt" => [VALUE, ARG1], "csqrt" => [VALUE, ARG1],
  "cuberoot" => [VALUE, ARG1], "ccbrt" => [VALUE, ARG1],
  "pow" => [VALUE, ARG2], "cpow" => [VALUE, ARG2], "ipow" => [VALUE, ARG2],
  "escalb" => [VOID, ARG2SCALAR2],
  "cabs" => [VALUE, ARG1],
  "carg" => [VALUE, ARG1],
  "l2norm" => [VALUE, ARG1],
  "quadrant" => [VALUE, ARG2],
  "erf" => [VALUE, ARG1],
  "erfc" => [VALUE, ARG1],
  "f_euler" => [VALUE, ARG1],
  "PI"=>[VALUE, ARG_PREC],
  "E"=>[VALUE, ARG_PREC],
  "EulerGamma"=>[VALUE, ARG_PREC],
  "LOG2"=>[VALUE, ARG_PREC],
  "LOG10"=>[VALUE, ARG_PREC],
  "LOG_PI"=>[VALUE, ARG_PREC],
  "SQRT2"=>[VALUE, ARG_PREC],
  "SQRT3"=>[VALUE, ARG_PREC]
}

CB_TYPE = {
  "exp" => "bigmath_func1", "cexp" => "bigmath_func1",
  "exp2" => "bigmath_func1", "cexp2" => "bigmath_func1",
  "expm1" => "bigmath_func1", "cexpm1" => "bigmath_func1",
  "log" => "bigmath_func1", "clog" => "bigmath_func1",
  "log2" => "bigmath_func1", "clog2" => "bigmath_func1",
  "log10" => "bigmath_func1", "clog10" => "bigmath_func1",
  "log1p" => "bigmath_func1", "clog1p" => "bigmath_func1",
  "sqrt" => "bigmath_func1", "csqrt" => "bigmath_func1",
  "cuberoot" => "bigmath_func1", "ccbrt" => "bigmath_func1",
  "sin" => "bigmath_func1", "csin" => "bigmath_func1",
  "cos" => "bigmath_func1", "ccos" => "bigmath_func1",
  "tan" => "bigmath_func1", "ctan" => "bigmath_func1",
  "csc" => "bigmath_func1", "ccsc" => "bigmath_func1",
  "sec" => "bigmath_func1", "csec" => "bigmath_func1",
  "cot" => "bigmath_func1", "ccot" => "bigmath_func1",
  "sinh" => "bigmath_func1", "csinh" => "bigmath_func1",
  "cosh" => "bigmath_func1", "ccosh" => "bigmath_func1",
  "tanh" => "bigmath_func1", "ctanh" => "bigmath_func1",
  "csch" => "bigmath_func1", "ccsch" => "bigmath_func1",
  "sech" => "bigmath_func1", "csech" => "bigmath_func1",
  "coth" => "bigmath_func1", "ccoth" => "bigmath_func1",
  "asin" => "bigmath_func1", "casin" => "bigmath_func1",
  "acos" => "bigmath_func1", "cacos" => "bigmath_func1",
  "atan" => "bigmath_func1", "catan" => "bigmath_func1",
  "acsc" => "bigmath_func1", "cacsc" => "bigmath_func1",
  "asec" => "bigmath_func1", "casec" => "bigmath_func1",
  "acot" => "bigmath_func1", "cacot" => "bigmath_func1",
  "asinh" => "bigmath_func1", "casinh" => "bigmath_func1",
  "acosh" => "bigmath_func1", "cacosh" => "bigmath_func1",
  "atanh" => "bigmath_func1", "catanh" => "bigmath_func1",
  "acsch" => "bigmath_func1", "cacsch" => "bigmath_func1",
  "asech" => "bigmath_func1", "casech" => "bigmath_func1",
  "acoth" => "bigmath_func1", "cacoth" => "bigmath_func1",
  "hypot" => "bigmath_func2",
  "erf" => "bigmath_func1",
  "erfc" => "bigmath_func1"
}

API_H = 'api.h'
DECL_H = "decl.h"
ALGOFUNC_H = 'algofunc.h'

MATHFUNC_DIR_PATH = "internal/algo/bigmath/*/**/*.h"
BRANCH_DIR_PATH = "internal/algo/branch/*/**/*.h"
API_DIR_PATH = "api/*/**/*.h"

DECL_INCLG = "BIGMATH_MATHFUNC_H"

def declare_func(retval_type, funcname, args)
  ary = args.map{|(arg, type)| [type, arg].join(" ")}.join(", ")
  "%s %s(%s);" % [retval_type, funcname, ary]
end

def cfile_writer(filename, str)
  f = IO.read(filename)
  if f != str
    IO.write(filename, str)
  end
end

def update_header(include_guard, header_filename, target_dir)
  header_str = String.new
  Dir.chdir(__dir__) do
    header_str << "#ifndef #{include_guard}\n"
    header_str << "#define #{include_guard}\n"
    header_str << "\n"
    Dir.glob(target_dir) do |h|
      header_str << "#include \"#{h}\"\n"
    end
    header_str << "\n"
    header_str << "#endif /* #{include_guard} */\n"
    cfile_writer(header_filename, header_str)
  end
end

def update_decl_mathfunc_header
  header_filename = DECL_H
  header_str = String.new
  Dir.chdir(__dir__) do
    header_str << "#ifndef #{DECL_INCLG}\n"
    header_str << "#define #{DECL_INCLG}\n"
    header_str << "\n"
    Dir.glob(MATHFUNC_DIR_PATH) do |h|
      if /\w+\/\w+\/\w+\/\w+\/\w+.h/.match?(h)
        /(.+)\/(.+)\/(.+)\/(.+)\/(.+).h/ =~ h
        mathfunc, algo = $4, $5
        if MATHFUNCS.keys.include?(mathfunc)
          retval_type, args = MATHFUNCS[mathfunc]
          if algo == "branch"
            if CB_TYPE.keys.include?(mathfunc)
              args = args.merge({"cb" => CB_TYPE[mathfunc]})
            else
              raise "The callback function name is not in the list: #{mathfunc}"
            end
          end
          header_str << declare_func(retval_type, "#{mathfunc}_#{algo}", args)
          header_str << "\n"
        else
          raise "The function name is not in the list: #{mathfunc}"
        end
      end
    end
    header_str << "\n"
    header_str << "#endif /* #{DECL_INCLG} */"
    cfile_writer(header_filename, header_str)
  end
end

update_header("BIGMATH_ALGOFUNC_H", ALGOFUNC_H, MATHFUNC_DIR_PATH)
update_header("BIGMATH_API_H", API_H, API_DIR_PATH)
update_decl_mathfunc_header

create_makefile('bigdecimal/math_r/math_r')
