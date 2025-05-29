# frozen_string_literal: true

require "bundler/gem_tasks"
require "minitest/test_task"

Minitest::TestTask.create

require "rake/extensiontask"
Rake::ExtensionTask.new("bigdecimal/math_r") do |ext|
  ext.lib_dir = "lib/bigdecimal/"
end

task default: :task
