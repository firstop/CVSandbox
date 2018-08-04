/*
    DirectShow video source library of Computer Vision Sandbox

    Copyright (C) 2011-2018, cvsandbox
    http://www.cvsandbox.com/contacts.html

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#ifndef CVS_XLOCAL_VIDEO_DEVICE_HPP
#define CVS_XLOCAL_VIDEO_DEVICE_HPP

#include <XInterfaces.hpp>
#include <IVideoSource.hpp>
#include <vector>

#include "XDeviceName.hpp"
#include "XDeviceCapabilities.hpp"
#include "XDevicePinInfo.hpp"

namespace CVSandbox { namespace Video { namespace DirectShow
{

namespace Private
{
    class XLocalVideoDeviceData;
};

enum class XVideoProperty
{
    Brightness = 0,
    Contrast,
    Hue,
    Saturation,
    Sharpness,
    Gamma,
    ColorEnable,
    WhiteBalance,
    BacklightCompensation,
    Gain
};

// Class which provides access to local video devices available through DirectShow interface
class XLocalVideoDevice : public IVideoSource, private Uncopyable
{
private:
    XLocalVideoDevice( const std::string& deviceMoniker );

public:
    ~XLocalVideoDevice( );

    static const std::shared_ptr<XLocalVideoDevice> Create( const std::string& deviceMoniker = std::string( ) );

    // Start video device (start its background thread which manages video acquisition)
    virtual XErrorCode Start( );
    // Signal video source to stop and finalize its background thread
    virtual void SignalToStop( );
    // Wait till video source stops
    virtual void WaitForStop( );
    // Check if video source (its background thread) is running or not
    virtual bool IsRunning( );
    // Terminate video source (call it ONLY as the last action of stopping video source, when nothing else helps)
    virtual void Terminate( );
    // Get number of frames received since the the start of the video source
    virtual uint32_t FramesReceived( );

    // Set video source listener
    virtual void SetListener( IVideoSourceListener* listener );

    // Set device moniker for the video source (video source must not be running)
    bool SetDeviceMoniker( const std::string& moniker );
    // Set resolution and frame rate of the device (video source must not be running)
    bool SetResolution( const XDeviceCapabilities& resolution, uint32_t requestedFps = 0 );
    // Set video input of the device
    void SetVideoInput( const XDevicePinInfo& input );

    // Get capabilities of the device (resolutions and frame rates)
    const std::vector<XDeviceCapabilities> GetCapabilities( );
    // Get available video pins of the device if any
    const std::vector<XDevicePinInfo> GetInputVideoPins( );
    // Check if device supports crossbar, which would allow setting video input pin
    bool IsCrossbarSupported( );

    // Get list of available video devices in the system
    static std::vector<XDeviceName> GetAvailableDevices( );

    // The IsRunning() reports if video source's background thread is running or not. However,
    // it does not mean the video device itself is running. When the thread is started, it
    // needs to perform certain configuration of the device and start it, which may or may not
    // succeed (device can be un-plugged, used by another application, etc). So the
    // IsDeviceRunning() reports status of the device itself.

    // Check if device is running
    bool IsDeviceRunning( ) const;
    // Wait till video configuration becomes available (milliseconds)
    bool WaitForDeviceRunning( uint32_t msec );

    // Check if video configuration is supported (device must be running)
    bool IsVideoConfigSupported( ) const;

    // Set the specified video property. The device does not have to be running. If it is not,
    // the setting will be cached and applied as soon as the device gets running.
    XErrorCode SetVideoProperty( XVideoProperty property, int32_t value, bool automatic = false );
    // Get current value if the specified video property. The device must be running.
    XErrorCode GetVideoProperty( XVideoProperty property, int32_t* value, bool* automatic = nullptr ) const;
    // Get range of values supported by the specified video property
    XErrorCode GetVideoPropertyRange( XVideoProperty property, int32_t* min, int32_t* max, int32_t* step, int32_t* defaultValue, bool* isAutomaticSupported ) const;

private:
    Private::XLocalVideoDeviceData* mData;
};

} } } // namespace CVSandbox::Video::DirectShow

#endif // CVS_XLOCAL_VIDEO_DEVICE_HPP
