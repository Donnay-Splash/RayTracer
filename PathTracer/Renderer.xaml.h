//
// Renderer.xaml.h
// Declaration of the Renderer class
//

#pragma once

#include "Renderer.g.h"

namespace PathTracer
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Renderer sealed
	{
	public:
		Renderer();

        void Render();
    private:
        void SaveToScreen(uint8_t* pixelData, int width, int height);

        void OnKeyUp(Platform::Object^ object, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);
        void OnDragEnter(Platform::Object ^sender, Windows::UI::Xaml::DragEventArgs ^e);
    };
}
