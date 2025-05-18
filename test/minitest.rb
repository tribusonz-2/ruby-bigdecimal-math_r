  PREC = 20
  # Quadrant XY in non-finites
  # For 0-deg
  ComplexPlane.quadrant(-1.0, BigDecimal::INFINITY, PREC)   #=> -0.0
  ComplexPlane.quadrant(1.0, BigDecimal::INFINITY, PREC)  #=> 0.0
  ComplexPlane.quadrant(-0.0, BigDecimal::INFINITY, PREC) #=> -0.0
  ComplexPlane.quadrant(BigDecimal('-0'), BigDecimal::INFINITY, PREC) #=> -0.0
  ComplexPlane.quadrant(0.0, BigDecimal::INFINITY, PREC) #=> 0.0
  ComplexPlane.quadrant(BigDecimal('0'), BigDecimal::INFINITY, PREC) #=> 0.0
  # For 45-Deg
  ComplexPlane.quadrant(BigDecimal::INFINITY, BigDecimal::INFINITY, PREC) #=> 0.78539816339744830962e0
  # For 90-Deg
  ComplexPlane.quadrant(BigDecimal::INFINITY, 0.0, PREC) #=> 0.15707963267948966192e1
  # For 135-Deg
  ComplexPlane.quadrant(BigDecimal::INFINITY, -BigDecimal::INFINITY, PREC) #=> -0.78539816339744830962e0
  # For 180-deg
  ComplexPlane.quadrant(-1.0, -BigDecimal::INFINITY, PREC) #=> -0.31415926535897932385e1
  ComplexPlane.quadrant(1.0, -BigDecimal::INFINITY, PREC) #=> 0.31415926535897932385e1
  ComplexPlane.quadrant(-0.0, -BigDecimal::INFINITY, PREC) #=0> -0.31415926535897932385e1
  ComplexPlane.quadrant(BigDecimal('-0'), -BigDecimal::INFINITY, PREC) #=> -0.31415926535897932385e1
  ComplexPlane.quadrant(0.0, -BigDecimal::INFINITY, PREC) #=> 0.31415926535897932385e1
  ComplexPlane.quadrant(BigDecimal('0'), -BigDecimal::INFINITY, PREC) #=> 0.31415926535897932385e1
  # For 225-Deg
  ComplexPlane.quadrant(-BigDecimal::INFINITY, -BigDecimal::INFINITY, PREC) #=> -0.23561944901923449288e1
  # For 270-Deg
  ComplexPlane.quadrant(-BigDecimal::INFINITY, 0.0, PREC) #=> -0.15707963267948966192e1
  # For 315-Deg
  ComplexPlane.quadrant(-BigDecimal::INFINITY, BigDecimal::INFINITY, PREC) #=> 0.23561944901923449288e1

  # Quadrant XY in the complex argument
  ComplexPlane.quadrant(0.0, 0.0, PREC) #=> 0.0
  ComplexPlane.quadrant(0.0, -0.0, PREC) #=> -0.0
  ComplexPlane.quadrant(-0.0, -0.0, PREC) #=> -0.31415926535897932385e1
  ComplexPlane.quadrant(-0.0, 0.0, PREC) #=> 0.31415926535897932385e1
  ComplexPlane.quadrant(0.0, rand(), PREC) #=> 0.15707963267948966192e1
  ComplexPlane.quadrant(0.0, -rand(), PREC) #=> -0.15707963267948966192e1

  # Quadrant XY diagonals
  # For imaginary
  ComplexPlane.quadrant(1i, 1i, PREC) #=> 0.78539816339744830962e0
  ComplexPlane.quadrant(1i, -1i, PREC) #=> -0.78539816339744830962e0
  ComplexPlane.quadrant(-1i, -1i, PREC) #=> -0.23561944901923449288e1
  ComplexPlane.quadrant(-1i, 1i, PREC) #=> 0.23561944901923449288e1

  # For same values
  ComplexPlane.quadrant(1+1i, 1+1i, PREC) #=> (0.78539816339744830962e0+0i)
  ComplexPlane.quadrant(-1+1i, -1+1i, PREC) #=> (-0.23561944901923449288e1+0i)

  # For Different signed the same values
  ComplexPlane.quadrant(1-1i, -1+1i, PREC) #=> (-0.78539816339744830962e0+0i)
  ComplexPlane.quadrant(-1+1i, 1-1i, PREC) #=> (0.23561944901923449288e1+0i)

