/*
** Copyright (c) 2022 Advanced Micro Devices, Inc. All rights reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
** DEALINGS IN THE SOFTWARE.
*/

#ifndef GFXRECON_DECODE_EXE_INFO_CONSUMER_H
#define GFXRECON_DECODE_EXE_INFO_CONSUMER_H

#include "decode/api_decoder.h"
#include "exe_info_consumer_base.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

class ExeInfoConsumer : public ExeInfoConsumerBase
{
  public:
    ExeInfoConsumer() {}
    const std::string GetAppExeName() const { return exe_info.AppExeName; }
    const uint32_t*   GetAppVersion() const { return exe_info.AppVersion; }
    const char*       GetCompanyName() const { return exe_info.CompanyName; }
    const char*       GetFileDescription() const { return exe_info.FileDescription; }
    const char*       GetFileVersion() const { return exe_info.FileVersion; }
    const char*       GetInternalName() const { return exe_info.InternalName; }
    const char*       GetOriginalFileName() const { return exe_info.OriginalFilename; }
    const char*       GetProductName() const { return exe_info.ProductName; }
    const char*       GetProductVersion() const { return exe_info.ProductVersion; }
    virtual void      Process_ExeFileInfo(gfxrecon::util::filepath::ExeFileInfo& info)
    {
        exe_info        = info;
        found_exe_info_ = true;
    }

    virtual bool IsComplete(uint64_t current_block_index)
    {
        return (current_block_index >= MaxBlockIdx) || (found_exe_info_ == true);
    }

  private:
    static int const                      MaxBlockIdx = 50;
    gfxrecon::util::filepath::ExeFileInfo exe_info    = {};
    bool                                  found_exe_info_{ false };
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_EXE_INFO_CONSUMER_H
