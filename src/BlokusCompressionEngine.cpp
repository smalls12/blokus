#include "BlokusCompressionEngine.hpp"

#include "snappy.h"

#include "spdlog/spdlog.h"

BlokusCompressionEngine::BlokusCompressionEngine()
{
    spdlog::get("console")->debug("BlokusCompressionEngine::BlokusCompressionEngine()");
}

BlokusCompressionEngine::~BlokusCompressionEngine()
{
    spdlog::get("console")->debug("BlokusCompressionEngine::~BlokusCompressionEngine()");
}

void BlokusCompressionEngine::Compress(std::string& input, std::string& output)
{
    snappy::Compress(input.data(), input.size(), &output);
    spdlog::get("console")->debug("BlokusCompressionEngine::Compress() - {} to {}", input.size(), output.size());
}

void BlokusCompressionEngine::Decompress(std::string& input, std::string& output)
{
    snappy::Uncompress(input.data(), input.size(), &output);
    spdlog::get("console")->debug("BlokusCompressionEngine::Decompress() - {} to {}", input.size(), output.size());
}