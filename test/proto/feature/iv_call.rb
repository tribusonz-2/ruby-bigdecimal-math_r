module MathSolver
  @sinh = Math.method(:sinh)
end

def iv_call1(iv, *args)
  raise ArgumentError, "no include for #{iv}" unless MathSolver.instance_variables.include?(iv)
  meth = MathSolver.instance_variable_get(iv)
  raise TypeError, "variable #{meth} not a Method" unless meth.class == Method
  meth.call(*args) 
end

iv_call1(:@sinh, 1)
#=> 1.1752011936438014
