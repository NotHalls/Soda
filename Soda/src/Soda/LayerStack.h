#pragma once

#include "SD_PCH.h"

#include "Core.h"
#include "Layers.h"


namespace Soda
{
    class SD_DLL LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin()
        { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end()
        { return m_Layers.end(); }
    
    protected:
        std::vector<Layer*> m_Layers;
        std::vector<Layer*>::iterator m_InsertedLayers;
    };
}