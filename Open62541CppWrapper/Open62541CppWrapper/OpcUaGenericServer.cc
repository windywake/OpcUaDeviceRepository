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

#include "OpcUaGenericServer.hh"
#include "OpcUaNodeId.hh"

#include <vector>
#include <sstream>
#include <functional>

#ifdef HAS_OPCUA
#ifndef UA_ENABLE_AMALGAMATION
#include <open62541/server_config_default.h>
#include <open62541/plugin/log_stdout.h>
#endif
#endif // HAS_OPCUA

namespace OPCUA {

#ifdef HAS_OPCUA
// create signal handler
UA_Boolean running = true;
void signal_handler(int sign)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

static std::map<UA_Server*,std::function<void(const std::string&,ValueType&)>> on_read_upcall_bindings;
static std::map<UA_Server*,std::function<void(const std::string&,const ValueType&)>> on_write_upcall_bindings;

static std::map<UA_Server*,std::function<void(const std::string&,const std::vector<ValueType>&,std::vector<ValueType>&)>> method_callback_bindings;


static std::string readBrowseName(UA_Server *server, const UA_NodeId *nodeId)
{
	std::string browseName;
	UA_QualifiedName *outBrowseName = UA_QualifiedName_new();
	UA_StatusCode status = UA_Server_readBrowseName(server, *nodeId, outBrowseName);
	if(status == UA_STATUSCODE_GOOD) {
		browseName = std::string((const char*)outBrowseName->name.data, outBrowseName->name.length);
	}
	UA_QualifiedName_delete(outBrowseName);
	return browseName;
}

static void handle_onRead(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeId, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data)
{
	auto it = on_read_upcall_bindings.find(server);
	if(it != on_read_upcall_bindings.end()) {
		// propagate upcall to the according server object to get a new value
		ValueType value;
		it->second(readBrowseName(server,nodeId), value);
		if(!value.isEmpty()) {
			// there is a new value from the upcall handler, write the value to the server
			UA_Server_writeValue(server, *nodeId, *static_cast<const UA_Variant*>(value));
		}
	}
}

static void handle_onWrite(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeId, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data)
{
	if(sessionId->identifier.numeric != 1)
	{
		auto it = on_write_upcall_bindings.find(server);
		if(it != on_write_upcall_bindings.end()) {
			// call the upcall method related to the according server object
			it->second(readBrowseName(server,nodeId), ValueType(data->value));
		}
	}
}

static UA_StatusCode
genericMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output)
{
	std::vector<ValueType> inputVector(inputSize);
	for(size_t i=0; i<inputSize; ++i) {
		inputVector[i] = input[i];
	}
	std::vector<ValueType> outputVector(outputSize);

	auto it = method_callback_bindings.find(server);
	if(it != method_callback_bindings.end()) {
		NodeId id(*methodId);
		// propagate the method call
		it->second(id.getSimpleName(), inputVector, outputVector);

		std::vector<UA_Variant> outputArguments(outputVector.size());
		for(size_t i=0; i<outputVector.size(); ++i) {
			output[i] = outputVector[i];
		}
	}
	return UA_STATUSCODE_GOOD;
}
#endif // HAS_OPCUA

GenericServer::GenericServer(const std::string &rootObjectName, const unsigned short &namespaceId, const unsigned short &portNr, const bool &activateSignalHandler)
{
	#ifdef HAS_OPCUA

	if(activateSignalHandler == true) {
		// setup signal handlers
		signal(SIGINT, signal_handler);
		signal(SIGTERM, signal_handler);
	}

	// setup the OPC UA server
	config = UA_ServerConfig_new_minimal(portNr, NULL);
	server = UA_Server_new(config);

	on_read_upcall_bindings[server] = std::bind(&GenericServer::handleOnRead, this, std::placeholders::_1, std::placeholders::_2);
	on_write_upcall_bindings[server] = std::bind(&GenericServer::handleOnWrite, this, std::placeholders::_1, std::placeholders::_2);

	method_callback_bindings[server] = std::bind(&GenericServer::handleMethodCall, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	// initialize the root object
	this->createRootObject(rootObjectName, namespaceId);
	#endif // HAS_OPCUA
}

GenericServer::~GenericServer()
{
	#ifdef HAS_OPCUA
	// cleanup server resources
	UA_Server_delete(server);
	UA_ServerConfig_delete(config);
	#endif // HAS_OPCUA
}


void GenericServer::handleOnWrite(const std::string &browseName, const ValueType &value)
{
	// no-op
}
void GenericServer::handleOnRead(const std::string &browseName, ValueType &value)
{
	// no-op
}
void GenericServer::handleMethodCall(const std::string &browseName, const std::vector<ValueType> &inputs, std::vector<ValueType> &outputs)
{
	// no-op
}

int GenericServer::run() {
	#ifdef HAS_OPCUA
	// setup server space
	if(createServerSpace() == true) {
		// execute the blocking server method
		UA_StatusCode retval = UA_Server_run(server, &running);
		return (int)retval;
	}
	#endif // HAS_OPCUA
	return -1;
}

bool GenericServer::createRootObject(const std::string &objectName, const unsigned short &namespaceId)
{
#ifdef HAS_OPCUA
	// Add an object node to the information model
	UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
	oAttr.displayName = UA_LOCALIZEDTEXT_ALLOC("en-US", objectName.c_str());
	UA_QualifiedName browseName = UA_QUALIFIEDNAME_ALLOC(namespaceId, objectName.c_str());
	// create the root-object ID
	rootObjectId = NodeId(objectName, namespaceId);
	const UA_NodeId *rootObjectIdPtr = rootObjectId;
	// add object node
	UA_StatusCode status = UA_Server_addObjectNode(server,
			*rootObjectIdPtr, // use the predefined rootObjectId
			UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),	// parent node is the objects folder
			UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),		// default reference type for objects
			browseName, // browse name
			UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE), // type definition: default base object type
			oAttr, NULL, NULL
	);
	// cleanup allocated memory
	UA_ObjectAttributes_deleteMembers(&oAttr);
	UA_QualifiedName_deleteMembers(&browseName);

	// check and return the status
	if(status == UA_STATUSCODE_GOOD) {
		return true;
	}
#endif // HAS_OPCUA
	return false;
}

bool GenericServer::addVariableNode(
		const std::string &nodeName,
		const OPCUA::ValueType &initialValue,
		const bool &readOnly,
		const unsigned short &namespaceId
)
{
#ifdef HAS_OPCUA
	// create default attribute properties
	UA_VariableAttributes attr = UA_VariableAttributes_default;

	// copy the initial value into the attribute definition
	UA_Variant uaValue = initialValue;
	attr.dataType = uaValue.type->typeId;
	attr.value = uaValue;

	// setup the variable properties
	attr.description = UA_LOCALIZEDTEXT_ALLOC("en-US", nodeName.c_str());
	attr.displayName = UA_LOCALIZEDTEXT_ALLOC("en-US", nodeName.c_str());
	// setup read/write access
	if(readOnly == true) {
		attr.accessLevel = UA_ACCESSLEVELMASK_READ;
	} else {
		attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
	}

	// create a string node id
	NodeId nodeId(nodeName, namespaceId);
	const UA_NodeId *nodeIdPtr = nodeId;

	// create browse name
	UA_QualifiedName browseName = UA_QUALIFIEDNAME_ALLOC(namespaceId, nodeName.c_str());

	const UA_NodeId *rootObjectIdPtr = rootObjectId;

	// add variable definition to the server using rootObjectId as the parent node
	UA_StatusCode status = UA_Server_addVariableNode(server,
				*nodeIdPtr,			// specify the node-id up-front
				*rootObjectIdPtr,   // parent node
				UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), // default reference type
				browseName, // browse name
				UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), // type definition
				attr, NULL, NULL);

	// cleanup allocated memory
	UA_QualifiedName_deleteMembers(&browseName);
	UA_VariableAttributes_deleteMembers(&attr);

	if(status != UA_STATUSCODE_GOOD) {
		return false;
	}

	// set generic callback method references
	UA_ValueCallback callback;
	callback.onRead = handle_onRead;
	callback.onWrite = handle_onWrite;
	status = UA_Server_setVariableNode_valueCallback(server, *nodeIdPtr, callback);

	// check and return the status
	if(status == UA_STATUSCODE_GOOD) {
		return true;
	}
#endif // HAS_OPCUA
		return false;
}

bool GenericServer::addMethodNode(const std::string &methodBrowseName,
			const std::map<std::string,ValueType> &inputArguments,
			const std::map<std::string,ValueType> &outputArguments,
			const unsigned short &namespaceId)
{
#ifdef UA_ENABLE_METHODCALLS
	// create method's input arguments
	UA_Argument uaInputArguments[inputArguments.size()];
	size_t i=0;
	for(auto input = inputArguments.begin(); input != inputArguments.end(); input++) {
		UA_Argument_init(&uaInputArguments[i]);
		uaInputArguments[i].description = UA_LOCALIZEDTEXT_ALLOC("en-US", input->first.c_str());
		uaInputArguments[i].name = UA_STRING_ALLOC(input->first.c_str());
		// get a value copy
		UA_Variant value = input->second;
		uaInputArguments[i].dataType = value.type->typeId;

		if(input->second.isArrayType()) {
			// setup the array dimensions
			uaInputArguments[i].valueRank = 1;
			uaInputArguments[i].arrayDimensionsSize = value.arrayDimensionsSize;
			UA_UInt32_copy(value.arrayDimensions, uaInputArguments[i].arrayDimensions);
		} else {
			// scalar type
			uaInputArguments[i].valueRank = -1;
		}

		// cleanup value copy
		UA_Variant_deleteMembers(&value);

		// increment i
		i++;
	}

	// create method's output arguments
	UA_Argument uaOutputArguments[outputArguments.size()];
	// reset i
	i = 0;
	for(auto output = outputArguments.begin(); output != outputArguments.end(); output++)
	{
		UA_Argument_init(&uaOutputArguments[i]);
		uaOutputArguments[i].description = UA_LOCALIZEDTEXT_ALLOC("en-US", output->first.c_str());
		uaOutputArguments[i].name = UA_STRING_ALLOC(output->first.c_str());
		// get a value copy
		UA_Variant value = output->second;
		uaOutputArguments[i].dataType = value.type->typeId;

		if(output->second.isArrayType()) {
			// setup the array dimensions
			uaOutputArguments[i].valueRank = 1;
			uaOutputArguments[i].arrayDimensionsSize = value.arrayDimensionsSize;
			UA_UInt32_copy(value.arrayDimensions, uaOutputArguments[i].arrayDimensions);
		} else {
			// scalar type
			uaOutputArguments[i].valueRank = -1;
		}

		// cleanup value copy
		UA_Variant_deleteMembers(&value);

		// increment i
		i++;
	}

	// create method's attributes
	UA_MethodAttributes attr = UA_MethodAttributes_default;
	attr.description = UA_LOCALIZEDTEXT_ALLOC("en-US",methodBrowseName.c_str());
	attr.displayName = UA_LOCALIZEDTEXT_ALLOC("en-US",methodBrowseName.c_str());
	attr.executable = true;
	attr.userExecutable = true;

	// create browse name
	UA_QualifiedName browseName = UA_QUALIFIEDNAME_ALLOC(namespaceId, methodBrowseName.c_str());

	// create a string node id
	NodeId nodeId(methodBrowseName, namespaceId);
	const UA_NodeId *nodeIdPtr = nodeId;
	const UA_NodeId *rootObjectIdPtr = rootObjectId;

	// add method to the parent server object
	UA_StatusCode status = UA_Server_addMethodNode(server,
			*nodeIdPtr, // string-based method id
			*rootObjectIdPtr, // parent is the specified root object
			UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), // default reference type
			browseName, // browse name
			attr, &genericMethodCallback, // method attributes and the callback method reference
			inputArguments.size(), uaInputArguments,  // set input arguments
			outputArguments.size(), uaOutputArguments, // set output arguments
			NULL, NULL);

	// cleanup allocated memory
	UA_QualifiedName_deleteMembers(&browseName);
	UA_MethodAttributes_deleteMembers(&attr);

	// cleanup allocated memory for input arguments
	for(size_t i=0; i<inputArguments.size(); ++i)
	{
		UA_Argument_deleteMembers(&uaInputArguments[i]);
	}
	// cleanup allocated memory for output arguments
	for(size_t i=0; i<outputArguments.size(); ++i)
	{
		UA_Argument_deleteMembers(&uaOutputArguments[i]);
	}

	// check and return the status
	if(status == UA_STATUSCODE_GOOD) {
		return true;
	}
#endif // UA_ENABLE_METHODCALLS
	return false;
}

bool GenericServer::createServerSpace()
{
	// no-op
	return true;
}

OPCUA::StatusCode GenericServer::writeVariable(const std::string &nodeName, const OPCUA::ValueType &value, const unsigned short &namespaceId)
{
#ifdef HAS_OPCUA
    NodeId nodeId(nodeName,namespaceId);
    UA_StatusCode status = UA_Server_writeValue(server,
    		*static_cast<const UA_NodeId*>(nodeId), // use const access to prevent memory leaks
			*static_cast<const UA_Variant*>(value)  // use const access to prevent memory leaks
	);
	// check and return the status
	if(status == UA_STATUSCODE_GOOD) {
		return StatusCode::ALL_OK;
	}
#endif // HAS_OPCUA
	return StatusCode::ERROR_COMMUNICATION;
}

} /* namespace OPCUA */
