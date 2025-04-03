# frozen_string_literal: true

require 'mkmf'

MATHFUNCS = {
  "atan" => 1,
  "sqrt" => 1, "csqrt" => 1,
  "cabs" => 1,
  "carg" => 1,
  "l2norm" => 1,
  "quadrant" => 2
}

API_H = 'api.h'
DECL_H = "decl.h"
ALGOFUNC_H = 'algofunc.h'

MATHFUNC_DIR = "internal/algo/bigmath/*/**/*.h"
API_DIR = "api/*/**/*.h"

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
    Dir.glob(MATHFUNC_DIR) do |h|
      if /\w+\/\w+\/\w+\/\w+\/\w+.h/.match?(h)
        /(.+)\/(.+)\/(.+)\/(.+)\/(.+).h/ =~ h
        mathfunc, algo = $4, $5
        if MATHFUNCS.keys.include?(mathfunc)
          case MATHFUNCS[mathfunc]
          when 1
            header_str << "VALUE #{mathfunc}_#{algo}(VALUE, VALUE);\n"
          when 2
            header_str << "VALUE #{mathfunc}_#{algo}(VALUE, VALUE, VALUE);\n"
          end
        end
      end
    end
    header_str << "\n"
    header_str << "#endif /* #{DECL_INCLG} */"
    IO.write(header_filename, header_str)
  end
end


update_header("BIGMATH_ALGOFUNC_H", ALGOFUNC_H, MATHFUNC_DIR)
update_header("BIGMATH_API_H", API_H, API_DIR)
update_decl_mathfunc_header

create_makefile('bigdecimal/math_r/math_r')
