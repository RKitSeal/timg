// -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil; -*-
// (c) 2021 Henner Zeller <h.zeller@acm.org>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation version 2.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://gnu.org/licenses/gpl-2.0.txt>

#ifndef TIMG_STB_IMAGE_SOURCE_H
#define TIMG_STB_IMAGE_SOURCE_H

#include "display-options.h"
#include "image-source.h"

#include <memory>

namespace timg {
// STB image loader fallback. Not pretty and should only be used as fallback.
class STBImageSource final : public ImageSource {
public:
    STBImageSource(const std::string &filename);
    ~STBImageSource();

    // Attempt to load given filename as video, open stream and set-up scaling.
    // Returns true on success.
    bool LoadAndScale(const DisplayOptions &options,
                      int frame_offset, int frame_count) final;

    // Play video up to given duration.
    //
    // The reference to the "interrupt_received" can be updated by a signal
    // while the method is running and shall be checked often.
    void SendFrames(Duration duration, int loops,
                    const volatile sig_atomic_t &interrupt_received,
                    const Renderer::WriteFramebufferFun &sink) final;
private:
    class PreprocessedFrame;
    std::vector<PreprocessedFrame*> frames_;
    int max_frames_ = 1;
    int indentation_ = 0;
};
}  // namespace timg

#endif  // TIMG_STB_IMAGE_SOURCE_H
