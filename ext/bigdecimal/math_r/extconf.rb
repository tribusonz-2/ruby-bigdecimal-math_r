# frozen_string_literal: true

require 'mkmf'

class CCoder
  def self.declare_func(retval_type, funcname, args)
    ary = args.map{|(arg, type)| [type, arg].join(" ")}.join(", ")
    "%s %s(%s);" % [retval_type, funcname, ary]
  end
end

ARG1 = {"x"=>"VALUE", "prec"=>"VALUE"}
ARG2 = {"x"=>"VALUE", "y"=>"VALUE", "prec"=>"VALUE"}
ARG2SCALAR2 = {"x"=>"VALUE", "y"=>"VALUE", "prec"=>"VALUE", "*a"=>"VALUE", "*b"=>"VALUE"}
ARG_RCM = {"x"=>"VALUE", "*reso"=>"VALUE"}

VALUE = "VALUE"
VOID = "void"

MATHFUNCS = {
  "exp" => [VALUE, ARG1],
  "exp2" => [VALUE, ARG1],
  "expxt" => [VALUE, ARG2],
  "log" => [VALUE, ARG1],
  "log2" => [VALUE, ARG1],
  "log10" => [VALUE, ARG1],
  "logxt" => [VALUE, ARG2],
  "rcm2" => [VALUE, ARG_RCM], "rcm10" => [VALUE, ARG_RCM],
  "atan" => [VALUE, ARG1],
  "sqrt" => [VALUE, ARG1], "csqrt" => [VALUE, ARG1],
  "cuberoot" => [VALUE, ARG1], "ccbrt" => [VALUE, ARG1],
  "pow" => [VALUE, ARG2], "cpow" => [VALUE, ARG2], "ipow" => [VALUE, ARG2],
  "escalb" => [VOID, ARG2SCALAR2],
  "cabs" => [VALUE, ARG1],
  "carg" => [VALUE, ARG1],
  "l2norm" => [VALUE, ARG1],
  "quadrant" => [VALUE, ARG2]
}

CB_TYPE = {
  "log" => "bigmath_func1",
  "sqrt" => "bigmath_func1",
  "atan" => "bigmath_func1"
}

API_H = 'api.h'
DECL_H = "decl.h"
ALGOFUNC_H = 'algofunc.h'

MATHFUNC_DIR_PATH = "internal/algo/bigmath/*/**/*.h"
BRANCH_DIR_PATH = "internal/algo/branch/*/**/*.h"
API_DIR_PATH = "api/*/**/*.h"

DECL_INCLG = "BIGMATH_MATHFUNC_H"

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
    IO.write(header_filename, header_str)
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
          header_str << CCoder.declare_func(retval_type, "#{mathfunc}_#{algo}", args)
          header_str << "\n"
        else
          raise "The function name is not in the list: #{mathfunc}"
        end
      end
    end
    header_str << "\n"
    header_str << "#endif /* #{DECL_INCLG} */"
    IO.write(header_filename, header_str)
  end
end


update_header("BIGMATH_ALGOFUNC_H", ALGOFUNC_H, MATHFUNC_DIR_PATH)
update_header("BIGMATH_API_H", API_H, API_DIR_PATH)
update_decl_mathfunc_header

create_makefile('bigdecimal/math_r/math_r')
