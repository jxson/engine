// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SKY_ENGINE_CORE_SCRIPT_DART_INIT_H_
#define SKY_ENGINE_CORE_SCRIPT_DART_INIT_H_

#include "base/callback.h"
#include "dart/runtime/include/dart_api.h"
#include "sky/engine/wtf/OperatingSystem.h"

#include <string>

namespace blink {

#define DART_ALLOW_DYNAMIC_RESOLUTION OS(IOS)

#if DART_ALLOW_DYNAMIC_RESOLUTION

extern const char* kDartVmIsolateSnapshotBufferName;
extern const char* kDartIsolateSnapshotBufferName;
extern const char* kInstructionsSnapshotName;

void* _DartSymbolLookup(const char* symbol_name);

#define DART_SYMBOL(symbol) _DartSymbolLookup(symbol##Name)

#else  // DART_ALLOW_DYNAMIC_RESOLUTION

extern "C" {
extern void* kDartVmIsolateSnapshotBuffer;
extern void* kDartIsolateSnapshotBuffer;
}

#define DART_SYMBOL(symbol) (&symbol)

#endif  // DART_ALLOW_DYNAMIC_RESOLUTION

// Name of the snapshot blob asset within the FLX bundle.
extern const char kSnapshotAssetKey[];

bool IsRunningPrecompiledCode();

using EmbedderTracingCallback = base::Callback<void(void)>;

struct EmbedderTracingCallbacks {
  EmbedderTracingCallback start_tracing_callback;
  EmbedderTracingCallback stop_tracing_callback;

  EmbedderTracingCallbacks(EmbedderTracingCallback start,
                           EmbedderTracingCallback stop);
};

void InitDartVM();

void SetEmbedderTracingCallbacks(
    std::unique_ptr<EmbedderTracingCallbacks> callbacks);

Dart_Handle DartLibraryTagHandler(Dart_LibraryTag tag,
                                  Dart_Handle library,
                                  Dart_Handle url);
}  // namespace blink

#endif  // SKY_ENGINE_CORE_SCRIPT_DART_INIT_H_
