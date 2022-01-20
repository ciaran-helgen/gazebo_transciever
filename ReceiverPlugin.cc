#include "ReceiverPlugin.hh"
#include <gazebo/sensors/SensorFactory.hh>
#include <gazebo/sensors/SensorManager.hh>
#include <ignition/math/Rand.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/transport/Node.hh>
#include <gazebo/transport/Publisher.hh>
#include <gazebo/sensors/WirelessReceiver.hh>

using namespace gazebo;
using namespace sensors;
using namespace sensors;

GZ_REGISTER_SENSOR_PLUGIN(ReceiverPlugin)

ReceiverPlugin::ReceiverPlugin() : SensorPlugin()
{
}

ReceiverPlugin::~ReceiverPlugin()
{
}

void ReceiverPlugin::Load(sensors::SensorPtr _sensor, sdf::ElementPtr /*_sdf*/)
{
  // Get the parent sensor.
  this->parentSensor =
    std::dynamic_pointer_cast<sensors::WirelessReceiver>(_sensor);

  // Make sure the parent sensor is valid.
  if (!this->parentSensor)
  {
    gzerr << "ReceiverPlugin requires a Wireless Receiver Sensor.\n";
    return;
  }

  // Connect to the sensor update event.
  this->updateConnection = this->parentSensor->ConnectUpdated(
      std::bind(&ReceiverPlugin::OnUpdate, this));

  // Make sure the parent sensor is active.
  this->parentSensor->SetActive(true);
  // this->parentSensor->SetPose(ignition::math::Pose3d (100, 100, 100, 0, 0, 0));

}

void ReceiverPlugin::OnUpdate()
{
  std::string txEssid;
  // msgs::WirelessNodes msg;
  double rxPower;
  double txFreq;

  sensors::SensorPtr sensor_ptr;
  sensor_ptr = SensorManager::Instance()->GetSensor("wirelessTransmitter");

  sensors::WirelessTransmitterPtr transmitSensor;
  transmitSensor = std::dynamic_pointer_cast<sensors::WirelessTransmitter>(sensor_ptr);

  std::cout << "Connected to: " + transmitSensor->ESSID() + "\n";
  double signal_strength;
  const ignition::math::Pose3d pose_tmp = this->parentSensor->Pose();

  signal_strength = transmitSensor->SignalStrength(pose_tmp, this->parentSensor->Gain());
  std::cout << "Signal strengh: " << signal_strength << "\n";
  std::cout << "Transmitter Pose: " << pose_tmp << "\n";

  return;
      
}