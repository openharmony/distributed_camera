/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DCAMERA_SA_PROCESS_STATE_H
#define DCAMERA_SA_PROCESS_STATE_H

#include "single_instance.h"

#include <mutex>

namespace OHOS {
namespace DistributedHardware {
class DCameraSAProcessState {
DECLARE_SINGLE_INSTANCE_BASE(DCameraSAProcessState);

public:
    void SetSinkProcessExit();
    void SetSourceProcessExit();
private:
    typedef enum {
        DCAMERA_SA_EXIT_STATE_START = 0,
        DCAMERA_SA_EXIT_STATE_STOP = 1
    } DCameraSAState;
    DCameraSAProcessState() = default;
    ~DCameraSAProcessState();
    void CheckSAProcessState();
    DCameraSAState sinkSAState_ = DCAMERA_SA_EXIT_STATE_START;
    DCameraSAState sourceSAState_ = DCAMERA_SA_EXIT_STATE_START;
    std::mutex saProcessState_;
};
} // namespace DistributedHardware
} // namespace OHOS
#endif // DCAMERA_SA_EXIT_STATE_H
