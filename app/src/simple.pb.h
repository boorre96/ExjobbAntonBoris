/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.6 */

#ifndef PB_SIMPLE_PB_H_INCLUDED
#define PB_SIMPLE_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _SimpleMessage { 
    int32_t regNum;
    int32_t val;
    int32_t read;
} SimpleMessage;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define SimpleMessage_init_default               {0, 0, 0}
#define SimpleMessage_init_zero                  {0, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define SimpleMessage_regNum_tag                 1
#define SimpleMessage_val_tag                    2
#define SimpleMessage_read_tag                   3

/* Struct field encoding specification for nanopb */
#define SimpleMessage_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    regNum,            1) \
X(a, STATIC,   SINGULAR, INT32,    val,               2) \
X(a, STATIC,   SINGULAR, INT32,    read,              3)
#define SimpleMessage_CALLBACK NULL
#define SimpleMessage_DEFAULT NULL

extern const pb_msgdesc_t SimpleMessage_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define SimpleMessage_fields &SimpleMessage_msg

/* Maximum encoded size of messages (where known) */
#define SimpleMessage_size                       33

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
