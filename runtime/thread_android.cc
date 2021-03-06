/*
 * Copyright (C) 2011 The Android Open Source Project
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

#include <signal.h>
#include <sys/mman.h>

#include "thread.h"

namespace art {

void Thread::SetUpAlternateSignalStack() {
  // Bionic does this for us.
}

void Thread::TearDownAlternateSignalStack() {
  // Bionic does this for us.
}

void Thread::MadviseAwayAlternateSignalStack() {
  stack_t old_ss;
  int result = sigaltstack(nullptr, &old_ss);
  CHECK_EQ(result, 0);
  // Note: We're testing and benchmarking ART on devices with old kernels
  // which may not support `MADV_FREE`, so we do not check the result.
  // It should succeed on devices with Android 12+.
  madvise(old_ss.ss_sp, old_ss.ss_size, MADV_FREE);
}

}  // namespace art
