#include "isocketadapter.h"

ISocketAdapter::ISocketAdapter(QObject *parent) : ITransport(parent) {

}

ISocketAdapter::~ISocketAdapter() {

}

bool ISocketAdapter::isLocal() {
    return false;
}

bool ISocketAdapter::isConnected() {

}
