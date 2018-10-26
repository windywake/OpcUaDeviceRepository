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

#include <sstream>
#include "OpcUaValueType.hh"

namespace OPCUA {

// NativeVariantType value copy
template <>
void ValueType::copy(const NativeVariantType &var, const bool &cleanupPreviousValue)
{
#ifdef HAS_OPCUA
	if(cleanupPreviousValue) {
		UA_Variant_deleteMembers(&_value);
	}
	UA_Variant_init(&_value);
	// deep-copy UA variant value
	UA_Variant_copy(&var, &_value);
#else
	_value = var;
#endif
}

// default constructor
ValueType::ValueType()
{
#ifdef HAS_OPCUA
	UA_Variant_init(&_value);
#else
	_value = std::stringstream(); // clear the stringstream
#endif
}

// default destructor
ValueType::~ValueType()
{
#ifdef HAS_OPCUA
	UA_Variant_deleteMembers(&_value);
#endif
}

ValueType::ValueType(const ValueType &value)
{
	copy(value._value, false);
}

/// internal value pointer-type copy constructor
ValueType::ValueType(const NativeVariantType *value)
{
	this->copy(*value, false);
}

ValueType& ValueType::operator=(const ValueType &value)
{
	this->copy(value._value);
	return *this;
}

/// internal value pointer-type assignment copy operator
ValueType& ValueType::operator=(const NativeVariantType *value)
{
	this->copy(*value);
	return *this;
}

bool ValueType::isEmpty() const
{
#ifdef HAS_OPCUA
	return UA_Variant_isEmpty(&_value);
#else
	return _value.str().empty();
#endif
}

bool ValueType::isArrayType() const
{
	if(isEmpty()) {
		return false;
	}
#ifdef HAS_OPCUA
	return ! UA_Variant_isScalar(&_value);
#else
	return false;
#endif
}


/// method checks if the internal value is an integer type
bool ValueType::isIntegerType() const
{
	if(isEmpty()) {
		return false;
	}
#ifdef HAS_OPCUA
	return (_value.type == &UA_TYPES[UA_TYPES_INT32]);
#else
	return false;
#endif
}
/// method checks if the internal value is a boolean type
bool ValueType::isBooleanType() const
{
	if(isEmpty()) {
		return false;
	}
#ifdef HAS_OPCUA
	return (_value.type == &UA_TYPES[UA_TYPES_BOOLEAN]);
#else
	return false;
#endif
}
/// method checks if the internal value is a floating type
bool ValueType::isDoubleType() const
{
	if(isEmpty()) {
		return false;
	}
#ifdef HAS_OPCUA
	return (_value.type == &UA_TYPES[UA_TYPES_DOUBLE]);
#else
	return false;
#endif
}
/// method checks if the internal value is a string type
bool ValueType::isStringType() const
{
	if(isEmpty()) {
		return false;
	}
#ifdef HAS_OPCUA
	return (_value.type == &UA_TYPES[UA_TYPES_STRING]);
#else
	return false;
#endif
}

/**
 * Specialization of the copy template method for the C++ primitive types
 */

template <>
void ValueType::copy(const int &var, const bool &cleanupPreviousValue)
{
#ifdef HAS_OPCUA
	if(cleanupPreviousValue) {
		UA_Variant_deleteMembers(&_value);
	}
	UA_Variant_init(&_value);
	UA_Variant_setScalarCopy(&_value, &var, &UA_TYPES[UA_TYPES_INT32]);
#else
	if(cleanupPreviousValue) {
		_value = std::stringstream(); // clear the stringstream
	}
	_value << *var;
#endif
}

template <>
void ValueType::copy(const bool &var, const bool &cleanupPreviousValue)
{
#ifdef HAS_OPCUA
	if(cleanupPreviousValue) {
		UA_Variant_deleteMembers(&_value);
	}
	UA_Variant_init(&_value);
	UA_Variant_setScalarCopy(&_value, &var, &UA_TYPES[UA_TYPES_BOOLEAN]);
#else
	if(cleanupPreviousValue) {
		_value = std::stringstream(); // clear the stringstream
	}
	_value << *var;
#endif
}

template <>
void ValueType::copy(const double &var, const bool &cleanupPreviousValue)
{
#ifdef HAS_OPCUA
	if(cleanupPreviousValue) {
		UA_Variant_deleteMembers(&_value);
	}
	UA_Variant_init(&_value);
	UA_Variant_setScalarCopy(&_value, &var, &UA_TYPES[UA_TYPES_DOUBLE]);
#else
	if(cleanupPreviousValue) {
		_value = std::stringstream(); // clear the stringstream
	}
	_value << *var;
#endif
}

template <>
void ValueType::copy(const std::string &var, const bool &cleanupPreviousValue)
{
#ifdef HAS_OPCUA
	if(cleanupPreviousValue) {
		UA_Variant_deleteMembers(&_value);
	}
	UA_Variant_init(&_value);
	// copy string
	UA_String ua_s;
	ua_s.length = var.length();
	ua_s.data = (UA_Byte*)var.c_str();
	// set string variant
	UA_Variant_setScalarCopy(&_value, &ua_s, &UA_TYPES[UA_TYPES_STRING]);
#else
	v.str(*var); // overwrite internal string
#endif
}

template <>
void ValueType::copy(const std::vector<int> &var, const bool &cleanupPreviousValue)
{
#ifdef HAS_OPCUA
	if(cleanupPreviousValue) {
		UA_Variant_deleteMembers(&_value);
	}
	UA_Variant_init(&_value);

	// deep-copy the array values
	UA_Variant_setArrayCopy(&_value, var.data(), var.size(), &UA_TYPES[UA_TYPES_INT32]);

	// one-dimension size
	_value.arrayDimensionsSize = 1;
	// set array dimension
	_value.arrayLength = var.size();
	// set the single array dimension-size
	_value.arrayDimensions = UA_UInt32_new();
	_value.arrayDimensions[0] = var.size();

#else
	if(cleanupPreviousValue) {
		_value = std::stringstream(); // clear the stringstream
	}
	for(auto it=var->begin(); it != var->end(); it++) {
		_value << *it << " ";
	}
#endif
}
template <>
void ValueType::copy(const std::vector<bool> &var, const bool &cleanupPreviousValue)
{
#ifdef HAS_OPCUA
	if(cleanupPreviousValue) {
		UA_Variant_deleteMembers(&_value);
	}
	UA_Variant_init(&_value);

	// create a copy of the boolean array values
	UA_Boolean uaBoolArray[var.size()];
	for(size_t i=0; i<var.size(); ++i) {
		uaBoolArray[i] = var[i];
	}

	// deep-copy the array values
	UA_Variant_setArrayCopy(&_value, uaBoolArray, var.size(), &UA_TYPES[UA_TYPES_BOOLEAN]);

	// one-dimension size
	_value.arrayDimensionsSize = 1;
	// set array dimension
	_value.arrayLength = var.size();
	// set the single array dimension-size
	_value.arrayDimensions = UA_UInt32_new();
	_value.arrayDimensions[0] = var.size();

#else
	if(cleanupPreviousValue) {
		_value = std::stringstream(); // clear the stringstream
	}
	for(auto it=var->begin(); it != var->end(); it++) {
		_value << *it << " ";
	}
#endif
}
template <>
void ValueType::copy(const std::vector<double> &var, const bool &cleanupPreviousValue)
{
#ifdef HAS_OPCUA
	if(cleanupPreviousValue) {
		UA_Variant_deleteMembers(&_value);
	}
	UA_Variant_init(&_value);

	// deep-copy the array values
	UA_Variant_setArrayCopy(&_value, var.data(), var.size(), &UA_TYPES[UA_TYPES_DOUBLE]);

	// one-dimension size
	_value.arrayDimensionsSize = 1;
	// set array dimension
	_value.arrayLength = var.size();
	// set the single array dimension-size
	_value.arrayDimensions = UA_UInt32_new();
	_value.arrayDimensions[0] = var.size();

#else
	if(cleanupPreviousValue) {
		_value = std::stringstream(); // clear the stringstream
	}
	for(auto it=var->begin(); it != var->end(); it++) {
		_value << *it << " ";
	}
#endif
}
template <>
void ValueType::copy(const std::vector<std::string> &var, const bool &cleanupPreviousValue)
{
#ifdef HAS_OPCUA
	if(cleanupPreviousValue) {
		UA_Variant_deleteMembers(&_value);
	}
	UA_Variant_init(&_value);

	// shallow-copy the strings into a local array
	UA_String ua_arr[var.size()];
	for(size_t i=0; i<var.size(); ++i) {
		ua_arr[i].length = var[i].length();
		ua_arr[i].data = (UA_Byte*)var[i].c_str();
	}

	// deep-copy the array values
	UA_Variant_setArrayCopy(&_value, ua_arr, var.size(), &UA_TYPES[UA_TYPES_STRING]);

	// one-dimension size
	_value.arrayDimensionsSize = 1;
	// set array dimension
	_value.arrayLength = var.size();
	// set the single array dimension-size
	_value.arrayDimensions = UA_UInt32_new();
	_value.arrayDimensions[0] = var.size();

#else
	if(cleanupPreviousValue) {
		_value = std::stringstream(); // clear the stringstream
	}
	for(auto it=var->begin(); it != var->end(); it++) {
		_value << *it << " ";
	}
#endif
}

/**
 * Specialization of the conversion operator template method for the C++ primitive types
 */

template <>
ValueType::operator int() const {
	if(isArrayType() || isEmpty()) {
		return 0;
	}

	#ifdef HAS_OPCUA
	if(isIntegerType()) {
		return *(static_cast<UA_Int32*>(_value.data));;
	}
	#else
	if(_value.good()) {
		return std::stoi(_value.str());
	}
	#endif
	return 0;
}

template <>
ValueType::operator bool() const {
	if(isArrayType() || isEmpty()) {
		return false;
	}

	#ifdef HAS_OPCUA
	if(isBooleanType()) {
		return *(static_cast<UA_Boolean*>(_value.data));;
	}
	#else
	bool result;
	std::istringstream iss(_value.str());
	iss >> std::boolalpha >> result;
	if(iss.good()) {
		return result;
	}
	#endif
	return 0;
}

template <>
ValueType::operator double() const {
	if(isArrayType() || isEmpty()) {
		return 0.0;
	}

	#ifdef HAS_OPCUA
	if(isDoubleType()) {
		return *(static_cast<UA_Double*>(_value.data));;
	}
	#else
	if(_value.good()) {
		return std::stod(_value.str());
	}
	#endif
	return 0.0;
}

template <>
ValueType::operator std::string() const {
	if(isArrayType() || isEmpty()) {
		return std::string();
	}

	#ifdef HAS_OPCUA
	if(isStringType()) {
		UA_String *temp = (UA_String*)_value.data;
		std::string str((const char*)temp->data, temp->length);
		return str;
	}
	return std::string();
	#else
	return v.str();
	#endif
}
//template <>
ValueType::operator const char*() const {
	if(isArrayType() || isEmpty()) {
		return 0;
	}

	#ifdef HAS_OPCUA
	if(isStringType()) {
		UA_String *temp = (UA_String*)_value.data;
		std::string str((const char*)temp->data, temp->length);
		return str.c_str();
	}
	return 0;
	#else
	return v.str().c_str();
	#endif
}

template <>
ValueType::operator ValueType::NativeVariantType() const {
#ifdef HAS_OPCUA
	UA_Variant v_out;
	UA_Variant_init(&v_out);
	UA_Variant_copy(&_value, &v_out);
	return v_out;
#else
	return _value;
#endif
}

template <>
ValueType::operator std::vector<int>() const
{
	std::vector<int> result;
	if(!isArrayType() || isEmpty()) {
		return result;
	}

#ifdef HAS_OPCUA
	if(isIntegerType()) {
		UA_Int32 *uaArray = (UA_Int32*)_value.data;
		for(size_t i=0; i<_value.arrayLength; ++i) {
			result.push_back( uaArray[i] );
		}
	}
#else
	if(_value.good()) {
//		return std::stoi(_value.str());
	}
#endif
	return result;
}

template <>
ValueType::operator std::vector<bool>() const
{
	std::vector<bool> result;
	if(!isArrayType() || isEmpty()) {
		return result;
	}

#ifdef HAS_OPCUA
	if(isBooleanType()) {
		UA_Boolean *uaArray = (UA_Boolean*)_value.data;
		for(size_t i=0; i<_value.arrayLength; ++i) {
			result.push_back( uaArray[i] );
		}
	}
#else
	if(_value.good()) {
//		return std::stoi(_value.str());
	}
#endif
	return result;
}

template <>
ValueType::operator std::vector<double>() const
{
	std::vector<double> result;
	if(!isArrayType() || isEmpty()) {
		return result;
	}

#ifdef HAS_OPCUA
	if(isDoubleType()) {
		UA_Double *uaArray = (UA_Double*)_value.data;
		for(size_t i=0; i<_value.arrayLength; ++i) {
			result.push_back( uaArray[i] );
		}
	}
#else
	if(_value.good()) {
//		return std::stoi(_value.str());
	}
#endif
	return result;
}

template <>
ValueType::operator std::vector<std::string>() const
{
	std::vector<std::string> result;
	if(!isArrayType() || isEmpty()) {
		return result;
	}

#ifdef HAS_OPCUA
	if(isStringType()) {
		UA_String *uaArray = (UA_String*)_value.data;
		for(size_t i=0; i<_value.arrayLength; ++i) {
			std::string str( (const char*)uaArray[i].data, uaArray[i].length);
			result.push_back( str );
		}
	}
#else
	if(_value.good()) {
//		return std::stoi(_value.str());
	}
#endif
	return result;
}

/**
 * To-string conversion method
 */
std::string ValueType::toString() const {
#ifdef HAS_OPCUA
	std::stringstream s;

	if(isIntegerType()) {
		int d = *this;
		s << d;
	} else if(isBooleanType()) {
		bool b = *this;
		s << b;
	} else if(isDoubleType()) {
		double d = *this;
		s << d;
	} else if(isStringType()) {
		std::string str = *this;
		s << str;
	}

	return s.str();
#else
	return _value.str();
#endif
}

} /* namespace OPCUA */
