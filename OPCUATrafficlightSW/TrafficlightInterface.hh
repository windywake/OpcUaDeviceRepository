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
#ifndef _TRAFFICLIGHT_INTERFACE_HH
#define _TRAFFICLIGHT_INTERFACE_HH	

#include <string>
#include "OpcUaStatusCode.hh"

/**
 * This is the public C++ interface that needs to be implemented on
 * both sides (the client and the server)
 */
class TrafficlightInterface {
public:
	TrafficlightInterface() {  }
	virtual ~TrafficlightInterface() {  }

	/** XML Specific Getter function for variable LED_RED
	 *
	 *  This function gets LED_RED  from the Server
	 *  When class Trafficlight is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getLED_RED(bool &lED_RED) const = 0;
	
	/** XML Specific Setter function for entity LED_RED
	 *
	 *  This function sets LED_RED  at the Server
	 *  When class Trafficlight is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *
	 *  @param value			:Value to be set
	 * 
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode setLED_RED(const bool &value) = 0;
	
	/** XML Specific Getter function for variable LED_YELLOW
	 *
	 *  This function gets LED_YELLOW  from the Server
	 *  When class Trafficlight is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getLED_YELLOW(bool &lED_YELLOW) const = 0;
	
	/** XML Specific Setter function for entity LED_YELLOW
	 *
	 *  This function sets LED_YELLOW  at the Server
	 *  When class Trafficlight is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *
	 *  @param value			:Value to be set
	 * 
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode setLED_YELLOW(const bool &value) = 0;
	
	/** XML Specific Getter function for variable LED_GREEN
	 *
	 *  This function gets LED_GREEN  from the Server
	 *  When class Trafficlight is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getLED_GREEN(bool &lED_GREEN) const = 0;
	
	/** XML Specific Setter function for entity LED_GREEN
	 *
	 *  This function sets LED_GREEN  at the Server
	 *  When class Trafficlight is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *
	 *  @param value			:Value to be set
	 * 
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode setLED_GREEN(const bool &value) = 0;
	
};

#endif /* _TRAFFICLIGHT_INTERFACE_HH */
