#ifndef FIX44_REGISTRATIONINSTRUCTIONS_H
#define FIX44_REGISTRATIONINSTRUCTIONS_H

#include "Message.h"

namespace FIX44
{

  class RegistrationInstructions : public Message
  {
  public:
    RegistrationInstructions() : Message(MsgType()) {}
    RegistrationInstructions(const FIX::Message& m) : Message(m) {}
    RegistrationInstructions(const Message& m) : Message(m) {}
    RegistrationInstructions(const RegistrationInstructions& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("o"); }

    RegistrationInstructions(
      const FIX::RegistID& aRegistID,
      const FIX::RegistTransType& aRegistTransType,
      const FIX::RegistRefID& aRegistRefID )
    : Message(MsgType())
    {
      set(aRegistID);
      set(aRegistTransType);
      set(aRegistRefID);
    }

    FIELD_SET(*this, FIX::RegistID);
    FIELD_SET_EX(std::string, RegistID);
    FIELD_SET(*this, FIX::RegistTransType);
    FIELD_SET_EX(char, RegistTransType);
    FIELD_SET(*this, FIX::RegistRefID);
    FIELD_SET_EX(std::string, RegistRefID);
    FIELD_SET(*this, FIX::ClOrdID);
    FIELD_SET_EX(std::string, ClOrdID);
    FIELD_SET(*this, FIX::NoPartyIDs);
    FIELD_SET_EX(int, NoPartyIDs);
    class NoPartyIDs: public FIX::Group
    {
    public:
    NoPartyIDs() : FIX::Group(453,448,FIX::message_order(448,447,452,802,0)) {}
      FIELD_SET(*this, FIX::PartyID);
      FIELD_SET_EX(std::string, PartyID);
      FIELD_SET(*this, FIX::PartyIDSource);
      FIELD_SET_EX(char, PartyIDSource);
      FIELD_SET(*this, FIX::PartyRole);
      FIELD_SET_EX(int, PartyRole);
      FIELD_SET(*this, FIX::NoPartySubIDs);
      FIELD_SET_EX(int, NoPartySubIDs);
      class NoPartySubIDs: public FIX::Group
      {
      public:
      NoPartySubIDs() : FIX::Group(802,523,FIX::message_order(523,803,0)) {}
        FIELD_SET(*this, FIX::PartySubID);
        FIELD_SET_EX(std::string, PartySubID);
        FIELD_SET(*this, FIX::PartySubIDType);
        FIELD_SET_EX(int, PartySubIDType);
      };
    };
    FIELD_SET(*this, FIX::Account);
    FIELD_SET_EX(std::string, Account);
    FIELD_SET(*this, FIX::AcctIDSource);
    FIELD_SET_EX(int, AcctIDSource);
    FIELD_SET(*this, FIX::RegistAcctType);
    FIELD_SET_EX(std::string, RegistAcctType);
    FIELD_SET(*this, FIX::TaxAdvantageType);
    FIELD_SET_EX(int, TaxAdvantageType);
    FIELD_SET(*this, FIX::OwnershipType);
    FIELD_SET_EX(char, OwnershipType);
    FIELD_SET(*this, FIX::NoRegistDtls);
    FIELD_SET_EX(int, NoRegistDtls);
    class NoRegistDtls: public FIX::Group
    {
    public:
    NoRegistDtls() : FIX::Group(473,509,FIX::message_order(509,511,474,482,539,522,486,475,0)) {}
      FIELD_SET(*this, FIX::RegistDtls);
      FIELD_SET_EX(std::string, RegistDtls);
      FIELD_SET(*this, FIX::RegistEmail);
      FIELD_SET_EX(std::string, RegistEmail);
      FIELD_SET(*this, FIX::MailingDtls);
      FIELD_SET_EX(std::string, MailingDtls);
      FIELD_SET(*this, FIX::MailingInst);
      FIELD_SET_EX(std::string, MailingInst);
      FIELD_SET(*this, FIX::NoNestedPartyIDs);
      FIELD_SET_EX(int, NoNestedPartyIDs);
      class NoNestedPartyIDs: public FIX::Group
      {
      public:
      NoNestedPartyIDs() : FIX::Group(539,524,FIX::message_order(524,525,538,804,0)) {}
        FIELD_SET(*this, FIX::NestedPartyID);
        FIELD_SET_EX(std::string, NestedPartyID);
        FIELD_SET(*this, FIX::NestedPartyIDSource);
        FIELD_SET_EX(char, NestedPartyIDSource);
        FIELD_SET(*this, FIX::NestedPartyRole);
        FIELD_SET_EX(int, NestedPartyRole);
        FIELD_SET(*this, FIX::NoNestedPartySubIDs);
        FIELD_SET_EX(int, NoNestedPartySubIDs);
        class NoNestedPartySubIDs: public FIX::Group
        {
        public:
        NoNestedPartySubIDs() : FIX::Group(804,545,FIX::message_order(545,805,0)) {}
          FIELD_SET(*this, FIX::NestedPartySubID);
          FIELD_SET_EX(std::string, NestedPartySubID);
          FIELD_SET(*this, FIX::NestedPartySubIDType);
          FIELD_SET_EX(int, NestedPartySubIDType);
        };
      };
      FIELD_SET(*this, FIX::OwnerType);
      FIELD_SET_EX(int, OwnerType);
      FIELD_SET(*this, FIX::DateOfBirth);
      FIELD_SET_EX(std::string, DateOfBirth);
      FIELD_SET(*this, FIX::InvestorCountryOfResidence);
    };
    FIELD_SET(*this, FIX::NoDistribInsts);
    FIELD_SET_EX(int, NoDistribInsts);
    class NoDistribInsts: public FIX::Group
    {
    public:
    NoDistribInsts() : FIX::Group(510,477,FIX::message_order(477,512,478,498,499,500,501,502,0)) {}
      FIELD_SET(*this, FIX::DistribPaymentMethod);
      FIELD_SET_EX(int, DistribPaymentMethod);
      FIELD_SET(*this, FIX::DistribPercentage);
      FIELD_SET_EX(double, DistribPercentage);
      FIELD_SET(*this, FIX::CashDistribCurr);
      FIELD_SET_EX(std::string, CashDistribCurr);
      FIELD_SET(*this, FIX::CashDistribAgentName);
      FIELD_SET_EX(std::string, CashDistribAgentName);
      FIELD_SET(*this, FIX::CashDistribAgentCode);
      FIELD_SET_EX(std::string, CashDistribAgentCode);
      FIELD_SET(*this, FIX::CashDistribAgentAcctNumber);
      FIELD_SET_EX(std::string, CashDistribAgentAcctNumber);
      FIELD_SET(*this, FIX::CashDistribPayRef);
      FIELD_SET_EX(std::string, CashDistribPayRef);
      FIELD_SET(*this, FIX::CashDistribAgentAcctName);
      FIELD_SET_EX(std::string, CashDistribAgentAcctName);
    };
  };

}

#endif
