# Change Log


All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/) and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.2.2] - 2025-10-XX

### Changed
- The names of mathematical constants were unified by the discoverer
- Renamed `BigMathR::Const::E.ser` to `BigMathR::Const::E.napier`
- Renamed `BigMathR::GammaR` to `BigMathR::GammaBeta`

### Added
- `BigMathR::Const::E#euler`. Continued fraction type constant $e$ .
- `BigMathR::Const::E#euler_number`. It is an alias of `napier`.
- `BigMathR::Const::EulerGamma#borwein_bailey`. Brent-McMillan type constant $\gamma$ .
- `BigMathR::Const::EulerGamma#brent_mcmillan`. It is an alias of `borwein_bailey`.
- `BigMathR#EulerGamma`.
- Branches for the logarithmic functions.
- `expm1` Function.

## [0.2.1] - 2025-05-XX

### Changed
- `atan_branch()` limit a calculation range in $0 \lt x \lt \frac{1}{2}$ .

### Fixed
- `cpow_formula()` return complex solution when left hand side is in negative real number.
- `acsch_branch()` had a domain.
- `sqrt_branch()` API did not perform an implicit type conversion.
- The global constant was set when the library was loaded.
- `log*_edf()` was not defined in the sub-module `Log`.

### Added
- Add API `rb_num_domain_p()`. This query whether an argument is in the domain.
- Add minitest.

## [0.2.0] - 2025-05-XX

### Changed
- Rename `BigMathR::PowerRoot` to `BigMathR::Power`

### Added
- Add function `BigMathR#sqrt`, `BigMath#cbrt`
- Add module `BigMathR::Erf` with functions of  `#erf_algo911` and `#erfc_algo911`
- Add Power functions `BigMathR::Power.pow`, `BigMathR::Power.cpow`

### Fixed
- `asec_branch()` incorrected a range of domain
- `rb_bigmath_atan()` API was too slow a convergent

## [0.1.0] - 2025-05-XX

### Public release
