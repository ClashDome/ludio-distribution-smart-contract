#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/transaction.hpp>
#include <atomicassets.hpp>
#include <atomicdata.hpp>

using namespace eosio;
using namespace std;

#define ATOMIC name("atomicassets")
#define EOSIO name("eosio")
#define CONTRACTN name("clashdomedst")

CONTRACT clashdomedst : public contract {

public:

    using contract::contract;

    ACTION claimludio(name account, uint64_t asset_id, uint16_t game_id);
    ACTION updateorcs(uint32_t orcs, uint32_t day);
    ACTION clearorcs();

private:

    TABLE killed_orcs_s {
        uint32_t day;
        uint64_t killed_orcs;
        uint16_t orcs_ludio_ratio;

        uint64_t primary_key() const {return (uint64_t) day;}
    };

    typedef multi_index <name("orcs"), killed_orcs_s> killed_orcs_t;
    killed_orcs_t killed_orcs = killed_orcs_t(get_self(), get_self().value); 

    const string GAME_NAMES[3] = {"Endless Siege", "Candy Fiesta", "Templok"};

    const string COLLECTION_NAME = "blcollection";
    const string SCHEMA_NAME = "land3";

    static constexpr symbol LUDIO_SYMBOL = symbol(symbol_code("LUDIO"), 4);
};