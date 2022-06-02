/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef OHOS_DCAMERA_HISYSEVENT_ADAPTER_H
#define OHOS_DCAMERA_HISYSEVENT_ADAPTER_H

#include <string>

namespace OHOS {
namespace DistributedHardware {
const std::string SA_ERROR = "DCAMERA_SA_START_FAIL";
const std::string HDF_ERROR = "DCAMERA_HDF_START_FAIL";
const std::string REGISTER_CAMERA_ERROR = "DCAMERA_REGISTER_FAIL";
const std::string SOFTBUS_SESSIONSERVER_ERROR = "DCAMERA_CREATE_SESSIONSVR_FAIL";
const std::string SOFTBUS_SESSION_ERROR = "DCAMERA_OPEN_SESSION_FAIL";
const std::string SINK_OPEN_CAMERA_ERROR = "DCAMERA_SINK_OPEN_CAM_FAIL";
const std::string START_VIDEO_ENCODER_ERROR = "DCAMERA_ENCODE_FAIL";
const std::string START_VIDEO_DECODER_ERROR = "DCAMERA_DECODE_FAIL";

const std::string INIT_SA_EVENT = "DCAMERA_INIT";
const std::string RELEASE_SA_EVENT = "DCAMERA_EXIT";
const std::string REGIST_CAMERA_EVENT = "DCAMERA_REGISTER";
const std::string UNREGIST_CAMERA_EVENT = "DCAMERA_UNREGISTER";
const std::string OPEN_CAMERA_EVENT = "DCAMERA_OPEN";
const std::string CLOSE_CAMERA_EVENT = "DCAMERA_CLOSE";
const std::string START_CAPTURE_EVENT = "DCAMERA_CAPTURE";

using EventCaptureInfo = struct _EventCaptureInfo {
    int32_t width_;
    int32_t height_;
    int32_t format_;
    bool isCapture_;
    int32_t encodeType_;
    int32_t type_;
};

void ReportStartSaFail(const std::string eventName, int32_t saId, const std::string& errMsg);
void ReportStartHDFFail(const std::string eventName, const std::string& errMsg);
void ReportRegisterCameraFail(const std::string eventName, const std::string& devId, const std::string& dhId,
    std::string version, const std::string& errMsg);
void ReportSoftbusSessionServerFail(const std::string eventName, const std::string& pkgName,
    std::string sessionName, const std::string& errMsg);
void ReportSoftbusSessionFail(const std::string eventName, std::string mySessName,
    std::string peerSessName, std::string peerDevId, const std::string& errMsg);
void ReportSinkOpenCamFail(const std::string eventName, const std::string& dhId, const std::string& errMsg);
void ReportStartVideoEncoderFail(const std::string eventName, int32_t width, int32_t height,
    std::string format, const std::string& errMsg);
void ReportStartVideoDecoderFail(const std::string eventName, int32_t width, int32_t height,
    std::string format, const std::string& errMsg);

void ReportSaEvent(const std::string eventName, int32_t saId, const std::string& errMsg);
void ReportRegisterCameraEvent(const std::string eventName, const std::string& devId, const std::string& dhId,
    std::string version, const std::string& errMsg);
void ReportCameraOperaterEvent(const std::string eventName, const std::string& devId, const std::string& dhId,
    const std::string& errMsg);
void ReportStartCaptureEvent(const std::string eventName, EventCaptureInfo& capture, const std::string& errMsg);
} // namespace DistributedHardware
} // namespace OHOS
#endif // OHOS_DCAMERA_HISYSEVENT_ADAPTER_H