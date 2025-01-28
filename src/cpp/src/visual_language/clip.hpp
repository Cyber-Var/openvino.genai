// Copyright (C) 2023-2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstdint>
#include <cstring>
#include <vector>

struct clip_ctx {
    float image_mean[3] = {0.0f, 0.0f, 0.0f};
    float image_std[3] = {1.0f, 1.0f, 1.0f};
    size_t image_size = 0;
};

// RGB uint8 image
struct clip_image_u8 {
    int nx;
    int ny;

    std::vector<uint8_t> buf;
};

// RGB float32 image (NHWC)
// Memory layout: RGBRGBRGB...
struct clip_image_f32 {
    int nx;
    int ny;

    std::vector<float> buf;
};

void bicubic_resize(const clip_image_u8& img, clip_image_u8& dst, int target_width, int target_height);
void bilinear_resize(const clip_image_u8& src, clip_image_u8& dst, int target_width, int target_height);

/** preprocess img and store the result in res_imgs, pad_to_square may be overridden to false depending on model configuration */
clip_image_f32 clip_image_preprocess(struct clip_ctx& ctx, const clip_image_u8& img);

std::vector<clip_image_u8> get_image_patches(
    const clip_image_u8& image,
    const std::vector<std::pair<int, int>>& image_grid_pinpoints,
    const std::pair<int, int>& size,
    int patch_size
);

std::pair<int, int> select_best_resolution(const std::pair<int, int> & original_size, const std::vector<std::pair<int, int>> & possible_resolutions);
