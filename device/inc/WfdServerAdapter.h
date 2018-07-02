/* Copyright 2017-2018 All Rights Reserved.
 *  Gyeonghwan Hong (redcarrottt@gmail.com)
 *  
 * [Contact]
 *  Gyeonghwan Hong (redcarrottt@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0(the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _WFD_SERVER_ADAPTER_H_
#define _WFD_SERVER_ADAPTER_H_

#include <ServerAdapter.h>
#include <WfdDevice.h>
#include <WfdP2PServer.h>
#include <TcpServerSocket.h>

#include <Counter.h>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <stdio.h>

namespace cm {

class WfdServerAdapter : ServerAdapter, ControlMessageListener {
public:
  WfdServerAdapter(char* name, int port, const char* wfd_device_name) : ServerAdapter(name) { 
    WfdDevice* device = WfdDevice::getSingleton();
    WfdP2PServer* p2pServer = new WfdP2PServer(wfd_device_name);
    TcpServerSocket* serverSocket = new TcpServerSocket(port);
    p2pServer->add_wfd_ip_address_listener(p2pServer);
    this->initialize(device, p2pServer, serverSocket);
  }

  virtual void on_receive_control_message(int adapter_id, void* data, size_t len) {
    if(adapter_id == this->get_id()) {
      WfdP2PServer* p2pServer = (WfdP2PServer*)this->mP2pServer;
      p2pServer->on_receive_control_message(data, len);
    }
  }

  ~WfdServerAdapter(void) {
  }

protected:
}; /* class WfdServerAdapter */

} /* namespace cm */

#endif /* !defined(_WFD_SERVER_ADAPTER_H_) */
