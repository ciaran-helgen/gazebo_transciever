#include "ReceiverPlugin.hh"
#include <gazebo/sensors/SensorFactory.hh>
#include <gazebo/sensors/SensorManager.hh>
#include <ignition/math/Rand.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/transport/Node.hh>
#include <gazebo/transport/Publisher.hh>
#include <gazebo/sensors/WirelessReceiver.hh>

using namespace gazebo;
//using namespace sensors;
//using namespace physics;
//using namespace ignition::math;

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

}

void ReceiverPlugin::OnUpdate()
{
  std::string txEssid;
  // create sensor pointer
  sensors::SensorPtr sensor_ptr;
  // find wirelessTransmitter sensor and instantiate a sensor object for it
  sensor_ptr = sensors::SensorManager::Instance()->GetSensor("wirelessTransmitter");
  // create a wireless transmitter pointer
  sensors::WirelessTransmitterPtr transmitSensor;
  // convert sensor pointer to wireless transmitter pointer
  transmitSensor = std::dynamic_pointer_cast<sensors::WirelessTransmitter>(sensor_ptr);

  //Get pointer to receiver model
  physics::WorldPtr world = physics::get_world("default");
  physics::ModelPtr model_ptr = world->ModelByName("wirelessReceiver");

  // Get pose of receiver model in global frame
  ignition::math::Pose3d model_pose = model_ptr->RelativePose();

  // Calculate global pose of sensor relative to model
  // get pose of sensor relative to model
  ignition::math::Pose3d sensor_global_pose = this->parentSensor->Pose();
  // sum pose of sensor with global model pose
  sensor_global_pose += model_pose;


  std::cout << "Connected to: " + transmitSensor->ESSID() + "\n";
  double signal_strength;
  

  signal_strength = transmitSensor->SignalStrength(model_pose, this->parentSensor->Gain());
  std::cout << "Signal strengh: " << signal_strength << "\n";
  std::cout << "Receiver Pose: " << model_pose << "\n";

  return;
      
}