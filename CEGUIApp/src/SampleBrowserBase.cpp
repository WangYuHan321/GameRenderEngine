/***********************************************************************
    created:    24/9/2004
    author:     Paul D Turner
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2008 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#include "SampleBrowserBase.h"

#include "CEGUISamplesConfig.h"
#include "CEGuiOpenGLBaseApplication.h"


/*************************************************************************
    Constructor
*************************************************************************/
SampleBrowserBase::SampleBrowserBase() :
        d_baseApp(nullptr),
        d_quitting(false)
{}


/*************************************************************************
    Destructor
*************************************************************************/
SampleBrowserBase::~SampleBrowserBase()
{
    if (d_baseApp)
    {
        d_baseApp->cleanup();
        delete d_baseApp;
    }

}

/*************************************************************************
    Application entry point
*************************************************************************/
int SampleBrowserBase::run()
{
    try
    {
        if (initialise("CEGUI.log", CEGUI::String()))
            d_baseApp->run();
        cleanup();
    }
    catch (const std::exception& exc)
    {
        outputExceptionMessage(exc.what());
    }
    catch (const char* exc)
    {
        outputExceptionMessage(exc);
    }
    catch (...)
    {
        outputExceptionMessage("Unknown exception was caught!");
    }
    return 0;
}

/*************************************************************************
    Start the SamplesFramework application
*************************************************************************/
bool SampleBrowserBase::initialise
  (const CEGUI::String& logFile, const CEGUI::String& dataPathPrefixOverride)
{
    d_baseApp = new CEGuiOpenGLBaseApplication();

    if (!d_baseApp)
        throw CEGUI::GenericException("No renderer was selected!");

    return d_baseApp->init(this, logFile, dataPathPrefixOverride);
}

void SampleBrowserBase::cleanup()
{
    if (d_baseApp)
    {
        d_baseApp->cleanup();
        delete d_baseApp;
        d_baseApp = nullptr;
    }
}

void SampleBrowserBase::renderSingleFrame(float elapsed)
{
    d_baseApp->renderSingleFrame(elapsed);
}

/*************************************************************************
    Output a message to the user in some OS independant way.
*************************************************************************/
void SampleBrowserBase::outputExceptionMessage(const char* message)
{
#if defined(__WIN32__) || defined(_WIN32)
    MessageBoxA(nullptr, message, "CEGUI - Exception", MB_OK|MB_ICONERROR);
#elif defined(__ANDROID__)
    __android_log_write (ANDROID_LOG_ERROR, "CEGUISampleFramework_NDK",
      "An exception was thrown within the sample framework:");
    __android_log_write (ANDROID_LOG_ERROR, "CEGUISampleFramework_NDK",
      message);
#else
    std::cout << "An exception was thrown within the sample framework:" << std::endl;
    std::cout << message << std::endl;
#endif
}

void SampleBrowserBase::setQuitting(bool quit)
{
    d_quitting = quit;
}

bool SampleBrowserBase::isQuitting()
{
    return d_quitting;
}

void SampleBrowserBase::setApplicationWindowSize(int width, int height)
{
    d_appWindowWidth = width;
    d_appWindowHeight = height;
}
