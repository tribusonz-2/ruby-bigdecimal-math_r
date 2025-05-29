# frozen_string_literal: true

require_relative "lib/bigdecimal/math_r/version"

Gem::Specification.new do |spec|
  spec.name = "bigdecimal-math_r"
  spec.version = BigMathR::VERSION
  spec.authors = ["tribusonz-2"]
  spec.email = ["xwisepp62543@gmail.com"]

  spec.summary = "Refined Math for BigDecimal"
  spec.description = "It provides a math module for multiple-precision arithmetic."
  spec.homepage = "https://github.com/tribusonz-2/ruby-bigdecimal-math_r"
  spec.license = "MIT"
  spec.required_ruby_version = ">= 3.1.0"

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = spec.homepage
  spec.metadata["changelog_uri"] = "https://github.com/tribusonz-2/ruby-bigdecimal-math_r"

  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been added into git.
  gemspec = File.basename(__FILE__)
  spec.files = IO.popen(%w[git ls-files -z], chdir: __dir__, err: IO::NULL) do |ls|
    ls.readlines("\x0", chomp: true).reject do |f|
      (f == gemspec) ||
        f.start_with?(*%w[bin/ test/ spec/ features/ .git .github appveyor Gemfile])
    end
  end
  spec.bindir = "exe"
  spec.executables = spec.files.grep(%r{\Aexe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.extensions = %w{ext/bigdecimal/math_r/extconf.rb}

  spec.add_development_dependency "bundler"
  spec.add_development_dependency "rake", "~> 13.0"
  spec.add_development_dependency "rake-compiler"

  # For more information and examples about making a new gem, check out our
  # guide at: https://bundler.io/guides/creating_gem.html
end
