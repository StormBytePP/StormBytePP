#include <StormByte/system/executable.hxx>
#include <StormByte/system/worker.hxx>

using namespace StormByte::System;

Worker::Worker(std::unique_ptr<Executable>&& exec):m_executable(std::move(exec)) {}