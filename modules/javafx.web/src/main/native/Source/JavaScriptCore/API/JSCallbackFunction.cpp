/*
 * Copyright (C) 2006-2021 Apple Inc. All rights reserved.
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

#include "config.h"
#include "JSCallbackFunction.h"

#include "APICallbackFunction.h"
#include "JSCInlines.h"

namespace JSC {

STATIC_ASSERT_IS_TRIVIALLY_DESTRUCTIBLE(JSCallbackFunction);

const ClassInfo JSCallbackFunction::s_info = { "CallbackFunction"_s, &InternalFunction::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSCallbackFunction) };

static JSC_DECLARE_HOST_FUNCTION(callJSCallbackFunction);

JSC_DEFINE_HOST_FUNCTION(callJSCallbackFunction, (JSGlobalObject* globalObject, CallFrame* callFrame))
{
    return APICallbackFunction::callImpl<JSCallbackFunction>(globalObject, callFrame);
}

JSCallbackFunction::JSCallbackFunction(VM& vm, Structure* structure, JSObjectCallAsFunctionCallback callback)
    : InternalFunction(vm, structure, callJSCallbackFunction, nullptr)
    , m_callback(callback)
{
}

void JSCallbackFunction::finishCreation(VM& vm, const String& name)
{
    Base::finishCreation(vm, 0, name);
    ASSERT(inherits(info()));
}

JSCallbackFunction* JSCallbackFunction::create(VM& vm, JSGlobalObject* globalObject, JSObjectCallAsFunctionCallback callback, const String& name)
{
    Structure* structure = globalObject->callbackFunctionStructure();
    JSCallbackFunction* function = new (NotNull, allocateCell<JSCallbackFunction>(vm)) JSCallbackFunction(vm, structure, callback);
    function->finishCreation(vm, name);
    return function;
}

} // namespace JSC
