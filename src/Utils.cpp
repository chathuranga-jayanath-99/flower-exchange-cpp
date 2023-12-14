#include "Utils.h"
#include "Constants.h"

using namespace std;

string Utils::getStrFromInstrument(Instrument instrument) {
    switch (instrument)
    {
    case Instrument::ROSE:
        return Constants::ROSE;
        break;
    case Instrument::LAVENDER:
        return Constants::LAVENDER;
        break;
    case Instrument::LOTUS:
        return Constants::LOTUS;
        break;
    case Instrument::ORCHID:
        return Constants::ORCHID;
        break;
    case Instrument::TULIP:
        return Constants::TULIP;
        break;
    default:
        break;
    }
} 

string Utils::getStrFromReason(Reason reason) {
    switch (reason)
    {
    case Reason::INVALID_INSTRUMENT:
        return Constants::INVALID_INSTRUMENT;
        break;
    case Reason::INVALID_PRICE:
        return Constants::INVALID_PRICE;
        break;
    case Reason::INVALID_SIDE:
        return Constants::INVALID_SIDE;
        break;
    case Reason::INVALID_SIZE:
        return Constants::INVALID_SIZE;
        break;
    default:
        return Constants::EMPTY;
        break;
    }
}

string Utils::getStrFromExecutionStatus(ExecutionStatus execStatus) {
    switch (execStatus)
    {
    case ExecutionStatus::NEW:
        return Constants::NEW;
        break;
    case ExecutionStatus::FILL:
        return Constants::FILL;
        break;
    case ExecutionStatus::PFILL:
        return Constants::PFILL;
        break;
    case ExecutionStatus::REJECTED:
        return Constants::REJECTED;
    default:
        break;
    }
}

string Utils::getReasonStrFromErrorCode(int errorCode) {
    if (errorCode == 0) {
        return Constants::INVALID_INSTRUMENT;
    } else if (errorCode == 1) {
        return Constants::INVALID_SIDE;
    } else if (errorCode == 2) {
        return Constants::INVALID_PRICE;
    } else if (errorCode == 3) {
        return Constants::INVALID_SIZE;
    } else {
        return Constants::EMPTY;
    }
    
}
