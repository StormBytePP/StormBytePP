#include <StormByte/system/process.hxx>
#include <StormByte/system/worker.hxx>

using namespace StormByte::System;

Worker::Worker(std::unique_ptr<Process>&& exec):m_executable(std::move(exec)) {}