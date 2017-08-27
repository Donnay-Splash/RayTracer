//
// Renderer.xaml.cpp
// Implementation of the Renderer class
//

#include "pch.h"

#include <random>

#include "Renderer.xaml.h"
#include "Robuffer.h"
#include "DirectXHelpers.h"
#include "SimpleMath.h"
#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"

#include <Threading\ThreadPool.h>

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

// Anonymous namespace 
namespace
{
    static const int kMaxBounces = 40;
    static const int kThreadCount = 4;

    static std::default_random_engine generator;
    static std::uniform_real_distribution<float> distribution;
}

float kRand()
{
    return distribution(generator);
}

Renderer::Renderer():
    m_threadPool(kThreadCount)
{
    InitializeComponent();

    m_scene = std::make_shared<HitableList>();
    auto sphere = std::make_shared<Sphere>(Vector3(0.0f, 0.0f, -1.0f), 0.5f);
    m_scene->AddObjectToScene(sphere);
    auto sphere2 = std::make_shared<Sphere>(Vector3(0.0f, -100.5f, -1.0f), 100.0f);
    m_scene->AddObjectToScene(sphere2);
}

float HitSphere(const Vector3& centre, float radius, const Ray& ray)
{
    Vector3 oc = ray.EndPoint() - centre;
    float a = Vector3::Dot(ray.Direction(), ray.Direction());
    float b = 2.0f * Vector3::Dot(oc, ray.Direction());
    float c = Vector3::Dot(oc, oc) - (radius * radius);
    float discriminant = b*b - 4.0f*a*c;

    if (discriminant < 0) return -1.0f;

    return (-b - sqrt(discriminant)) / (2.0f * a);
}

Vector3 RandomInUnitSphere()
{
    Vector3 point;
    do 
    {
        point = 2.0f * Vector3(kRand(), kRand(), kRand()) - Vector3::kOne;
    } while (Vector3::Dot(point, point) >= 1.0f);

    return point;
}

Color color(const Ray& ray, Hitable::Ptr world, int bounce)
{
    HitData data;
    if(world->Hit(ray, 0.0f, FLT_MAX, data) && bounce <= kMaxBounces)
    {
        Vector3 target = data.Position + data.Normal + RandomInUnitSphere();
        return 0.5f * color(Ray(data.Position, target - data.Position), world, bounce + 1);
    }
    Vector3 unitDirection = Vector3::Normalise(ray.Direction());
    float t = 0.5f * (unitDirection.y + 1.0f);
    return Color::Lerp({1.0f, 1.0f, 1.0f, 1.0f}, {0.3f, 0.4f, 1.0f, 1.0f}, t);
}

void Renderer::Render(int imageWidth, int imageHeight)
{
    const int width = 256;
    const int height = 256;
    const int samples = 30;

    std::vector<uint8_t> pixels;
    pixels.resize(height * width * 4);

    auto renderFunc = [=](int startHeight, int startWidth, int endHeight, int endWidth, uint8_t* pixelData)
    {
        Camera camera;
        for (int j = startHeight; j < endHeight; j++)
        {
            for (int i = startWidth; i < endWidth; i++)
            {
                float floatingHeight = static_cast<float>(height);
                float floatingWidth = static_cast<float>(width);
                Color hitColor(0.0f, 0.0f, 0.0f, 0.0f);
                for (int sample = 0; sample < samples; sample++)
                {
                    float u = (float(i + kRand()) / floatingWidth);
                    float v = (float(j + kRand()) / floatingHeight);
                    auto ray = camera.GetRay(u, v);

                    hitColor += color(ray, m_scene, 0);
                }

                hitColor /= float(samples);
                hitColor.w = 1.0f;
                hitColor = hitColor.GammaEncode();
                uint8_t ir = static_cast<uint8_t>(hitColor.x * 255.99f);
                uint8_t ig = static_cast<uint8_t>(hitColor.y * 255.99f);
                uint8_t ib = static_cast<uint8_t>(hitColor.z * 255.99f);
                uint8_t ia = static_cast<uint8_t>(hitColor.w * 255.99f);


                // Fill pixel data in BGRA8 format
                int index = (((height - 1 - j) * width) + i) * 4;
                pixelData[index] = ib;
                pixelData[index + 1] = ig;
                pixelData[index + 2] = ir;
                pixelData[index + 3] = ia;
            }
        }
    };

    std::vector<Utils::Threading::ThreadPool::TaskFuture<void>> tasks;
    int threadSplit = kThreadCount / 2;
    int heightDelta = height / threadSplit;
    int widthDelta = width / threadSplit;
    for (int i = 0; i < threadSplit; i++)
    {
        for (int j = 0; j < threadSplit; j++)
        {
            int startWidth = widthDelta * i;
            int startHeight = heightDelta * j;
            int endWidth = startWidth + widthDelta;
            int endHeight = startHeight + heightDelta;
            auto future = m_threadPool.Submit([=, &pixels]()
            {
                renderFunc(startHeight, startWidth, endHeight, endWidth, pixels.data());
            });

            tasks.push_back(std::move(future));
        }
    }

    for (auto& task : tasks)
    {
        task.Get();
    }

    /*auto future = m_threadPool.Submit([=, &pixels]()
    {
        renderFunc(127, 119, 128, 120, pixels.data());
    });

    future.Get();*/

    SaveToScreen(pixels.data(), width, height);
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
    }
}


void PathTracer::Renderer::OnDragEnter(Platform::Object ^sender, Windows::UI::Xaml::DragEventArgs ^e)
{
    throw ref new Platform::NotImplementedException();
}
