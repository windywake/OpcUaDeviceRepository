//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------

#ifndef _JOYSTICK_HH
#define _JOYSTICK_HH

#include <OpcUaGenericServer.hh>

#include "JoystickInterface.hh"

namespace OPCUA {

class Joystick : public OPCUA::GenericServer
{
private:
	JoystickInterface *controller;
	
	/** this method implements the server space for Joystick
	 *
	 *  Please use the methods addVariableNode() and addMethodNode() to define the server space.
	 *  This method is automatically called from within the method run()
	 *
	 *  @return true on success or false if something went wrong during initialization
	 *
	 *  @sa addVariableNode()
	 *  @sa addMethodNode()
	 */
	virtual bool createServerSpace() override;
	
	/** overload this method to get notified about read requests from a remote client for the provided variable name
	 *
	 *  This upcall handler is triggered each time the OPC UA variable (identified by the browseName) is read from a remote client.
	 *  In case the variable is read internally from within the server, this method is not called as this might easily
	 *  cause infinite loops. You can overload this method in derived classes to implement a specific behavior for
	 *  incoming read requests.
	 *
	 *  @param browseName the browse name of the OPC UA variable
	 *  @param value output argument receives the new value of the OPC UA variable
	 *
	 */
	virtual void handleOnRead(const std::string &browseName, ValueType &value) override;

	/** this method notifies about write requests from a remote client for the provided variable name
	 *
	 *  This upcall handler is triggered each time the OPC UA variable (identified by the browseName) is written from a remote client.
	 *  You can overload this method in derived classes to implement a specific behavior for incoming write requests.
	 *
	 *  @param browseName the browse name of the OPC UA variable
	 *  @param value the new value of the OPC UA variable
	 *
	 */
	virtual void handleOnWrite(const std::string &browseName, const ValueType &value) override;

	/** this method notifies about remote method calls from a remote client for the provided OPC UA Method name
	 *
	 *  This upcall handler is triggered each time the OPC UA Method (identified by the browseName) is called from a remote client.
	 *  You can overload this method in derived classes to implement a specific behavior for incoming method calls.
	 *
	 *  @param browseName the browse name of the OPC UA variable
	 *  @param inputs a vector of input-argument-values
	 *  @param outputs a reference to a vector to store the resulting output-argument-values
	 *
	 */
	virtual void handleMethodCall(const std::string &browseName, const std::vector<ValueType> &inputs, std::vector<ValueType> &outputs) override;
	
public:
	Joystick(JoystickInterface *controller);
	virtual ~Joystick();
};

} /* namespace OPCUA */

#endif /* _JOYSTICK_HH */
