# Change Log


All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/) and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Changed
- `atan_branch()` limit a calculation range in $0 \lt x \lt \frac{1}{2}$ .

### Fixed
- `cpow_formula()` return complex solution when left hand side is in negative real number.
- `acsch_branch()` had a domain.

### Added
- Add API `rb_num_domain_p()`. This query whether an argument is in the domain.

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
