#pragma once

/////////////////
//HEADERS
/////////////////
#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Entity/ComponentIterator.hpp>

namespace ax
{
    template<typename C>
    class AXION_CORE_API MonothreadSystem : public NonCopyable
    {
    public:
        virtual void onStart() noexcept {};
        virtual void onStop() noexcept {};

        virtual void onCreate(C& entity) noexcept {};
        virtual void onUpdate(ComponentIterator<C>& it) noexcept {};
        virtual void onDestroy(C& entity) noexcept {};
    };
}