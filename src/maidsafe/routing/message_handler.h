/*******************************************************************************
 *  Copyright 2012 maidsafe.net limited                                        *
 *                                                                             *
 *  The following source code is property of maidsafe.net limited and is not   *
 *  meant for external use.  The use of this code is governed by the licence   *
 *  file licence.txt found in the root of this directory and also on           *
 *  www.maidsafe.net.                                                          *
 *                                                                             *
 *  You are not free to copy, amend or otherwise use this source code without  *
 *  the explicit written permission of the board of directors of maidsafe.net. *
 ******************************************************************************/

#ifndef MAIDSAFE_ROUTING_MESSAGE_HANDLER_H_
#define MAIDSAFE_ROUTING_MESSAGE_HANDLER_H_

#include "boost/thread/shared_mutex.hpp"
#include "boost/thread/mutex.hpp"
#include "maidsafe/common/rsa.h"
#include "maidsafe/transport/managed_connections.h"
#include "maidsafe/routing/routing.pb.h"
#include "maidsafe/routing/routing_table.h"
#include "maidsafe/routing/routing_api.h"
#include "maidsafe/routing/service.h"
#include "maidsafe/routing/rpcs.h"
#include "maidsafe/routing/response_handler.h"
#include "maidsafe/routing/cache_manager.h"
#include "maidsafe/routing/timer.h"
#include "maidsafe/routing/node_id.h"
#include "maidsafe/routing/log.h"


namespace maidsafe {

namespace routing {

class MessageHandler {
public:
  MessageHandler(const NodeValidationFunctor &node_Validation_functor,
                 RoutingTable &routing_table,
                 transport::ManagedConnections &transport,
                 Timer &timer_ptr);
  ~MessageHandler();
  void ProcessMessage(protobuf::Message &message);
  void ProcessDirectMessage(protobuf::Message &message);
  void ProcessCloseNodesMessage(protobuf::Message &message);
  bool CheckCacheData(protobuf::Message &message);
  bool CheckAndSendToLocalClients(protobuf::Message &message);
  boost::signals2::signal<void(int, std::string)> &MessageReceivedSignal();
private:
  MessageHandler(const MessageHandler&);  // no copy
  MessageHandler& operator=(const MessageHandler&);  // no assign
  NodeValidationFunctor node_validation_functor_;
  RoutingTable &routing_table_;
  transport::ManagedConnections &transport_;
  Timer &timer_ptr_;
  CacheManager cache_manager_;
  Service service_;
  Rpcs rpcs_;
  ResponseHandler response_handler_;
  boost::signals2::signal<void(int, std::string)> message_received_signal_;
};

}  // namespace routing

}  // namespace maidsafe


#endif // MAIDSAFE_ROUTING_MESSAGE_HANDLER_H_