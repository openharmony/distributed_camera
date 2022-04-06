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

#ifndef OHOS_DCAMERA_CLIENT_H
#define OHOS_DCAMERA_CLIENT_H

#include "icamera_operator.h"

#include "access_token.h"
#include "accesstoken_kit.h"
#include "camera_info.h"
#include "camera_input.h"
#include "camera_manager.h"
#include "capture_input.h"
#include "capture_output.h"
#include "capture_session.h"
#include "hap_token_info.h"
#include "ipc_skeleton.h"
#include "photo_output.h"
#include "preview_output.h"
#include "token_setproc.h"
#include "video_output.h"

#include "dcamera_photo_surface_listener.h"
#include "dcamera_video_surface_listener.h"

namespace OHOS {
namespace DistributedHardware {
const std::string OHOS_PERMISSION_CAMERA = "ohos.permission.CAMERA";
const std::string APP_ID_DESC = "distributed camera";
const std::string LABEL = "label";
const std::string DESCRIPTION = "distributed camera";
const std::string RES_DEVICE_ID = "local";
const std::string DOMAIN = "distribtued_camera.domain";
const int32_t USER_ID = 1;
const int32_t INST_INDEX = 0;
const int32_t GRANT_MODE = 1;
const int32_t GRANT_FLAGS = 1;
const int32_t LABEL_ID = 1;
const int32_t DESCRIPTION_ID = 1;

const Security::AccessToken::HapInfoParams HAP_INFO_PARAMS = {
    .userID = USER_ID,
    .bundleName = OHOS_PERMISSION_CAMERA,
    .instIndex = INST_INDEX,
    .appIDDesc = APP_ID_DESC
};

const Security::AccessToken::PermissionDef PERMISSION_DEF = {
    .permissionName = OHOS_PERMISSION_CAMERA,
    .bundleName = OHOS_PERMISSION_CAMERA,
    .grantMode = GRANT_MODE,
    .availableLevel = Security::AccessToken::ATokenAplEnum::APL_NORMAL,
    .label = LABEL,
    .labelId = LABEL_ID,
    .description = DESCRIPTION,
    .descriptionId = DESCRIPTION_ID
};

const Security::AccessToken::PermissionStateFull PERMISSION_STATE_FULL = {
    .permissionName = OHOS_PERMISSION_CAMERA,
    .isGeneral = true,
    .resDeviceID = {RES_DEVICE_ID},
    .grantStatus = {Security::AccessToken::PermissionState::PERMISSION_GRANTED},
    .grantFlags = {GRANT_FLAGS}
};

const Security::AccessToken::HapPolicyParams HAP_POLICY_PARAMS = {
    .apl = Security::AccessToken::ATokenAplEnum::APL_NORMAL,
    .domain = DOMAIN,
    .permList = {PERMISSION_DEF},
    .permStateList = {PERMISSION_STATE_FULL}
};

class DCameraClient : public ICameraOperator {
public:
    explicit DCameraClient(const std::string& dhId);
    ~DCameraClient();

    int32_t Init() override;
    int32_t UnInit() override;
    int32_t UpdateSettings(std::vector<std::shared_ptr<DCameraSettings>>& settings) override;
    int32_t StartCapture(std::vector<std::shared_ptr<DCameraCaptureInfo>>& captureInfos) override;
    int32_t StopCapture() override;
    int32_t SetStateCallback(std::shared_ptr<StateCallback>& callback) override;
    int32_t SetResultCallback(std::shared_ptr<ResultCallback>& callback) override;

private:
    int32_t ConfigCaptureSession(std::vector<std::shared_ptr<DCameraCaptureInfo>>& captureInfos);
    int32_t ConfigCaptureSessionInner();
    int32_t CreateCaptureOutput(std::vector<std::shared_ptr<DCameraCaptureInfo>>& captureInfos);
    int32_t CreatePhotoOutput(std::shared_ptr<DCameraCaptureInfo>& info);
    int32_t CreateVideoOutput(std::shared_ptr<DCameraCaptureInfo>& info);
    int32_t StartCaptureInner(std::shared_ptr<DCameraCaptureInfo>& info);
    int32_t StartPhotoOutput(std::shared_ptr<DCameraCaptureInfo>& info);
    int32_t StartVideoOutput();
    void SetQualityAndGpsLocation(const std::shared_ptr<CameraStandard::CameraMetadata>& cameraMetadata,
        std::shared_ptr<CameraStandard::PhotoCaptureSetting>& photoCaptureSettings);

    bool isInit_;
    std::string cameraId_;
    sptr<Surface> photoSurface_;
    sptr<Surface> videoSurface_;
    sptr<CameraStandard::CameraInfo> cameraInfo_;
    sptr<CameraStandard::CameraManager> cameraManager_;
    sptr<CameraStandard::CaptureSession> captureSession_;
    sptr<CameraStandard::CaptureInput> cameraInput_;
    sptr<CameraStandard::CaptureOutput> photoOutput_;
    sptr<CameraStandard::CaptureOutput> previewOutput_;
    sptr<CameraStandard::CaptureOutput> videoOutput_;
    std::shared_ptr<StateCallback> stateCallback_;
    std::shared_ptr<ResultCallback> resultCallback_;
    std::shared_ptr<DCameraPhotoSurfaceListener> photoListener_;
    std::shared_ptr<DCameraVideoSurfaceListener> videoListener_;
    Security::AccessToken::AccessTokenIDEx tokenIdEx_;
};
} // namespace DistributedHardware
} // namespace OHOS
#endif // OHOS_DCAMERA_CLIENT_H