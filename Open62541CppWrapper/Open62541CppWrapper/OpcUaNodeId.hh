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

#ifndef OPCUANODEID_HH_
#define OPCUANODEID_HH_

#ifdef HAS_OPCUA
	#ifdef UA_ENABLE_AMALGAMATION
		#include <open62541.h>
	#else
		#include <open62541/types.h>
	#endif
#endif

#include <string>

namespace OPCUA {

class NodeId {
public:
#ifdef HAS_OPCUA
	typedef UA_NodeId NativeIdType;
#else
	typedef std::string NativeIdType;
#endif
private:
	/// the internal (native) id value
	NativeIdType _id;

protected:
	/// method copies the native id value into the NodeId's member variable
	void copy(const NativeIdType &id, const bool cleanupPreviousId=true);

public:
	/// default constructor creates a null id
	NodeId();

	/// string-based node-id constructor
	NodeId(const std::string &id, const unsigned short &index=1);

	/// numeric node-id constructor
	NodeId(const unsigned int &id, const unsigned short &index=1);

	/// copy constructor
	NodeId(const NodeId &id) {
		copy(id._id, false);
	}

	/// copy constructor for the native ID type
	NodeId(const NativeIdType &id) {
		copy(id, false);
	}

	/// default destructor
	virtual ~NodeId();

	/// object-type copy assigned operator (overrides and frees previous internal value)
	inline NodeId& operator=(const NodeId &id) {
		this->copy(id._id);
		return *this;
	}

	/// internal value pointer-type assignment copy operator
	inline NodeId& operator=(const NativeIdType &id) {
		this->copy(id);
		return *this;
	}

	/// native const access
	operator const NativeIdType*() const;

	/// native id conversion operator (makes a copy of the internal id)
	operator NativeIdType() const;

	/// comparison operator: equality
	bool operator ==(const NodeId &id) const;
	/// comparison operator: smaller than right hand side
	bool operator <(const NodeId &id) const;

	/// checks if the id has been set to a value or is empty
	bool isNull() const;

	/// returns true if ID is a numeric type
	bool isNumericType() const;

	/// returns true if ID is a numeric type
	bool isStringType() const;

	/// returns a string representation of the ID without the namespace index
	std::string getSimpleName() const;
};

} /* namespace OPCUA */

#endif /* OPCUANODEID_HH_ */
