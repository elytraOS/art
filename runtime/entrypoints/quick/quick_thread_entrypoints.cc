/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "callee_save_frame.h"
#include "jit/jit.h"
#include "runtime.h"
#include "thread-inl.h"

namespace art {

extern "C" void artTestSuspendFromCode(Thread* self) REQUIRES_SHARED(Locks::mutator_lock_) {
  // Called when there is a pending checkpoint or suspend request.
  ScopedQuickEntrypointChecks sqec(self);
  self->CheckSuspend();
}

extern "C" void artImplicitSuspendFromCode(Thread* self) REQUIRES_SHARED(Locks::mutator_lock_) {
  // Called when there is a pending checkpoint or suspend request.
  ScopedQuickEntrypointChecks sqec(self);
  self->CheckSuspend(/*implicit=*/ true);
}

extern "C" void artCompileOptimized(ArtMethod* method, Thread* self)
    REQUIRES_SHARED(Locks::mutator_lock_) {
  ScopedQuickEntrypointChecks sqec(self);
  ScopedAssertNoThreadSuspension sants("Enqueuing optimized compilation");
  Runtime::Current()->GetJit()->EnqueueOptimizedCompilation(method, self);
}

}  // namespace art
