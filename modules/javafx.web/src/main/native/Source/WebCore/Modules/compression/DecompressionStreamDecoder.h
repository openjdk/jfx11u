/*
 * Copyright (C) 2022 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "BufferSource.h"
#include "ExceptionOr.h"
#include "Formats.h"
#include <JavaScriptCore/Forward.h>
#include <wtf/RefCounted.h>
#include <wtf/RefPtr.h>
#if !PLATFORM(JAVA)
#include <zlib.h>
#endif

namespace WebCore {

class DecompressionStreamDecoder : public RefCounted<DecompressionStreamDecoder> {
public:
    static Ref<DecompressionStreamDecoder> create(unsigned char format)
    {
        return adoptRef(*new DecompressionStreamDecoder(format));
    }

    ExceptionOr<RefPtr<Uint8Array>> decode(const BufferSource&&);
    ExceptionOr<RefPtr<Uint8Array>> flush();

    ~DecompressionStreamDecoder()
    {
/* removing zlib dependency , as newly added module compression requires zlib */
#if !PLATFORM(JAVA)
        if (initailized)
            deflateEnd(&zstream);
#endif
    }

private:

    // When given an encoded input, it is difficult to guess the output size.
    // My approach here is starting from one page and growing at a linear rate of x2 until the input data
    // has been fully processed. To ensure the user's memory is not completely consumed, I am setting a cap
    // of 1GB per allocation. This strategy enables very fast memory allocation growth without needing to perform
    // unnecessarily large allocations upfront.
    const size_t startingAllocationSize = 16384; // 16KB
    const size_t maxAllocationSize = 1073741824; // 1GB

    bool initailized { false };
    bool finish { false };
    #if !PLATFORM(JAVA)
    z_stream zstream;
    #endif

    Formats::CompressionFormat m_format;

    ExceptionOr<Vector<uint8_t>> decompress(const uint8_t* input, const size_t inputLength);
    ExceptionOr<bool> initialize();

    explicit DecompressionStreamDecoder(unsigned char format)
        : m_format(static_cast<Formats::CompressionFormat>(format))
    {
    }
};
} // namespace WebCore
