#ifndef UTILS_H
#define UTILS_H

#include "./enums/Instrument.h"
#include "./enums/Reason.h"
#include "./enums/ExecutionStatus.h"
#include <string>

using namespace std;

class Utils {
    public:
        static string getStrFromInstrument(Instrument instrument);
        static string getStrFromReason(Reason reason);
        static string getStrFromExecutionStatus(ExecutionStatus execStatus);
        static string getReasonStrFromErrorCode(int errorCode);
};

#endif