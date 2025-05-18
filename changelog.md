# Change Log


All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/) and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

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
