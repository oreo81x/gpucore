#pragma once

#include <gpucore/export.hpp>

namespace gpucore
{
    class GPUCORE_API class_name
    {
    public:
         class_name();
        ~class_name();

        void attach() const;
        void detach() const;

    private:
        class components;

        const components *
            m_components = nullptr;
    };
}
