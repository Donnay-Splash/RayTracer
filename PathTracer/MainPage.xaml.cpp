//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Renderer.xaml.h"


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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
    InitializeComponent();
    KeyUp += ref new Windows::UI::Xaml::Input::KeyEventHandler(this, &PathTracer::MainPage::OnKeyUp);
    SizeChanged += ref new Windows::UI::Xaml::SizeChangedEventHandler(this, &PathTracer::MainPage::OnSizeChanged);
    _renderer->KeyUp += ref new Windows::UI::Xaml::Input::KeyEventHandler(this, &PathTracer::MainPage::OnKeyUp);
    _renderer->Focus(Windows::UI::Xaml::FocusState::Programmatic);
}

void PathTracer::MainPage::OnKeyUp(Platform::Object^ object, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
    if (e->Key == Windows::System::VirtualKey::Space)
    {

    }
}


void PathTracer::MainPage::OnSizeChanged(Platform::Object ^sender, Windows::UI::Xaml::SizeChangedEventArgs ^e)
{
    auto windowSize = e->NewSize;
    _renderer->Render((int)windowSize.Width, (int)windowSize.Height);
}
