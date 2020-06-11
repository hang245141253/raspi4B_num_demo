// Copyright (c) 2019 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/highgui.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "paddle_api.h"  // NOLINT

using namespace paddle::lite_api;  // NOLINT

const std::vector<float> INPUT_MEAN = {0.f};
const std::vector<float> INPUT_STD = {1.f};

int64_t ShapeProduction(const shape_t& shape) {
  int64_t res = 1;
  for (auto i : shape) res *= i;
  return res;
}

void RunModel(cv::Mat &photo,
              std::shared_ptr<paddle::lite_api::PaddlePredictor> &predictor) {

    //Pre_process
    cv::cvtColor(photo, photo, CV_BGR2GRAY);//三通道 -> 灰度
    if(photo.cols != 28 || photo.rows != 28) {
        std::cout << "当前图像尺寸为:"
                  << photo.cols
                  << "x"
                  << photo.rows
                  << std::endl;
        cv::resize(photo, photo, cv::Size(28, 28), 0.f, 0.f);
        std::cout << "img has been resize."
                  << std::endl;
    }
    photo.convertTo(photo, CV_32FC1, 1.f / 255.f * 2.f , -1.f);//归一化
//    std::cout << photo << std::endl;//查看形状
//    cv::imshow("num", photo);
//    cv::waitKey(0);

    // Get Input Tensor
    std::unique_ptr<Tensor> input_tensor(std::move(predictor->GetInput(0)));
    input_tensor->Resize({1, 1, 28, 28});
    auto* input_data = input_tensor->mutable_data<float>();

    // NHWC->NCHW
    const float *image_data = reinterpret_cast<const float *>(photo.data);
    float32x4_t vmean0 = vdupq_n_f32(INPUT_MEAN[0]);
    float32x4_t vscale0 = vdupq_n_f32(1.0f / INPUT_STD[0]);
    float *input_data_c0 = input_data;
    int i = 0;
    for (; i < photo.cols*photo.rows; i += 1) {
      float32x4x3_t vin3 = vld3q_f32(image_data);
      float32x4_t vsub0 = vsubq_f32(vin3.val[0], vmean0);
      float32x4_t vs0 = vmulq_f32(vsub0, vscale0);
      vst1q_f32(input_data_c0, vs0);
      image_data += 1;
      input_data_c0 += 1;
    }
    for (; i < photo.cols*photo.rows; i++) {
      *(input_data_c0++) = (*(image_data++) - INPUT_MEAN[0]) / INPUT_STD[0];
    }

    // Detection Model Run
    predictor->Run();

    // Get Output Tensor
    std::unique_ptr<const Tensor> output_tensor(std::move(predictor->GetOutput(0)));
    auto output_data = output_tensor->data<float>();
    auto output_shape = output_tensor->shape();
    int64_t outputSize = ShapeProduction(output_shape);
    for(int i =0 ;i<outputSize ; i++) {
    //std::cout << output_data[i] << std::endl;
        if(output_data[i] > 0.5f )
            std::cout << "预测结果为:" << i << " Acc:" << output_data[i] << std::endl;
    }
}

int main(int argc, char** argv) {

    std::string num_model = argv[1];
    const int CPU_THREAD_NUM = 4;
    const paddle::lite_api::PowerMode CPU_POWER_MODE = paddle::lite_api::PowerMode::LITE_POWER_FULL;

    // Detection
    MobileConfig config;
    config.set_threads(CPU_THREAD_NUM);
    config.set_power_mode(CPU_POWER_MODE);
    config.set_model_from_file(num_model);//v2.6 API

    // Create Predictor For Detction Model
    std::shared_ptr<PaddlePredictor> predictor = CreatePaddlePredictor<MobileConfig>(config);

    if (argc == 3){
      std::string img_path = argv[2];
      std::cout << argv[2] << std::endl;
      cv::Mat photo = imread(img_path, cv::IMREAD_COLOR);
      RunModel(photo,predictor);
      cv::imshow("num", photo);
      cv::waitKey(0);
    }else {
      exit(1);
    }
    return 0;
}
