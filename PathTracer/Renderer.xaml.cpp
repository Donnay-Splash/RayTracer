//
// Renderer.xaml.cpp
// Implementation of the Renderer class
//

#include "pch.h"
#include "Renderer.xaml.h"
#include "Robuffer.h"
#include "DirectXHelpers.h"
#include "SimpleMath.h"

using namespace PathTracer;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace DirectX;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

Renderer::Renderer()
{
    InitializeComponent();
}

void Renderer::Render()
{
    const int width = 300;
    const int height = 200;
    uint8_t pixels[width * height * 4];
    
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            float floatingHeight = static_cast<float>(height);
            float floatingWidth = static_cast<float>(width);
            float r = (j / floatingHeight);
            float g = (i / floatingWidth);
            float b = 0.3f;
            float a = 1.0f;

            Math::Color color(r, g, b, a);
            color = color.GammaEncode();
            
            // TODO: Apply gamma encoding before converting to range [0,255]
            uint8_t ir = static_cast<uint8_t>(color.x * 255.99f);
            uint8_t ig = static_cast<uint8_t>(color.y * 255.99f);
            uint8_t ib = static_cast<uint8_t>(color.z * 255.99f);
            uint8_t ia = static_cast<uint8_t>(color.w * 255.99f);

            const auto colourSizeInBytes = 4;
            const auto rowSizeInBytes = width * colourSizeInBytes;
            auto startIndex = (j * rowSizeInBytes) + (i * colourSizeInBytes);
            // Fill pixel data in BGRA8 format
            pixels[startIndex] = ib;
            pixels[startIndex + 1] = ig;
            pixels[startIndex + 2] = ir;
            pixels[startIndex + 3] = ia;
        }
    }

    SaveToScreen(pixels, width, height);
}

void Renderer::SaveToScreen(uint8_t* pixelData, int width, int height)
{

    Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ bitmap = ref new Windows::UI::Xaml::Media::Imaging::WriteableBitmap(width, height);
    Object^ buffer = bitmap->PixelBuffer;

    // Convert buffer object to underlying IInspectableInterface
    Microsoft::WRL::ComPtr<IInspectable> inspectableBuffer(reinterpret_cast<IInspectable*>(buffer));

    // Query the IBufferByteAccess interface
    Microsoft::WRL::ComPtr<Windows::Storage::Streams::IBufferByteAccess> bufferByteAccess;
    Engine_D3D12::DirectXHelpers::ThrowIfFailed(inspectableBuffer.As(&bufferByteAccess));

    // Get the native pointer to the buffer data
    uint8_t* pixels = nullptr;
    Engine_D3D12::DirectXHelpers::ThrowIfFailed(bufferByteAccess->Buffer(&pixels));

    auto dataSize = width * height * 4;
    memcpy_s(pixels, dataSize, pixelData, dataSize);
    // TODO:: Copy pixel data into buffer and display to the screen
    ScreenBuffer->Source = bitmap;
}

void Renderer::OnKeyUp(Platform::Object^ object, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
    if (e->Key == Windows::System::VirtualKey::Space)
    {
        Render();
    }
}


void PathTracer::Renderer::OnDragEnter(Platform::Object ^sender, Windows::UI::Xaml::DragEventArgs ^e)
{
    throw ref new Platform::NotImplementedException();
}
