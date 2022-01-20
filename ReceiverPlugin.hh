#ifndef _GAZEBO__RECEIVER_PLUGIN_HH_
#define _GAZEBO__RECEIVER_PLUGIN_HH_

#include <string>

#include <gazebo/gazebo.hh>
#include <gazebo/sensors/sensors.hh>

namespace gazebo
{
  class ReceiverPlugin : public SensorPlugin
  {
    public: ReceiverPlugin();

    public: virtual ~ReceiverPlugin();

    // Load the sensor plugin.
    // _sensor Pointer to the sensor that loaded this plugin.
    // _sdf SDF element that describes the plugin.
    public: virtual void Load(sensors::SensorPtr _sensor, sdf::ElementPtr _sdf);

    // Callback that receives the receiver sensor's update signal.
    private: virtual void OnUpdate();

    // Pointer to the receiver sensor
    private: sensors::WirelessReceiverPtr parentSensor;

    // Connection that maintains a link between the receiver sensor's
    // updated signal and the OnUpdate callback.
    private: event::ConnectionPtr updateConnection;
  };
}
#endif