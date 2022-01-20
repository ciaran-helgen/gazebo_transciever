#ifndef _GAZEBO__RECEIVER_PLUGIN_HH_
#define _GAZEBO__RECEIVER_PLUGIN_HH_

#include <string>

#include <gazebo/gazebo.hh>
#include <gazebo/sensors/sensors.hh>

namespace gazebo
{
  /// \brief An example plugin for a receiver sensor.
  class ReceiverPlugin : public SensorPlugin
  {
    /// \brief Constructor.
    public: ReceiverPlugin();

    /// \brief Destructor.
    public: virtual ~ReceiverPlugin();

    /// \brief Load the sensor plugin.
    /// \param[in] _sensor Pointer to the sensor that loaded this plugin.
    /// \param[in] _sdf SDF element that describes the plugin.
    public: virtual void Load(sensors::SensorPtr _sensor, sdf::ElementPtr _sdf);

    /// \brief Callback that receives the receiver sensor's update signal.
    private: virtual void OnUpdate();
    //private: virtual bool UpdateImpl();

    /// \brief Pointer to the receiver sensor
    private: sensors::WirelessReceiverPtr parentSensor;

    /// \brief Connection that maintains a link between the receiver sensor's
    /// updated signal and the OnUpdate callback.
    private: event::ConnectionPtr updateConnection;
  };
}
#endif