/**
 * Emotiv Development Kit (EDK) API
 * Copyright (c) 2009 Emotiv Systems, Inc.
 *
 *
 * EDK1.h file modified by Francesco Tenore
 * Copyright © May 2010 The Johns Hopkins University Applied Physics Laboratory (JHU/APL).  
 * All Rights Reserved.
 * JHU/APL PROVIDES THIS SOFTWARE "AS IS" WITHOUT WARRANTY OF ANY KIND AND IS NOT LIABLE 
 * FOR ANY DAMAGES OF ANY KIND ARISING FROM THE USE OF THIS SOFTWARE.
 *
 * The main interface that allows interactions between external programs and the Emotiv detection engine.
 *
 * None of the API functions are thread-safe.
 *
 * This header file is designed to be includable under C and C++ environment.
 *
 */


#ifndef EDK1_H
#define EDK1_H
#include "edkErrorCode.h"
#include "EmoStateDLL.h"
#import "EmoStateDLL.h"

#ifndef EDK_STATIC_LIB

#ifdef EDK_EXPORTS
#ifdef _WIN32
#define EDK_API __declspec(dllexport)
#else
#define EDK_API __declspec(dllimport)
#endif
#else
#define EDK_API
#endif

#else

#define EDK_API extern "C" __declspec(dllexport)

#endif

extern "C" __declspec(dllexport)

// From EmoStateDLL.h
	typedef enum {
		EE_CHAN_CMS = 0, EE_CHAN_DRL, EE_CHAN_FP1, EE_CHAN_AF3, EE_CHAN_F7, 
		EE_CHAN_F3, EE_CHAN_FC5, EE_CHAN_T7, EE_CHAN_P7, EE_CHAN_O1,
		EE_CHAN_O2, EE_CHAN_P8, EE_CHAN_T8, EE_CHAN_FC6, EE_CHAN_F4,
		EE_CHAN_F8, EE_CHAN_AF4, EE_CHAN_FP2,
	} EE_InputChannels_enum ;
	typedef enum EE_InputChannels_enum EE_InputChannels_t ;

// From EmoStateDLL.h
	typedef enum {
		EXP_NEUTRAL			= 0x0001,
		EXP_BLINK			= 0x0002,
		EXP_WINK_LEFT		= 0x0004,
		EXP_WINK_RIGHT		= 0x0008,
        EXP_HORIEYE			= 0x0010,
		EXP_EYEBROW			= 0x0020,
		EXP_FURROW			= 0x0040,
        EXP_SMILE			= 0x0080,
		EXP_CLENCH			= 0x0100,
		EXP_LAUGH			= 0x0200,
		EXP_SMIRK_LEFT		= 0x0400,
		EXP_SMIRK_RIGHT		= 0x0800,
	}  EE_ExpressivAlgo_enum ;
	typedef enum EE_ExpressivAlgo_enum EE_ExpressivAlgo_t ;

// From EmoStateDLL.h
		typedef enum {

		COG_NEUTRAL						= 0x0001,
		COG_PUSH						= 0x0002,
		COG_PULL						= 0x0004,
		COG_LIFT						= 0x0008,
		COG_DROP						= 0x0010,
		COG_LEFT						= 0x0020,
		COG_RIGHT						= 0x0040,
		COG_ROTATE_LEFT					= 0x0080,
		COG_ROTATE_RIGHT				= 0x0100,
		COG_ROTATE_CLOCKWISE			= 0x0200,
		COG_ROTATE_COUNTER_CLOCKWISE	= 0x0400,
		COG_ROTATE_FORWARDS				= 0x0800,
		COG_ROTATE_REVERSE				= 0x1000,
		COG_DISAPPEAR					= 0x2000,

	} EE_CognitivAction_enum ;
	typedef enum EE_CognitivAction_enum EE_CognitivAction_t ;

// From EmoStateDLL.h
	typedef enum {

		EE_EXPRESSIV = 0, EE_AFFECTIV, EE_COGNITIV,

	} EE_EmotivSuite_enum ;
	typedef enum EE_EmotivSuite_enum EE_EmotivSuite_t ;

	/**
	 * Affectiv emotional type enumerator
	 */
	typedef enum  {

		AFF_EXCITEMENT			= 0x0001,
		AFF_MEDITATION			= 0x0002,
		AFF_FRUSTRATION			= 0x0004,
		AFF_ENGAGEMENT_BOREDOM	= 0x0008

	} EE_AffectivAlgo_enum;
	typedef enum EE_AffectivAlgo_enum  EE_AffectivAlgo_t;









	//! Expressiv Suite threshold type enumerator
	typedef enum {
		EXP_SENSITIVITY,
	} EE_ExpressivThreshold_enum, EE_ExpressivThreshold_t;
	

	//! Expressiv Suite training control enumerator
	typedef enum {
		EXP_NONE = 0, EXP_START, EXP_ACCEPT, EXP_REJECT, EXP_ERASE, EXP_RESET,
	} EE_ExpressivTrainingControl_enum,EE_ExpressivTrainingControl_t ;
	//typedef enum EE_ExpressivTrainingControl_enum EE_ExpressivTrainingControl_t ;



	//! Expressiv Suite signature type enumerator
	typedef enum {
		EXP_SIG_UNIVERSAL = 0, EXP_SIG_TRAINED,
	} EE_ExpressivSignature_enum, ;
	typedef enum EE_ExpressivSignature_enum EE_ExpressivSignature_t ;
	

	 //! Cognitiv Suite training control enumerator
	typedef	enum {
		COG_NONE = 0, COG_START, COG_ACCEPT, COG_REJECT, COG_ERASE, COG_RESET,
	} EE_CognitivTrainingControl_enum EE_CognitivTrainingControl_t;

	//! Handle to internal EmoState structure allocated by EE_EmoStateCreate()
	typedef void*         EmoStateHandle;

	//! Handle to internal event structure allocated by EE_EmoEngineEventCreate()
	typedef void*         EmoEngineEventHandle;

	//! Handle to internal event structure allocated by EE_OptimizationParamCreate()
	typedef void*         OptimizationParamHandle;

	typedef void*		  DataHandle;

	//! EmoEngine event types
	typedef enum {
		EE_UnknownEvent		= 0x0000,
		EE_EmulatorError	= 0x0001,
		EE_ReservedEvent	= 0x0002,
		EE_UserAdded		= 0x0010,
		EE_UserRemoved		= 0x0020,
		EE_EmoStateUpdated	= 0x0040,
		EE_ProfileEvent		= 0x0080,
		EE_CognitivEvent	= 0x0100,
		EE_ExpressivEvent	= 0x0200,
		EE_InternalStateChanged = 0x0400,
		EE_AllEvent			= EE_UserAdded | EE_UserRemoved | EE_EmoStateUpdated | EE_ProfileEvent |
							  EE_CognitivEvent | EE_ExpressivEvent | EE_InternalStateChanged,
	} EE_Event_enum EE_Event_t;


	//! Expressiv-specific event types
	enum EE_ExpressivEvent_enum {
		EE_ExpressivNoEvent = 0, EE_ExpressivTrainingStarted, EE_ExpressivTrainingSucceeded,
		EE_ExpressivTrainingFailed, EE_ExpressivTrainingCompleted, EE_ExpressivTrainingDataErased,
		EE_ExpressivTrainingRejected, EE_ExpressivTrainingReset
	} ;
	typedef enum EE_ExpressivEvent_enum EE_ExpressivEvent_t;
	
	//! Cognitiv-specific event types
	enum EE_CognitivEvent_enum {
		EE_CognitivNoEvent = 0, EE_CognitivTrainingStarted, EE_CognitivTrainingSucceeded,
		EE_CognitivTrainingFailed, EE_CognitivTrainingCompleted, EE_CognitivTrainingDataErased,
		EE_CognitivTrainingRejected, EE_CognitivTrainingReset,
		EE_CognitivAutoSamplingNeutralCompleted, EE_CognitivSignatureUpdated
	} ;
	typedef enum EE_CognitivEvent_enum EE_CognitivEvent_t;

	enum EE_DataChannels_enum {
		ED_COUNTER = 0, ED_INTERPOLATED, ED_RAW_CQ,
		ED_AF3, ED_F7, ED_F3, ED_FC5, ED_T7, 
		ED_P7, ED_O1, ED_O2, ED_P8, ED_T8, 
		ED_FC6, ED_F4, ED_F8, ED_AF4, ED_GYROX, 
		ED_GYROY, ED_TIMESTAMP, ED_ES_TIMESTAMP, ED_FUNC_ID, ED_FUNC_VALUE, ED_MARKER, 
		ED_SYNC_SIGNAL
	} ;
	typedef enum EE_DataChannels_enum EE_DataChannel_t;

	//! Input sensor description
	typedef struct {
		EE_InputChannels_t channelId;  // logical channel id
		int                fExists;    // does this sensor exist on this headset model
		const char*        pszLabel;   // text label identifying this sensor
		double             xLoc;       // x coordinate from center of head towards nose
		double             yLoc;       // y coordinate from center of head towards ears
		double             zLoc;       // z coordinate from center of head toward top of skull
	} InputSensorDescriptor_struct ;
	typedef enum InputSensorDescriptor_struct InputSensorDescriptor_t ;

	//! Initializes the connection to EmoEngine. This function should be called at the beginning of programs that make use of EmoEngine, most probably in initialization routine or constructor.
	/*!	
		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if a connection is established

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_EngineConnect(const char* strDevID = "Emotiv Systems-5");

	
	//! Initializes the connection to a remote instance of EmoEngine.
	/*!
		Blocking call

		\param szHost - A null-terminated string identifying the hostname or IP address of the remote EmoEngine server
		\param port - The port number of the remote EmoEngine server
					- If connecting to the Emotiv Control Panel, use port 3008
					- If connecting to the EmoComposer, use port 1726
	
		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if a connection is established

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_EngineRemoteConnect(const char* szHost, unsigned short port);

	
	//! Terminates the connection to EmoEngine. This function should be called at the end of programs which make use of EmoEngine, most probably in clean up routine or destructor.
	/*!
		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if disconnection is achieved

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_EngineDisconnect();


	//! Controls the output of logging information from EmoEngine (which is off by default). This should only be enabled if instructed to do so by Emotiv developer support for the purposes of collecting diagnostic information.
	/*!
	    \param szFilename - The path of the logfile
		\param fEnable - If non-zero, then diagnostic information will be written to logfile.
		               - If zero, then all diagnostic information is suppressed (default).
	    \param nReserved - Reserved for future use.

	    \return EDK_ERROR_CODE
		        - EDK_ERROR_CODE = EDK_OK if the command succeeded
	*/
	EDK_API int
		EE_EnableDiagnostics(const char* szFilename, int fEnable, int nReserved);

	
	//! Returns a handle to memory that can hold an EmoEngine event. This handle can be reused by the caller to retrieve subsequent events.
	/*!
		\return EmoEngineEventHandle
	*/
	EDK_API EmoEngineEventHandle
		EE_EmoEngineEventCreate();


	//! Returns a handle to memory that can hold a profile byte stream. This handle can be reused by the caller to retrieve subsequent profile bytes.
	/*!
		\return EmoEngineEventHandle
	*/
	EDK_API EmoEngineEventHandle
		EE_ProfileEventCreate();

	
	//! Frees memory referenced by an event handle.
	/*!
		\param hEvent - a handle returned by EE_EmoEngineEventCreate() or EE_ProfileEventCreate()
	*/
	EDK_API void
		EE_EmoEngineEventFree(EmoEngineEventHandle hEvent);

	
	//! Returns a handle to memory that can store an EmoState. This handle can be reused by the caller to retrieve subsequent EmoStates.
	/*!
		\return EmoStateHandle
	*/
	EDK_API EmoStateHandle
		EE_EmoStateCreate();

	
	//! Frees memory referenced by an EmoState handle.
	/*!
		\param hState - a handle returned by EE_EmoStateCreate()
	*/
	EDK_API void
		EE_EmoStateFree(EmoStateHandle hState);


	//! Returns the event type for an event already retrieved using EE_EngineGetNextEvent.
	/*!
		\param hEvent - a handle returned by EE_EmoEngineEventCreate()
	
		\return EE_Event_t
	*/
	EDK_API EE_Event_t
		EE_EmoEngineEventGetType(EmoEngineEventHandle hEvent);

	
	//! Returns the Cognitiv-specific event type for an EE_CognitivEvent event already retrieved using EE_EngineGetNextEvent.
	/*!
		\param hEvent - a handle returned by EE_EmoEngineEventCreate()
	
		\return EE_CognitivEvent_t
	*/
	EDK_API EE_CognitivEvent_t
		EE_CognitivEventGetType(EmoEngineEventHandle hEvent);


	//! Returns the Expressiv-specific event type for an EE_ExpressivEvent event already retrieved using EE_EngineGetNextEvent.
	/*!
		\param hEvent - a handle returned by EE_EmoEngineEventCreate()
	
		\return EE_ExpressivEvent_t
	*/
	EDK_API EE_ExpressivEvent_t
		EE_ExpressivEventGetType(EmoEngineEventHandle hEvent);
	

	//! Retrieves the user ID for EE_UserAdded and EE_UserRemoved events.
	/*!
		\param hEvent - a handle returned by EE_EmoEngineEventCreate()
		\param pUserIdOut - receives the user ID associated with the current event
	
		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful.

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_EmoEngineEventGetUserId(EmoEngineEventHandle hEvent, unsigned int *pUserIdOut);

	
	//! Copies an EmoState returned with a EE_EmoStateUpdate event to memory referenced by an EmoStateHandle.
	/*!
		\param hEvent - a handle returned by EE_EmoEngineEventCreate() and populated with EE_EmoEngineGetNextEvent()
		\param hEmoState - a handle returned by EE_EmoStateCreate
	
		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful.

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_EmoEngineEventGetEmoState(EmoEngineEventHandle hEvent, EmoStateHandle hEmoState);
	

	//! Retrieves the next EmoEngine event
	/*!
		Non-blocking call

		\param hEvent - a handle returned by EE_EmoEngineEventCreate()

		\return EDK_ERROR_CODE
                <ul>
		        <li> EDK_ERROR_CODE = EDK_OK if a new event has been retrieved
				<li> EDK_ERROR_CODE = EDK_NO_EVENT if no new events have been generated by EmoEngine
				</ul>
		
		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_EngineGetNextEvent(EmoEngineEventHandle hEvent);

	
	//! Clear a specific EmoEngine event type or all events currently inside the event queue. Event flags can be combined together as one argument except EE_UnknownEvent and EE_EmulatorError.
	/*!
		\param eventTypes - EmoEngine event type (EE_Event_t), multiple events can be combined such as (EE_UserAdded | EE_UserRemoved)

		\return EDK_ERROR_CODE
                <ul>
		        <li> EDK_ERROR_CODE = EDK_OK if the events have been cleared from the queue
				<li> EDK_ERROR_CODE = EDK_INVALID_PARAMETER if input event types are invalid
				</ul>
		
		\sa EE_Event_t, edkErrorCode.h
	*/
	EDK_API int
		EE_EngineClearEventQueue(int eventTypes);

	
	//! Retrieves number of active users connected to the EmoEngine.
	/*!
		\param pNumUserOut - receives number of users

		\return EDK_ERROR_CODE
		        - EDK_ERROR_CODE = EDK_OK if successful.

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_EngineGetNumUser(unsigned int* pNumUserOut);


	//! Sets the player number displayed on the physical input device (currently the USB Dongle) that corresponds to the specified user
	/*!
		\param userId - EmoEngine user ID
		\param playerNum - application assigned player number displayed on input device hardware (must be in the range 1-4)
		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_SetHardwarePlayerDisplay(unsigned int userId, unsigned int playerNum);


	//! Loads an EmoEngine profile for the specified user.  
	/*!
		\param userId - user ID
		\param profileBuffer - pointer to buffer containing a serialized user profile previously returned from EmoEngine.
		\param length - buffer size (number of bytes)

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE if the function succeeds in loading this profile

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_SetUserProfile(unsigned int userId, const unsigned char profileBuffer[], unsigned int length);


	//! Returns user profile data in a synchronous manner.
	/*!
	     Fills in the event referred to by hEvent with an EE_ProfileEvent event
		 that contains the profile data for the specified user.

		 \param userId - user ID
		 \param hEvent - a handle returned by EE_EmoEngineEventCreate()

		 \return EDK_ERROR_CODE
		         - EDK_ERROR_CODE = EDK_OK if successful

		 \sa edkErrorCode.h
	*/
	EDK_API int
		EE_GetUserProfile(unsigned int userId, EmoEngineEventHandle hEvent);


	//! Returns a serialized user profile for a default user in a synchronous manner.
	/*!
	    Fills in the event referred to by hEvent with an EE_ProfileEvent event
		that contains the profile data for the default user

		 \param hEvent - a handle returned by EE_EmoEngineEventCreate()

		 \return EDK_ERROR_CODE
		         - EDK_ERROR_CODE = EDK_OK if successful

		 \sa edkErrorCode.h
	*/
	EDK_API int
		EE_GetBaseProfile(EmoEngineEventHandle hEvent);
	

	//! Returns the number of bytes required to store a serialized version of the requested user profile.
	/*!	
		\param hEvt - an EmoEngineEventHandle of type EE_ProfileEvent
		\param pProfileSizeOut - receives number of bytes required by the profile

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_GetUserProfileSize(EmoEngineEventHandle hEvt, unsigned int* pProfileSizeOut);

	
	//! Copies a serialized version of the requested user profile into the caller's buffer.
	/*!		
		\param hEvt - an EmoEngineEventHandle returned in a EE_ProfileEvent event
		\param destBuffer - pointer to a destination buffer
		\param length - the size of the destination buffer in bytes

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_GetUserProfileBytes(EmoEngineEventHandle hEvt, unsigned char destBuffer[], unsigned int length);

	//!  Loads a user profile from disk and assigns it to the specified user
	/*!		
		\param userID - a valid user ID
		\param szInputFilename - platform-dependent filesystem path of saved user profile

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_LoadUserProfile(unsigned int userID, const char* szInputFilename);

	//!  Saves a user profile for specified user to disk
	/*!		
		\param userID - a valid user ID
		\param szOutputFilename - platform-dependent filesystem path for output file

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_SaveUserProfile(unsigned int userID, const char* szOutputFilename);

	//! Set threshold for Expressiv algorithms
	/*!
		\param userId - user ID
		\param algoName - Expressiv algorithm type
		\param thresholdName - Expressiv threshold type
		\param value - threshold value (min: 0 max: 1000)

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h, EE_ExpressivAlgo_t, EE_ExpressivThreshold_t
	*/
	EDK_API int
		EE_ExpressivSetThreshold(unsigned int userId, EE_ExpressivAlgo_t algoName, EE_ExpressivThreshold_t thresholdName, int value);


	//! Get threshold from Expressiv algorithms
	/*!
		\param userId - user ID
		\param algoName - Expressiv algorithm type
		\param thresholdName - Expressiv threshold type
		\param pValueOut - receives threshold value

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h, EE_ExpressivAlgo_t, EE_ExpressivThreshold_t
	*/
	EDK_API int
		EE_ExpressivGetThreshold(unsigned int userId, EE_ExpressivAlgo_t algoName, EE_ExpressivThreshold_t thresholdName, int *pValueOut);


	//! Set the current facial expression for Expressiv training
	/*!
		Blocking call

		\param userId - user ID
		\param action - which facial expression would like to be trained

		\return EDK_ERROR_CODE - current status of EmoEngine. If the query is successful, EDK_ERROR_CODE = OK.

		\sa edkErrorCode.h, EE_ExpressivAlgo_t
	*/
	EDK_API int 
		EE_ExpressivSetTrainingAction(unsigned int userId, EE_ExpressivAlgo_t action);


	//! Set the control flag for Expressiv training
	/*!
		Blocking call

		\param userId - user ID
		\param control - pre-defined control command

		\return EDK_ERROR_CODE - current status of EmoEngine. If the query is successful, EDK_ERROR_CODE = OK.

		\sa edkErrorCode.h, EE_ExpressivTrainingControl_t
	*/
	EDK_API int 
		EE_ExpressivSetTrainingControl(unsigned int userId, EE_ExpressivTrainingControl_t control);


	//! Gets the facial expression currently selected for Expressiv training
	/*!
		Blocking call

		\param userId - user ID
		\param pActionOut - receives facial expression currently selected for training

		\return EDK_ERROR_CODE - current status of EmoEngine. If the query is successful, EDK_ERROR_CODE = OK.

		\sa EDK_ERROR_CODE, EE_ExpressivAlgo_t
	*/
	EDK_API int 
		EE_ExpressivGetTrainingAction(unsigned int userId, EE_ExpressivAlgo_t* pActionOut);

	
	//! Return the duration of a Expressiv training session
	/*!
		\param userId - user ID
		\param pTrainingTimeOut - receive the training time in ms

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int 
		EE_ExpressivGetTrainingTime(unsigned int userId, unsigned int* pTrainingTimeOut);


	//! Gets a list of the actions that have been trained by the user
	/*!
		Blocking call

		\param userId - user ID
		\param pTrainedActionsOut - receives a bit vector composed of EE_ExpressivAlgo_t contants

		\return EDK_ERROR_CODE - current status of EmoEngine. If the query is successful, EDK_ERROR_CODE = OK.

		\sa EDK_ERROR_CODE, EE_ExpressivAlgo_t
	*/
    EDK_API int
        EE_ExpressivGetTrainedSignatureActions(unsigned int userId, unsigned long* pTrainedActionsOut);


	//! Gets a flag indicating if the user has trained sufficient actions to activate a trained signature
	/*!
        *pfAvailableOut will be set to 1 if the user has trained EXP_NEUTRAL and at least
        one other Expressiv action.  Otherwise, *pfAvailableOut == 0.

		Blocking call

		\param userId - user ID
		\param pfAvailableOut - receives an int that is non-zero if a trained signature can be activated

		\return EDK_ERROR_CODE - current status of EmoEngine. If the query is successful, EDK_ERROR_CODE = OK.

		\sa EDK_ERROR_CODE
	*/
    EDK_API int
		EE_ExpressivGetTrainedSignatureAvailable(unsigned int userId, int* pfAvailableOut);

	//! Configures the Expressiv suite to use either the built-in, universal signature or a personal, trained signature
	/*!
        Note: Expressiv defaults to use its universal signature.  This function will fail if EE_ExpressivGetTrainedSignatureAvailable returns false.

		Blocking call

		\param userId - user ID
		\param sigType - signature type to use

		\return EDK_ERROR_CODE - current status of EmoEngine. If the query is successful, EDK_ERROR_CODE = OK.

		\sa EDK_ERROR_CODE, EE_ExpressivSignature_t
	*/
	EDK_API int 
		EE_ExpressivSetSignatureType(unsigned int userId, EE_ExpressivSignature_t sigType);

	//! Indicates whether the Expressiv suite is currently using either the built-in, universal signature or a trained signature
	/*!
		Blocking call

		\param userId - user ID
		\param pSigTypeOut - receives the signature type currently in use

		\return EDK_ERROR_CODE - current status of EmoEngine. If the query is successful, EDK_ERROR_CODE = OK.

		\sa EDK_ERROR_CODE, EE_ExpressivSignature_t
	*/
	EDK_API int 
		EE_ExpressivGetSignatureType(unsigned int userId, EE_ExpressivSignature_t* pSigTypeOut);




	//! Set the current Cognitiv active action types
	/*!
		\param userId - user ID
		\param activeActions - a bit vector composed of EE_CognitivAction_t contants

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h, EE_CognitivAction_t
	*/
	EDK_API int
		EE_CognitivSetActiveActions(unsigned int userId, unsigned long activeActions);

	
	//! Get the current Cognitiv active action types
	/*!
		\param userId - user ID
		\param pActiveActionsOut - receive a bit vector composed of EE_CognitivAction_t contants

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h, EE_CognitivAction_t
	*/
	EDK_API int
		EE_CognitivGetActiveActions(unsigned int userId, unsigned long* pActiveActionsOut);

	
	//! Return the duration of a Cognitiv training session
	/*!
		\param userId - user ID
		\param pTrainingTimeOut - receive the training time in ms

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int 
		EE_CognitivGetTrainingTime(unsigned int userId, unsigned int* pTrainingTimeOut);

	
	//! Set the training control flag for Cognitiv training
	/*!
		\param userId - user ID
		\param control - pre-defined Cognitiv training control

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h, EE_CognitivTrainingControl_t
	*/
	EDK_API int 
		EE_CognitivSetTrainingControl(unsigned int userId, EE_CognitivTrainingControl_t control);

	
	//! Set the type of Cognitiv action to be trained
	/*!
		\param userId - user ID
		\param action - which action would like to be trained

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h, EE_CognitivAction_t
	*/
	EDK_API int 
		EE_CognitivSetTrainingAction(unsigned int userId, EE_CognitivAction_t action);


	//! Get the type of Cognitiv action currently selected for training
	/*!
		\param userId - user ID
		\param pActionOut - action that is currently selected for training

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h, EE_CognitivAction_t
	*/
	EDK_API int 
		EE_CognitivGetTrainingAction(unsigned int userId, EE_CognitivAction_t* pActionOut);


	//! Gets a list of the Cognitiv actions that have been trained by the user
	/*!
		Blocking call

		\param userId - user ID
		\param pTrainedActionsOut - receives a bit vector composed of EE_CognitivAction_t contants

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h, EE_CognitivAction_t
	*/
    EDK_API int
        EE_CognitivGetTrainedSignatureActions(unsigned int userId, unsigned long* pTrainedActionsOut);
	
	
	//! Gets the current overall skill rating of the user in Cognitiv
	/*!
		Blocking call

		\param userId - user ID
		\param pOverallSkillRatingOut - receives the overall skill rating [from 0.0 to 1.0]

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
    EDK_API int
        EE_CognitivGetOverallSkillRating(unsigned int userId, float* pOverallSkillRatingOut);


	//! Gets the current skill rating for particular Cognitiv actions of the user
	/*!
		Blocking call

		\param userId - user ID
		\param action - a particular action of EE_CognitivAction_t contant
		\param pActionSkillRatingOut - receives the action skill rating [from 0.0 to 1.0]

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h, EE_CognitivAction_t
	*/
    EDK_API int
        EE_CognitivGetActionSkillRating(unsigned int userId, EE_CognitivAction_t action, float* pActionSkillRatingOut);

	
	//! Set the overall sensitivity for all Cognitiv actions
	/*!
		\param userId - user ID
		\param level - sensitivity level of all actions (lowest: 1, highest: 7)

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int 
		EE_CognitivSetActivationLevel(unsigned int userId, int level);

	
	//! Set the sensitivity of Cognitiv actions
	/*!
		\param userId - user ID
		\param action1Sensitivity - sensitivity of action 1 (min: 1, max: 10)
		\param action2Sensitivity - sensitivity of action 2 (min: 1, max: 10)
		\param action3Sensitivity - sensitivity of action 3 (min: 1, max: 10)
		\param action4Sensitivity - sensitivity of action 4 (min: 1, max: 10)

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int 
		EE_CognitivSetActionSensitivity(unsigned int userId,
										int action1Sensitivity, int action2Sensitivity,
										int action3Sensitivity, int action4Sensitivity);

	
	//! Get the overall sensitivity for all Cognitiv actions
	/*!
		\param userId - user ID
		\param pLevelOut - sensitivity level of all actions (min: 1, max: 10)

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int 
		EE_CognitivGetActivationLevel(unsigned int userId, int *pLevelOut);

	
	//! Query the sensitivity of Cognitiv actions
	/*!
		\param userId - user ID
		\param pAction1SensitivityOut - sensitivity of action 1
		\param pAction2SensitivityOut - sensitivity of action 2
		\param pAction3SensitivityOut - sensitivity of action 3
		\param pAction4SensitivityOut - sensitivity of action 4

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int 
		EE_CognitivGetActionSensitivity(unsigned int userId,
										int* pAction1SensitivityOut, int* pAction2SensitivityOut,
										int* pAction3SensitivityOut, int* pAction4SensitivityOut);

	
	//! Start the sampling of Neutral state in Cognitiv
	/*!
		\param userId - user ID

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_CognitivStartSamplingNeutral(unsigned int userId);

	
	//! Stop the sampling of Neutral state in Cognitiv
	/*!
		\param userId - user ID

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_CognitivStopSamplingNeutral(unsigned int userId);

	
	//! Enable or disable signature caching in Cognitiv
	/*!
		\param userId  - user ID
		\param enabled - flag to set status of caching (1: enable, 0: disable)

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_CognitivSetSignatureCaching(unsigned int userId, unsigned int enabled);


	//! Query the status of signature caching in Cognitiv
	/*!
		\param userId  - user ID
		\param pEnabledOut - flag to get status of caching (1: enable, 0: disable)

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_CognitivGetSignatureCaching(unsigned int userId, unsigned int* pEnabledOut);


	//! Set the cache size for the signature caching in Cognitiv
	/*!
		\param userId - user ID
		\param size   - number of signatures to be kept in the cache (0: unlimited)

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_CognitivSetSignatureCacheSize(unsigned int userId, unsigned int size);


	//! Get the current cache size for the signature caching in Cognitiv
	/*!
		\param userId - user ID
		\param pSizeOut - number of signatures to be kept in the cache (0: unlimited)

		\return EDK_ERROR_CODE
				- EDK_ERROR_CODE = EDK_OK if successful

		\sa edkErrorCode.h
	*/
	EDK_API int
		EE_CognitivGetSignatureCacheSize(unsigned int userId, unsigned int* pSizeOut);


	//! Returns a struct containing details about the specified EEG channel's headset 
    /*!
        \param channelId - channel identifier (see EmoStateDll.h)
        \param pDescriptorOut - provides detailed sensor location and other info

        \return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful

        \sa EmoStateDll.h, edkErrorCode.h
	*/
	EDK_API int
		EE_HeadsetGetSensorDetails(EE_InputChannels_t channelId, InputSensorDescriptor_t* pDescriptorOut);


	//! Returns the current hardware version of the headset and dongle for a particular user
    /*!
        \param userId - user ID for query
		\param pHwVersionOut - hardware version for the user headset/dongle pair. hiword is headset version, loword is dongle version.

        \return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful

        \sa EmoStateDll.h, edkErrorCode.h
	*/
	EDK_API int
		EE_HardwareGetVersion(unsigned int userId, unsigned long* pHwVersionOut);

	//! Returns the current version of the Emotiv SDK software
    /*!
		\param pszVersionOut - SDK software version in X.X.X.X format. Note: current beta releases have a major version of 0.
		\param nVersionChars - Length of char buffer pointed to by pszVersion argument.
		\param pBuildNumOut  - Build number.  Unique for each release.

        \return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful

        \sa edkErrorCode.h
	*/
	EDK_API int
		EE_SoftwareGetVersion(char* pszVersionOut, unsigned int nVersionChars, unsigned long* pBuildNumOut);

	//! Returns the delta of the movement of the gyro since the previous call for a particular user
	/*!
		\param userId - user ID for query
		\param pXOut  - horizontal displacement
		\param pYOut  - vertical displacment

		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful

        \sa EmoStateDll.h
        \sa edkErrorCode.h
	*/
	EDK_API int
		EE_HeadsetGetGyroDelta(unsigned int userId, int* pXOut, int* pYOut);

	//! Re-zero the gyro for a particular user
	/*!
		\param userId - user ID for query

		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful

        \sa EmoStateDll.h
        \sa edkErrorCode.h
	*/
	EDK_API int
		EE_HeadsetGyroRezero(unsigned int userId);

	//! Returns a handle to memory that can hold an optimization paramaeter which is used to configure the behaviour of optimization
	/*!
		\return OptimizationParamHandle
	*/
	EDK_API OptimizationParamHandle
		EE_OptimizationParamCreate();

	//! Frees memory referenced by an optimization parameter handle
	/*!
		\param hParam - a handle returned by EE_OptimizationParamCreate()
	*/
	EDK_API void
		EE_OptimizationParamFree(OptimizationParamHandle hParam);

	//! Enable optimization. EmoEngine will try to optimize its performance according to the information passed in with optimization parameter. EmoEngine guarantees the correctness of the results of vital algorithms. For algorithms that are not vital, results are undefined.
	/*!
		\param hParam - a handle returned by EE_OptimizationParamCreate()
		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful
	*/
	EDK_API int
		EE_OptimizationEnable(OptimizationParamHandle hParam);

	//! Determine whether optimization is on
	/*!
		\param pEnabledOut - receives information about whether optimization is on
		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful
	*/
	EDK_API int
		EE_OptimizationIsEnabled(bool* pEnabledOut);

	//! Disable optimization
	/*!
		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful
	*/
	EDK_API int
		EE_OptimizationDisable();

	//! Get optimization parameter.  If optimization is not enabled (this can be checked with EE_OptimmizationIsEnabled) then the results attached to the hParam parameter are undefined.
	/*!
		\param hParam - a handle returned by EE_OptimizationParamCreate()
		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful
	*/
	EDK_API int
		EE_OptimizationGetParam(OptimizationParamHandle hParam);

	//! Get a list of vital algorithms of specific suite from optimization parameter
	/*!
		\param hParam - a handle returned by EE_OptimizationParamCreate()
		\param suite - suite that you are interested in
		\param pVitalAlgorithmBitVectorOut - receives a list of vital algorithm composed of EE_ExpressivAlgo_t, EE_AffectivAlgo_t or EE_CognitivAction_t depending on the suite parameter
		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful
	*/
	EDK_API int
		EE_OptimizationGetVitalAlgorithm(OptimizationParamHandle hParam, EE_EmotivSuite_t suite, unsigned int* pVitalAlgorithmBitVectorOut);

	//! Set a list of vital algorithms of specific suite to optimization parameter
	/*!
		\param hParam - a handle returned by EE_OptimizationParamCreate()
		\param suite - suite that you are interested in
		\param vitalAlgorithmBitVector - a list of vital algorithm composed of EE_ExpressivAlgo_t, EE_AffectivAlgo_t or EE_CognitivAction_t depended on the suite parameter passed in
		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful
	*/
	EDK_API int
		EE_OptimizationSetVitalAlgorithm(OptimizationParamHandle hParam, EE_EmotivSuite_t suite, unsigned int vitalAlgorithmBitVector);

	//! Resets all settings and user-specific profile data for the specified detection suite
	/*!
		\param userId - user ID
		\param suite - detection suite (Expressiv, Affectiv, or Cognitiv)
		\param detectionBitVector - identifies specific detections.  Set to zero for all detections.
		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful
	*/
    EDK_API int EE_ResetDetection(unsigned int userId, EE_EmotivSuite_t suite, unsigned int detectionBitVector);

	//! Returns a handle to memory that can hold data. This handle can be reused by the caller to retrieve subsequent data.
	/*!
		\return DataHandle
	*/
	EDK_API DataHandle EE_DataCreate();

	//! Frees memory referenced by a data handle.
	/*!
		\param hData - a handle returned by EE_DataCreate()
	*/
	EDK_API void EE_DataFree(DataHandle hData);

	//! Updates the content of the data handle to point to new data since the last call
	/*!
		\param userId - user ID
		\param hData - a handle returned by EE_DataCreate()
		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful
	*/
	EDK_API int EE_DataUpdateHandle(unsigned int userId, DataHandle hData);

	//! Extracts data from the data handle
	/*!
		\param hData - a handle returned by EE_DataCreate()
		\param channel - channel that you are interested in
		\param buffer - pre-allocated buffer
		\param bufferSizeInSample - size of the pre-allocated buffer
		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful
	*/
	EDK_API int EE_DataGet(DataHandle hData, EE_DataChannel_t channel, double buffer[], unsigned int bufferSizeInSample);

	//! Returns number of sample of data stored in the data handle
	/*!
		\param hData - a handle returned by EE_DataCreate()
		\param nSampleOut - receives the number of sample of data stored in teh data handle
		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful
	*/
	EDK_API int EE_DataGetNumberOfSample(DataHandle hData, unsigned int* nSampleOut);

	//! Sets the size of the data buffer. The size of the buffer affects how frequent EE_DataUpdateHandle() needs to be called to prevent data loss.
	/*!
		\param bufferSizeInSec - buffer size in second
		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful
	*/
	EDK_API int EE_DataSetBufferSizeInSec(float bufferSizeInSec);

	//! Returns the size of the data buffer
	/*! 
		\param pBufferSizeInSecOut - receives the size of the data buffer
		\return EDK_ERROR_CODE
                - EDK_ERROR_CODE = EDK_OK if successful
	*/
	EDK_API int EE_DataGetBufferSizeInSec(float* pBufferSizeInSecOut);

	//! Controls acquisition of data from EmoEngine (which is off by default).
	/*!
	    \param userId - user ID
		\param enable - If true, then enables data acquisition
		              - If false, then disables data acquisition
		\return EDK_ERROR_CODE
		        - EDK_ERROR_CODE = EDK_OK if the command succeeded
	*/
	EDK_API int EE_DataAcquisitionEnable(unsigned int userId, bool enable);

	//! Returns whether data acquisition is enabled
	/*!
		\param userId - user ID
		\param pEnableOut - receives whether data acquisition is enabled
		\return EDK_ERROR_CODE
		        - EDK_ERROR_CODE = EDK_OK if the command succeeded
	*/
	EDK_API int EE_DataAcquisitionIsEnabled(unsigned int userId, bool* pEnableOut);

	//! Sets sychronization signal
	/*!
		\param userId - user ID
		\param signal - value of the sychronization signal
		\return EDK_ERROR_CODE
		        - EDK_ERROR_CODE = EDK_OK if the command succeeded
	*/
	EDK_API int EE_DataSetSychronizationSignal(unsigned int userId, int signal);

	//! Sets marker
	/*!
		\param userId - user ID
		\param marker - value of the marker
		\return EDK_ERROR_CODE
		        - EDK_ERROR_CODE = EDK_OK if the command succeeded
	*/
	EDK_API int EE_DataSetMarker(unsigned int userId, int marker);

	//! Gets sampling rate
	/*!
		\param userId - user ID
		\param samplingRateOut - receives the sampling rate
		\return EDK_ERROR_CODE
		        - EDK_ERROR_CODE = EDK_OK if the command succeeded
	*/
	EDK_API int EE_DataGetSamplingRate(unsigned int userId, unsigned int* samplingRateOut);


	// newly added
	EMOSTATE_DLL_API EmoStateHandle	ES_Create();

	//! Free EmoState handle
	/*!
        NOTE: THIS FUNCTION HAS BEEN DEPRECATED - please use EE_EmoStateFree instead.

		\param state - EmoStateHandle that was created by ES_Create function call

		\sa EE_EmoStateFree, ES_Create
	*/
	EMOSTATE_DLL_API void ES_Free(EmoStateHandle state);

	//! Initialize the EmoState into neutral state
	/*!
		\param state - EmoStateHandle
		
		\sa ES_Create, ES_Free
	*/
	EMOSTATE_DLL_API void ES_Init(EmoStateHandle state);

	//! Return the time since EmoEngine has been successfully connected to the headset
	/*!
		If the headset is disconnected from EmoEngine due to low battery or weak
		wireless signal, the time will be reset to zero.

		\param state - EmoStateHandle

		\return float - time in second

	*/
	EMOSTATE_DLL_API float ES_GetTimeFromStart(EmoStateHandle state);

	//! Return whether the headset has been put on correctly or not
	/*!
		If the headset cannot not be detected on the head, then signal quality will not report
		any results for all the channels

		\param state - EmoStatehandle

		\return int - (1: On, 0: Off)
	*/
	EMOSTATE_DLL_API int	ES_GetHeadsetOn(EmoStateHandle state);

	//! Query the number of channels of available sensor contact quality data
	/*!
		\param state - EmoStateHandle
		\return number of channels for which contact quality data is available (int)

		\sa ES_GetNumContactQualityChannels
	*/
	EMOSTATE_DLL_API int ES_GetNumContactQualityChannels(EmoStateHandle state);

	//! Query the contact quality of a specific EEG electrode
	/*!
		\param state - EmoStateHandle
		\param electroIdx - The index of the electrode for query

		\return EE_EEG_ContactQuality_t - Enumerated value that characterizes the EEG electrode contact for the specified input channel

		\sa ES_GetContactQuality
	*/
	EMOSTATE_DLL_API EE_EEG_ContactQuality_t ES_GetContactQuality(EmoStateHandle state, int electroIdx);

	//! Query the contact quality of all the electrodes in one single call
	/*!
		The contact quality will be stored in the array, contactQuality, passed to the function.
		The value stored in contactQuality[0] is identical to the result returned by
		ES_GetContactQuality(state, 0)
		The value stored in contactQuality[1] is identical to the result returned by
		ES_GetContactQuality(state, 1). etc.
		The ordering of the array is consistent with the ordering of the logical input
		channels in EE_InputChannels_enum.

		\param state - EmoStateHandle
		\param contactQuality - array of 32-bit float of size numChannels
		\param numChannels - size (number of floats) of the input array

		\return Number of signal quality values copied to the contactQuality array.

		\sa ES_GetContactQualityFromAllChannels
	*/
	EMOSTATE_DLL_API int ES_GetContactQualityFromAllChannels(EmoStateHandle state, EE_EEG_ContactQuality_t* contactQuality, size_t numChannels);

	//! Query whether the user is blinking at the time the EmoState is captured.
	/*!
		\param state - EmoStateHandle

		\return blink status (1: blink, 0: not blink)

	*/
	EMOSTATE_DLL_API int ES_ExpressivIsBlink(EmoStateHandle state);

	//! Query whether the user is winking left at the time the EmoState is captured.
	/*!
		\param state - EmoStateHandle

		\return left wink status (1: wink, 0: not wink)

		\sa ES_ExpressivIsRightWink
	*/
	EMOSTATE_DLL_API int ES_ExpressivIsLeftWink(EmoStateHandle state);

	//! Query whether the user is winking right at the time the EmoState is captured.
	/*!
		\param state - EmoStateHandle

		\return right wink status (1: wink, 0: not wink)

		\sa ES_ExpressivIsLeftWink
	*/
	EMOSTATE_DLL_API int ES_ExpressivIsRightWink(EmoStateHandle state);

	//! Query whether the eyes of the user are opened at the time the EmoState is captured.
	/*!
		\param state - EmoStateHandle

		\return eye open status (1: eyes open, 0: eyes closed)

	*/
	EMOSTATE_DLL_API int ES_ExpressivIsEyesOpen(EmoStateHandle state);

	//! Query whether the user is looking up at the time the EmoState is captured.
	/*!
		\param state - EmoStateHandle

		\return eyes position (1: looking up, 0: not looking up)

		\sa ES_ExpressivIsLookingDown
	*/
	EMOSTATE_DLL_API int ES_ExpressivIsLookingUp(EmoStateHandle state);

	//! Query whether the user is looking down at the time the EmoState is captured.
	/*!
		\param state - EmoStateHandle

		\return eyes position (1: looking down, 0: not looking down)

		\sa ES_ExpressivIsLookingUp
	*/
	EMOSTATE_DLL_API int ES_ExpressivIsLookingDown(EmoStateHandle state);

	//! Query whether the user is looking left at the time the EmoState is captured.
	/*!
		\param state - EmoStatehandle

		\return eye position (1: looking left, 0: not looking left)

		\sa ES_ExpressivIsLookingRight
	*/
	EMOSTATE_DLL_API int ES_ExpressivIsLookingLeft(EmoStateHandle state);

	//! Query whether the user is looking right at the time the EmoState is captured.
	/*!
		\param state - EmoStatehandle

		\return eye position (1: looking right, 0: not looking right)

		\sa ES_ExpressivIsLookingLeft
	*/
	EMOSTATE_DLL_API int ES_ExpressivIsLookingRight(EmoStateHandle state);

	//! Query the eyelids state of the user
	/*!
		The left and right eyelid state are stored in the parameter leftEye and rightEye
		respectively. They are floating point values ranging from 0.0 to 1.0.
		0.0 indicates that the eyelid is fully opened while 1.0 indicates that the
		eyelid is fully closed.

		\param state - EmoStatehandle
		\param leftEye - the left eyelid state (0.0 to 1.0)
		\param rightEye - the right eyelid state (0.0 to 1.0)

	*/
	EMOSTATE_DLL_API void ES_ExpressivGetEyelidState(EmoStateHandle state, float* leftEye, float* rightEye);

	//! Query the eyes position of the user
	/*!
		The horizontal and vertical position of the eyes are stored in the parameter x and y
		respectively. They are floating point values ranging from -1.0 to 1.0.
		
		For horizontal position, -1.0 indicates that the user is looking left while
		1.0 indicates that the user is looking right.
		
		For vertical position, -1.0 indicates that the user is looking down while
		1.0 indicatest that the user is looking up.

		This function assumes that both eyes have the same horizontal or vertical positions.
		(i.e. no cross eyes)

		\param state - EmoStateHandle
		\param x - the horizontal position of the eyes
		\param y - the veritcal position of the eyes

	*/
	EMOSTATE_DLL_API void ES_ExpressivGetEyeLocation(EmoStateHandle state, float* x, float* y);

	//! Returns the eyebrow extent of the user (Obsolete function)
	/*!
		\param state - EmoStateHandle
		
		\return eyebrow extent value (0.0 to 1.0)

		\sa ES_ExpressivGetUpperFaceAction, ES_ExpressivGetUpperFaceActionPower
	*/
	EMOSTATE_DLL_API float ES_ExpressivGetEyebrowExtent(EmoStateHandle state);

	//! Returns the smile extent of the user (Obsolete function)
	/*!
		\param state - EmoStatehandle
		
		\return smile extent value (0.0 to 1.0)

		\sa ES_ExpressivGetLowerFaceAction, ES_ExpressivGetLowerFaceActionPower
	*/
	EMOSTATE_DLL_API float ES_ExpressivGetSmileExtent(EmoStateHandle state);

	//! Returns the clench extent of the user (Obsolete function)
	/*!
		\param state - EmoStatehandle

		\return clench extent value (0.0 to 1.0)

		\sa ES_ExpressivGetLowerFaceAction, ES_ExpressivGetLowerFaceActionPower
	*/
	EMOSTATE_DLL_API float ES_ExpressivGetClenchExtent(EmoStateHandle state);


	//! Returns the detected upper face Expressiv action of the user
	/*!
		\param state - EmoStatehandle

		\return pre-defined Expressiv action types

		\sa ES_ExpressivGetUpperFaceActionPower
	*/
	EMOSTATE_DLL_API EE_ExpressivAlgo_t ES_ExpressivGetUpperFaceAction(EmoStateHandle state);

	//! Returns the detected upper face Expressiv action power of the user
	/*!
		\param state - EmoStatehandle

		\return power value (0.0 to 1.0)

		\sa ES_ExpressivGetUpperFaceAction
	*/
	EMOSTATE_DLL_API float ES_ExpressivGetUpperFaceActionPower(EmoStateHandle state);

	//! Returns the detected lower face Expressiv action of the user
	/*!
		\param state - EmoStatehandle

		\return pre-defined Expressiv action types

		\sa ES_ExpressivGetLowerFaceActionPower
	*/
	EMOSTATE_DLL_API EE_ExpressivAlgo_t ES_ExpressivGetLowerFaceAction(EmoStateHandle state);

	//! Returns the detected lower face Expressiv action power of the user
	/*!
		\param state - EmoStatehandle

		\return power value (0.0 to 1.0)

		\sa ES_ExpressivGetLowerFaceAction
	*/
	EMOSTATE_DLL_API float ES_ExpressivGetLowerFaceActionPower(EmoStateHandle state);
	
	//! Query whether the signal is too noisy for Expressiv detection to be active
	/*!
		\param state - EmoStateHandle
		\param type  - Expressiv detection type

		\return detection state (0: Not Active, 1: Active)

		\sa EE_ExpressivAlgo_t
	*/
	EMOSTATE_DLL_API int ES_ExpressivIsActive(EmoStateHandle state, EE_ExpressivAlgo_t type);

	//! Returns the long term excitement level of the user
	/*!
		\param state - EmoStateHandle

		\return excitement level (0.0 to 1.0)

		\sa ES_AffectivGetExcitementShortTermScore
	*/
	EMOSTATE_DLL_API float ES_AffectivGetExcitementLongTermScore(EmoStateHandle state);

	//! Returns short term excitement level of the user
	/*!
		\param state - EmoStateHandle

		\return excitement level (0.0 to 1.0)

		\sa ES_AffectivGetExcitementLongTermScore
	*/
	EMOSTATE_DLL_API float ES_AffectivGetExcitementShortTermScore(EmoStateHandle state);
	
	//! Query whether the signal is too noisy for Affectiv detection to be active
	/*!
		\param state - EmoStateHandle
		\param type  - Affectiv detection type

		\return detection state (0: Not Active, 1: Active)

		\sa EE_AffectivAlgo_t
	*/
	EMOSTATE_DLL_API int ES_AffectivIsActive(EmoStateHandle state, EE_AffectivAlgo_t type);

	//! Returns meditation level of the user
	/*!
		\param state - EmoStateHandle

		\return meditation level (0.0 to 1.0)
	*/
	EMOSTATE_DLL_API float ES_AffectivGetMeditationScore(EmoStateHandle state);

	//! Returns frustration level of the user
	/*!
		\param state - EmoStateHandle

		\return frustration level (0.0 to 1.0)
	*/
	EMOSTATE_DLL_API float ES_AffectivGetFrustrationScore(EmoStateHandle state);

	//! Returns engagement/boredom level of the user
	/*!
		\param state - EmoStateHandle

		\return engagement/boredom level (0.0 to 1.0)
	*/
	EMOSTATE_DLL_API float ES_AffectivGetEngagementBoredomScore(EmoStateHandle state);

	//! Returns the detected Cognitiv action of the user
	/*!
		\param state - EmoStateHandle

		\return Cognitiv action type

		\sa EE_CognitivAction_t, ES_CognitivGetCurrentActionPower
	*/
	EMOSTATE_DLL_API EE_CognitivAction_t ES_CognitivGetCurrentAction(EmoStateHandle state);

	//! Returns the detected Cognitiv action power of the user
	/*!
		\param state - EmoStateHandle

		\return Cognitiv action power (0.0 to 1.0)

		\sa ES_CognitivGetCurrentAction
	*/
	EMOSTATE_DLL_API float ES_CognitivGetCurrentActionPower(EmoStateHandle state);
	
	//! Query whether the signal is too noisy for Cognitiv detection to be active
	/*!
		\param state - EmoStateHandle

		\return detection state (0: Not Active, 1: Active)
	*/
	EMOSTATE_DLL_API int ES_CognitivIsActive(EmoStateHandle state);


	//! Query of the current wireless signal strength
	/*!
		\param state - EmoStateHandle

		\return wireless signal strength [No Signal, Bad, Fair, Good, Excellent].

		\sa EE_SignalStrength_t
	*/
	EMOSTATE_DLL_API EE_SignalStrength_t ES_GetWirelessSignalStatus(EmoStateHandle state);

	//! Clone EmoStateHandle
	/*!
		\param a - Destination of EmoStateHandle
		\param b - Source of EmoStateHandle

		\sa ES_Create
	*/
	EMOSTATE_DLL_API void ES_Copy(EmoStateHandle a, EmoStateHandle b);

	//! Check whether two states are with identical 'emotiv' state
	/*!
		\param a - EmoStateHandle
		\param b - EmoStateHandle

		\return 1: Equal, 0: Different

		\sa ES_ExpressivEqual, ES_CognitivEqual, ES_EmoEngineEqual, ES_Equal
	*/
	EMOSTATE_DLL_API int ES_AffectivEqual(EmoStateHandle a, EmoStateHandle b);

	//! Check whether two states are with identical Expressiv state, i.e. are both state representing the same facial expression
	/*!
		\param a - EmoStateHandle
		\param b - EmoStateHandle

		\return 1: Equal, 0: Different

		\sa ES_AffectivEqual, ES_CognitivEqual, ES_EmoEngineEqual, ES_Equal
	*/
	EMOSTATE_DLL_API int ES_ExpressivEqual(EmoStateHandle a, EmoStateHandle b);

	//! Check whether two states are with identical Cognitiv state
	/*!
		\param a - EmoStateHandle
		\param b - EmoStateHandle

		\return 1: Equal, 0: Different

		\sa ES_AffectivEqual, ES_ExpressivEqual, ES_EmoEngineEqual, ES_Equal
	*/
	EMOSTATE_DLL_API int ES_CognitivEqual(EmoStateHandle a, EmoStateHandle b);

	//! Check whether two states are with identical EmoEngine state.
	/*!
		This function is comparing the time since EmoEngine start,
		the wireless signal strength and the signal quality of different channels

		\param a - EmoStateHandle
		\param b - EmoStateHandle

		\return 1: Equal, 0: Different

		\sa ES_AffectivEqual, ES_ExpressivEqual, ES_CognitivEqual, ES_Equal
	*/
	EMOSTATE_DLL_API int ES_EmoEngineEqual(EmoStateHandle a, EmoStateHandle b);

	//! Check whether two EmoStateHandles are identical
	/*!
		\param a - EmoStateHandle
		\param b - EmoStateHandle

		\return 1: Equal, 0: Different

		\sa ES_AffectivEqual, ES_ExpressivEqual, ES_EmoEngineEqual
	*/
	EMOSTATE_DLL_API int ES_Equal(EmoStateHandle a, EmoStateHandle b);

	//! Get the level of charge remaining in the headset battery
	/*!
		\param state			- EmoStateHandle
		\param chargeLevel		- the current level of charge in the headset battery
		\param maxChargeLevel	- the maximum level of charge in the battery

	*/
	EMOSTATE_DLL_API void ES_GetBatteryChargeLevel(EmoStateHandle state, int* chargeLevel, int* maxChargeLevel);
};


#endif
