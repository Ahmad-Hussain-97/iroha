/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef IROHA_NETWORK_MOCKS_HPP
#define IROHA_NETWORK_MOCKS_HPP

#include <gmock/gmock.h>
#include "interfaces/iroha_internal/transaction_batch.hpp"
#include "network/block_loader.hpp"
#include "network/consensus_gate.hpp"
#include "network/ordering_gate.hpp"
#include "network/peer_communication_service.hpp"
#include "simulator/block_creator_common.hpp"
#include "synchronizer/synchronizer_common.hpp"

namespace shared_model {
  namespace interface {
    class Transaction;
  }
}  // namespace shared_model

namespace iroha {
  namespace network {
    class MockPeerCommunicationService : public PeerCommunicationService {
     public:
      MOCK_CONST_METHOD1(
          propagate_transaction,
          void(std::shared_ptr<const shared_model::interface::Transaction>));

      MOCK_CONST_METHOD1(
          propagate_batch,
          void(std::shared_ptr<shared_model::interface::TransactionBatch>));

      MOCK_CONST_METHOD0(onProposal, rxcpp::observable<OrderingEvent>());

      MOCK_CONST_METHOD0(
          onSynchronization,
          rxcpp::observable<synchronizer::SynchronizationEvent>());

      MOCK_CONST_METHOD0(
          onVerifiedProposal,
          rxcpp::observable<simulator::VerifiedProposalCreatorEvent>());
    };

    class MockBlockLoader : public BlockLoader {
     public:
      MOCK_METHOD2(
          retrieveBlocks,
          rxcpp::observable<std::shared_ptr<shared_model::interface::Block>>(
              const shared_model::interface::types::HeightType,
              const shared_model::crypto::PublicKey &));
      MOCK_METHOD2(
          retrieveBlock,
          boost::optional<std::shared_ptr<shared_model::interface::Block>>(
              const shared_model::crypto::PublicKey &,
              shared_model::interface::types::HeightType));
    };

    class MockOrderingGate : public OrderingGate {
     public:
      MOCK_CONST_METHOD1(
          propagateTransaction,
          void(std::shared_ptr<const shared_model::interface::Transaction>
                   transaction));

      MOCK_METHOD1(
          propagateBatch,
          void(std::shared_ptr<shared_model::interface::TransactionBatch>));

      MOCK_METHOD0(onProposal, rxcpp::observable<OrderingEvent>());

      MOCK_METHOD1(setPcs, void(const PeerCommunicationService &));
    };

    class MockConsensusGate : public ConsensusGate {
     public:
      MOCK_METHOD1(vote, void(const simulator::BlockCreatorEvent &));

      MOCK_METHOD0(onOutcome, rxcpp::observable<GateObject>());
    };

  }  // namespace network
}  // namespace iroha

#endif  // IROHA_NETWORK_MOCKS_HPP
