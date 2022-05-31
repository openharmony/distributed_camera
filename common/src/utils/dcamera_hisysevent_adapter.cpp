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

#include "dcamera_hisysevent_adapter.h"

#include "hisysevent.h"
#include "distributed_camera_errno.h"
#include "distributed_hardware_log.h"

namespace OHOS {
namespace DistributedHardware {
namespace {
using HiSysEventNameSpace = OHOS::HiviewDFX::HiSysEvent;
const std::string DOMAIN_STR = std::string(HiSysEventNameSpace::Domain::DISTRIBUTED_CAMERA);
const std::string ENUM_STREAMTYPE_STRINGS[] = {
    "CONTINUOUS_FRAME", "SNAPSHOT_FRAME"
};
const std::string ENUM_ENCODETYPE_STRINGS[] = {
    "ENCODE_TYPE_NULL", "ENCODE_TYPE_H264", "ENCODE_TYPE_H265", "ENCODE_TYPE_JPEG"
};
}

void ReportLoadSaFail(int32_t saId, const std::string& errMsg)
{
    int ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "SA_ERROR",
        HiSysEventNameSpace::EventType::FAULT,
        "SAID", saId,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error ret %d, saId %d, errMsg %s.", ret, saId, errMsg.c_str());
    }
}

void ReportHDFFail(const std::string& errMsg)
{
    int ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "HDF_ERROR",
        HiSysEventNameSpace::EventType::FAULT,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error ret %d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportRegisterHardwareFail(const std::string& devId, const std::string& dhId,
    std::string version, const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "REGISTER_HARDWARE_ERROR",
        HiSysEventNameSpace::EventType::FAULT,
        "DEVID", devId,
        "DHID", dhId,
        "VERSION", version,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error ret %d, devId %s, dhId %s, errMsg %s.", ret, devId.c_str(),
            dhId.c_str(), errMsg.c_str());
    }
}

void ReportSoftbusSessionServerFail(const std::string& pkgName, std::string sessionName, const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "SOFTBUS_SESSIONSERVER_ERROR",
        HiSysEventNameSpace::EventType::FAULT,
        "PKGNAME", pkgName,
        "SESSIONNAME", sessionName,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportSoftbusSessionFail(std::string mySessName, std::string peerSessName, std::string peerDevId,
    const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "SOFTBUS_SESSION_ERROR",
        HiSysEventNameSpace::EventType::FAULT,
        "MYSESSIONNAME", mySessName,
        "PEERSESSIONNAME", peerSessName,
        "PEERDEVID", peerDevId,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportCameraOperaterFail(const std::string& dhId, const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "CAMERA_OPERATER_ERROR",
        HiSysEventNameSpace::EventType::FAULT,
        "DHID", dhId,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, dhId %s, errMsg %s.", ret, dhId.c_str(), errMsg.c_str());
    }
}

void ReportStartVideoEncoderFail(int32_t width, int32_t height, std::string format, const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "START_VIDEO_ENCODER_ERROR",
        HiSysEventNameSpace::EventType::FAULT,
        "WIDTH", width,
        "HEIGHT", height,
        "FORMAT", format,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportStopVideoEncoderFail(const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "STOP_VIDEO_ENCODER_ERROR",
        HiSysEventNameSpace::EventType::FAULT,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportStartVideoDecoderFail(int32_t width, int32_t height, std::string format, const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "START_VIDEO_DECODER_ERROR",
        HiSysEventNameSpace::EventType::FAULT,
        "WIDTH", width,
        "HEIGHT", height,
        "FORMAT", format,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportStopVideoDecoderFail(const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "STOP_VIDEO_DECODER_ERROR",
        HiSysEventNameSpace::EventType::FAULT,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportSaEvent(const std::string eventName, int32_t saId, const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        eventName,
        HiSysEventNameSpace::EventType::BEHAVIOR,
        "SAID", saId,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportHDFEvent(const std::string eventName, const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        eventName,
        HiSysEventNameSpace::EventType::BEHAVIOR,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportRegisterCameraEvent(const std::string eventName, const std::string& devId, const std::string& dhId,
    std::string version, const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        eventName,
        HiSysEventNameSpace::EventType::BEHAVIOR,
        "DEVID", devId,
        "DHID", dhId,
        "VERSION", version,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportCameraOperaterEvent(const std::string eventName, const std::string& devId, const std::string& dhId,
    const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        eventName,
        HiSysEventNameSpace::EventType::BEHAVIOR,
        "DEVID", devId,
        "DHID", dhId,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportConfigStreamsEvent(EventStreamInfo& streamInfo, const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "CONFIG_STREAMS_EVENT",
        HiSysEventNameSpace::EventType::BEHAVIOR,
        "STREAMID", streamInfo.streamId_,
        "WIDTH", streamInfo.width_,
        "HEIGHT", streamInfo.height_,
        "FORMAT", streamInfo.format_,
        "ENCODETYPE", ENUM_ENCODETYPE_STRINGS[streamInfo.encodeType_],
        "STREAMTYPE", ENUM_STREAMTYPE_STRINGS[streamInfo.type_],
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportReleaseStreamsEvent(int32_t streamId, const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "RELEASE_STREAMS_EVENT",
        HiSysEventNameSpace::EventType::BEHAVIOR,
        "STREAMID", streamId,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportStartCaptureEvent(EventCaptureInfo& capture, const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "START_CAPTURE_EVENT",
        HiSysEventNameSpace::EventType::BEHAVIOR,
        "WIDTH", capture.width_,
        "HEIGHT", capture.height_,
        "FORMAT", capture.format_,
        "ISCAPTURE", capture.isCapture_ ? "true" : "false",
        "ENCODETYPE", ENUM_ENCODETYPE_STRINGS[capture.encodeType_],
        "STREAMTYPE", ENUM_STREAMTYPE_STRINGS[capture.type_],
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}

void ReportStopCaptureEvent(int32_t streamId, const std::string& errMsg)
{
    int32_t ret = HiSysEventNameSpace::Write(DOMAIN_STR,
        "STOP_CAPTURE_EVENT",
        HiSysEventNameSpace::EventType::BEHAVIOR,
        "STREAMID", streamId,
        "MSG", errMsg);
    if (ret != DCAMERA_OK) {
        DHLOGE("Write HiSysEvent error, ret:%d, errMsg %s.", ret, errMsg.c_str());
    }
}
} // namespace DistributedHardware
} // namespace OHOS