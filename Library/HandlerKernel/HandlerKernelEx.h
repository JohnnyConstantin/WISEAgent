/****************************************************************************/
/* Copyright(C) : Advantech Technologies, Inc.								*/
/* Create Date  : 2016/08/08 by Scott Chang								    */
/* Modified Date: 2016/08/08 by Scott Chang									*/
/* Abstract     : HandlerKernel API definition								*/
/* Reference    : None														*/
/****************************************************************************/

#ifndef _HANDLER_KERNEL_EX_H_
#define _HANDLER_KERNEL_EX_H_

#include <stdbool.h>
#include "susiaccess_handler_ex_api.h"
#include "IoTMessageGenerate.h"
//#include "ActionMessageGenerate.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#include <windows.h>
#ifndef HANDLERKERNEL_API
	#define HANDLERKERNEL_API WINAPI
#endif
#else
	#define HANDLERKERNEL_API
#endif

typedef enum{
	thr_normal = 0,
	thr_out_of_range,
}threshold_event_type;

typedef enum{
	unknown_cmd = 0,
	//-----------------------------predefined control command (521--600)-----------------------
	hk_get_capability_req = 521,
	hk_get_capability_rep = 522,
	hk_get_sensors_data_req = 523,
	hk_get_sensors_data_rep = 524,
	hk_set_sensors_data_req = 525,
	hk_set_sensors_data_rep = 526,
	hk_set_thr_req = 527,
	hk_set_thr_rep = 528,
	hk_del_thr_req = 529,
	hk_del_thr_rep = 530,
	hk_thr_check_rep = 532,
	hk_auto_upload_req = 533,
	hk_auto_upload_rep = 534,
	hk_get_sensors_data_error_rep = 598,
	hk_error_rep = 600,
	//-----------------------------------------------------------------------------------------
}hk_comm_cmd_t;

#define STATUS_SUCCESS				"Success"
#define STATUS_SETTING				"Setting"
#define STATUS_REQUEST_ERROR		"Request Error"
#define STATUS_NOT_FOUND			"Not Found"
#define STATUS_WRITE				"Write Only"
#define STATUS_READ					"Read Only"
#define STATUS_REQUEST_TIMEOUT		"Request Timeout"
#define STATUS_RESOURCE_LOSE		"Resource Lose"
#define STATUS_FORMAT_ERROR			"Format Error"
#define STATUS_OUTOF_RANGE			"Out of Range"
#define STATUS_SYNTAX_ERROR			"Syntax Error"
#define STATUS_LOCKED				"Resource Locked"
#define STATUS_FAIL					"Fail"
#define STATUS_NOT_IMPLEMENT		"Not Implement"
#define STATUS_SYS_BUSY				"Sys Busy"

#define STATUSCODE_SUCCESS			200
#define STATUSCODE_SETTING			202
#define STATUSCODE_REQUEST_ERROR	400
#define STATUSCODE_NOT_FOUND		404
#define STATUSCODE_WRITE			405
#define STATUSCODE_READ				405
#define STATUSCODE_REQUEST_TIMEOUT	408
#define STATUSCODE_RESOURCE_LOSE	410
#define STATUSCODE_FORMAT_ERROR		415
#define STATUSCODE_OUTOF_RANGE		416
#define STATUSCODE_SYNTAX_ERROR		422
#define STATUSCODE_LOCKED			426
#define STATUSCODE_FAIL				500
#define STATUSCODE_NOT_IMPLEMENT	401
#define STATUSCODE_SYS_BUSY			503

typedef struct get_data{
	char sensorname[256];
	MSG_ATTRIBUTE_T* attr;
	int errcode;
	char errstring[64];
	void* pNode;
	struct get_data *next;
}get_data_t;

typedef struct set_data{
	char sensorname[256];
	MSG_ATTRIBUTE_T* attr;
	int errcode;
	char errstring[64];
	void* pNode;
	attr_type newtype;
	union
	{
		double v;
		bool bv;
		char* sv;
	};
	struct set_data *next;
}set_data_t;

#ifdef __cplusplus
extern "C" {
#endif

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_Initialize
 *  Description: Init any objects or variables of this HandlerKernel
 *  Input : HANDLER_INFO *handler
 *  Output: None
 *  Return:  0 : Success Init Handler
 *          -1 : Fail Init Handler
 * ***************************************************************************************/
void* HANDLERKERNEL_API HandlerKernelEx_Initialize( HANDLER_INFO *handler );

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_Uninitialize
 *  Description: Uninit any objects or variables of this HandlerKernel
 *  Input : None
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_Uninitialize(void* pHandle);

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_SetCapability
 *  Description: Assign the Capability structure and set the bPublish to publish the new capability
 *  Input : MSG_CLASSIFY_T *pCapability
 *			bool bPublish
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_SetCapability(void* pHandle,  MSG_CLASSIFY_T* pCapability, bool bPublish );

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_LockCapability
 *  Description: Lock the Capability structure
 *  Input : 
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_LockCapability(void* pHandle);

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_UnlockCapability
 *  Description: Unlock the Capability structure
 *  Input : 
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_UnlockCapability(void* pHandle );

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_AutoReportStart
 *  Description: Start Auto Report
 *  Input : char *pInQuery
 *  Output: None
 *  Return:  0 : Success
 *          -1 : Fail
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_AutoReportStart(void* pHandle, char *pInQuery);

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_AutoReportStop
 *  Description: Stop Auto Report
 *  Input : char *pInQuery, if *pInQuery = NULL, then stop all upload message.
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail 
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_AutoReportStop(void* pHandle, char *pInQuery);

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_SetAutoReportFilter
 *  Description: Set Auto Report filter to filter out the unused sensor data. 
 *  Input : char *pInQuery
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail 
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_SetAutoReportFilter(void* pHandle, char *pInQuery);

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_SendAutoReportOnce
 *  Description: Send single auto report data. User can used with event trigger.
 *  Input : None
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail 
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_SendAutoReportOnce(void* pHandle);

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_LiveReportStart
 *  Description: Start Live Report (auto upload)
 *  Input : int replyID
 *			char *pInQuery
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail 
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_LiveReportStart(void* pHandle, int replyID, char *pInQuery);

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_ParseRecvCMDWithSessionID
 *  Description: Parse received command to command ID
 *  Input : char *pInQuery
 *  Output: int * cmdID
 *			char * sessionID
 *  Return:  0 : Success 
 *          -1 : Fail 
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_ParseRecvCMDWithSessionID(char *pInQuery, int * cmdID, char * sessionID);

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_SetThreshold
 *  Description: Set threshold rule
 *  Input : int replyID
 *			char *pInQuery
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_SetThreshold(void* pHandle, int replyID, char *pInQuery);

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_DeleteAllThreshold
 *  Description: Delete threshold rule
 *  Input : int replyID
 *			char *pInQuery
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_DeleteAllThreshold(void* pHandle, int replyID);

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_StartThresholdCheck
 *  Description: Start threshold rule check thread
 *  Input : None
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_StartThresholdCheck(void* pHandle);

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_StopThresholdCheck
 *  Description: Stop threshold rule check thread
 *  Input : None
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_StopThresholdCheck(void* pHandle);

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_SetThresholdTrigger
 *  Description: register the threshold check event callback function.
 *  Input : on_trigger - a callback function in the following form:
 *               void callback(HANDLE const handler, threshold_event_type tyep, char* sensorname, double value, MSG_ATTRIBUTE_T* attr, void *pRev)
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail
 * Callback Parameters:
 *  type -  threshold trigger type
 *  sensorname -  triggered sensor uri
 *  value - triggered value
 *  attr - triggered object
 *  pRev - preserved.
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_SetThresholdTrigger(void* pHandle, void (*on_triggered)(bool isnormal,
													char* sensorname, double value, MSG_ATTRIBUTE_T* attr,
													void *pRev));

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_GetSensorData
 *  Description: Get Sensor Data
 *  Input : int replyID
 *			char *pInQuery
 *			on_get_sensor - a callback function in the following form:
 *               bool (*on_get_sensor)(Handler_info* handler, char* sensorname, double* value, MSG_ATTRIBUTE_T* attr, void *pRev)
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail
 * Callback Parameters:
 *  sensorname -  sensor uri
 *  attr - target object
 *  pRev - preserved.
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_GetSensorData(void* pHandle, int replyID, char* sessionID, char *pInQuery, bool (*on_get_sensor)(get_data_t* getlist, void *pRev));

/* **************************************************************************************
 *  Function Name: HandlerKernelEx_SetSensorData
 *  Description: Set Sensor Data
 *  Input : int replyID
 *			char *pInQuery
 *			on_set_sensor - a callback function in the following form:
 *               bool (*on_get_sensor)(Handler_info* handler, char* sensorname, double value, MSG_ATTRIBUTE_T* attr, void *pRev)
 *  Output: None
 *  Return:  0 : Success 
 *          -1 : Fail
 * Callback Parameters:
 *  sensorname -  sensor uri
 *  value - received value
 *  attr - target object
 *  pRev - preserved.
 * ***************************************************************************************/
int HANDLERKERNEL_API HandlerKernelEx_SetSensorData(void* pHandle, int replyID, char* sessionID, char *pInQuery, bool (*on_set_sensor)(set_data_t* setlist, void *pRev));

#ifdef __cplusplus
}
#endif

#endif