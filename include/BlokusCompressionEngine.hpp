#pragma once

/* =========================================================
 *
 * BlokusCompressionEngine.hpp
 * 
 * Concrete implementation for compressing/decompressing data
 * 
 * ========================================================= */

#include "ICompress.hpp"
#include "IDecompress.hpp"

class BlokusCompressionEngine : public ICompress, public IDecompress
{
    public:
        BlokusCompressionEngine();
        ~BlokusCompressionEngine();

        void Compress(std::string& input, std::string& output);
        void Decompress(std::string& input, std::string& output);

    private:
};