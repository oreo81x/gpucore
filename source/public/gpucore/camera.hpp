#pragma once

#include <gpucore/export.hpp>

namespace gpucore
{
    class GPUCORE_API camera
    {
    public:
         camera();
        ~camera();

        const float *get_view_matrix() const;
        const float *get_clip_matrix() const;

        camera(float a_aspect_ratio, float a_field_of_view_in_radians, float a_near_plane, float a_far_plane, const float *a_center = nullptr, const float *a_orient = nullptr);

    private:
        class components;

        const components *
            m_components = nullptr;
    };
}
