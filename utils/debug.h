#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG_TYPE_NONE 0x00
#define DEBUG_TYPE_START_END 0x01
#define DEBUG_TYPE_GENERAL_MSG 0x02
#define DEBUG_TYPE_WARNING 0x04
#define DEBUG_TYPE_FATAL_ERR 0x08
#define DEBUG_TYPE_INTERNAL 0x10
#define DEBUG_TYPE_ALL 0xFF

// Current Filter
#define DEBUG_TYPE (DEBUG_TYPE_ALL)
// define DEBUG_TYPE (DEBUG_TYPE_WARNING | DEBUG_TYPE_FATAL_ERR)

#if defined(_DEBUG)
// Debug Messages
#include <QDebug>
#include <QRegularExpression>

static unsigned int _DEBUG_COUNTER = 0;

inline QString _DEBUG_CLEAN_FUNCTION_NAME(QString function_name) {
  QRegularExpression regex("\\w+::~?\\w+");
  QRegularExpressionMatch match = regex.match(function_name);
  if (match.capturedLength() > 0) {
    return match.captured(0);
  }
  return function_name;
}

#ifdef _MSC_VER
#define FUNCTION_NAME __FUNCTION__
#else
#define FUNCTION_NAME __PRETTY_FUNCTION__
#endif

#define DEBUG_LOG(type, msg)                                                 \
  if (DEBUG_TYPE_NONE != (type & DEBUG_TYPE)) {                              \
    qDebug() << "[" << qPrintable(_DEBUG_CLEAN_FUNCTION_NAME(FUNCTION_NAME)) \
             << __LINE__ << "] " << msg;                                     \
  }

#define DEBUG_ALLOCATE _DEBUG_COUNTER++;
#define DEBUG_RELEASED _DEBUG_COUNTER++;

#else
#define DEBUG_LOG(type, msg)
#define DEBUG_ALLOCATE
#define DEBUG_RELEASED
#endif

// Different type of debug messages
#define DEBUG_START DEBUG_LOG(DEBUG_TYPE_START_END, "START")
#define DEBUG_END DEBUG_LOG(DEBUG_TYPE_START_END, "END")
#define DEBUG_MSG(msg) DEBUG_LOG(DEBUG_TYPE_GENERAL_MSG, msg)
#define DEBUG_WARNING(msg) DEBUG_LOG(DEBUG_TYPE_WARNING, msg)
#define DEBUG_FATAL(msg) DEBUG_LOG(DEBUG_TYPE_FATAL_ERR, msg)
#define DEBUG_COUNTER \
  DEBUG_LOG(DEBUG_TYPE_INTERNAL, "DEBUG COUNT" << _DEBUG_COUNTER)

#endif // DEBUG_H

