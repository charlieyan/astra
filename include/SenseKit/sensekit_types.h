#ifndef SENSEKIT_TYPES_H
#define SENSEKIT_TYPES_H

#include <stdint.h>
#include <stddef.h>

const unsigned MAX_STRING_FIELD_LENGTH = 256;
const uint8_t SENSEKIT_MAX_READER_STREAMS = 16;

typedef struct _sensekit_stream* sensekit_stream_t;

typedef int32_t sensekit_stream_type_t;
typedef int32_t sensekit_stream_subtype_t;

const sensekit_stream_subtype_t ANY_SUBTYPE = -1;

struct sensekit_stream_desc_t {
    sensekit_stream_type_t type;
    sensekit_stream_subtype_t subType;
};

typedef struct _sensekit_streamset* sensekit_streamset_t;
typedef struct _sensekit_streamconnection_handle* sensekit_streamconnection_handle_t;

typedef struct _sensekit_streamconnection* sensekit_streamconnection_t;

typedef struct _sensekit_frame {
    size_t byteLength;
    uint32_t frameIndex;
    void* data;
} sensekit_frame_t;

typedef struct _sensekit_frame_ref {
    sensekit_streamconnection_t streamConnection;
    sensekit_frame_t* frame;
} sensekit_frame_ref_t;

typedef struct _sensekit_reader* sensekit_reader_t;
typedef sensekit_reader_t sensekit_reader_frame_t;

typedef struct _sensekit_parameter_data sensekit_parameter_data_t;
typedef int32_t sensekit_parameter_id;

typedef struct _sensekit_bin* sensekit_bin_t;

typedef enum _sensekit_status {
    SENSEKIT_STATUS_SUCCESS = 0,
    SENSEKIT_STATUS_INVALID_PARAMETER = 1,
    SENSEKIT_STATUS_DEVICE_ERROR = 2,
    SENSEKIT_STATUS_TIMEOUT = 3
} sensekit_status_t;

typedef struct _sensekit_device_desc {
    char uri[MAX_STRING_FIELD_LENGTH];
    char vendor[MAX_STRING_FIELD_LENGTH];
    char name[MAX_STRING_FIELD_LENGTH];
    uint16_t usbVendorId;
    uint16_t usbProductId;
} sensekit_device_desc_t;

typedef size_t CallbackId;

// Stream service callback types
typedef struct _sensekit_reader_callback_id {
    sensekit_reader_t reader;
    CallbackId callbackId;
} sensekit_reader_callback_id_raw_t, *sensekit_reader_callback_id_t;

typedef void(*FrameReadyCallback)(sensekit_reader_t reader,
    sensekit_reader_frame_t frame);

// Plugin service callback types

typedef void(*set_parameter_callback_t)(void*, sensekit_streamconnection_t,
                                        sensekit_parameter_id,
                                        size_t,
                                        sensekit_parameter_data_t*);

typedef void(*get_parameter_size_callback_t)(void*,
                                             sensekit_streamconnection_t,
                                             sensekit_parameter_id,
                                             size_t*);

typedef void(*get_parameter_data_callback_t)(void*,
                                             sensekit_streamconnection_t,
                                             sensekit_parameter_id, size_t,
                                             sensekit_parameter_data_t*);

typedef void(*connection_added_callback_t)(void*, sensekit_streamconnection_t);
typedef void(*connection_removed_callback_t)(void*, sensekit_streamconnection_t);


typedef void(*StreamAddedCallback)(sensekit_streamset_t,
                                   sensekit_stream_t,
                                   sensekit_stream_desc_t);

typedef void(*StreamRemovingCallback)(sensekit_streamset_t,
                                      sensekit_stream_t,
                                      sensekit_stream_desc_t);

struct stream_callbacks_t
{
    void* context;
    set_parameter_callback_t setParameterCallback;
    get_parameter_size_callback_t getParameterSizeCallback;
    get_parameter_data_callback_t getParameterDataCallback;
    connection_added_callback_t connectionAddedCallback;
    connection_removed_callback_t connectionRemovedCallback;
};
#endif /* SENSEKIT_TYPES_H */
