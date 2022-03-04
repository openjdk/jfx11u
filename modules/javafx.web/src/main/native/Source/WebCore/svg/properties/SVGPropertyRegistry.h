/*
 * Copyright (C) 2018-2019 Apple Inc.  All rights reserved.
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
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "SVGAttributeAnimator.h"

namespace WebCore {

class SVGAnimatedProperty;

class SVGPropertyRegistry {
public:
    SVGPropertyRegistry() = default;
    virtual ~SVGPropertyRegistry() = default;

    virtual void detachAllProperties() const = 0;
    virtual QualifiedName propertyAttributeName(const SVGProperty&) const = 0;
    virtual QualifiedName animatedPropertyAttributeName(const SVGAnimatedProperty&) const = 0;
    virtual void setAnimatedPropertyDirty(const QualifiedName&, SVGAnimatedProperty&) const = 0;
    virtual std::optional<String> synchronize(const QualifiedName&) const = 0;
    virtual HashMap<QualifiedName, String> synchronizeAllAttributes() const = 0;

    virtual bool isAnimatedPropertyAttribute(const QualifiedName&) const = 0;
    virtual bool isAnimatedStylePropertyAttribute(const QualifiedName&) const = 0;
    virtual RefPtr<SVGAttributeAnimator> createAnimator(const QualifiedName&, AnimationMode, CalcMode, bool isAccumulated, bool isAdditive) const = 0;
    virtual void appendAnimatedInstance(const QualifiedName& attributeName, SVGAttributeAnimator&) const = 0;
};

}
