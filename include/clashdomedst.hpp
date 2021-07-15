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
    ACTION updateorcs(uint32_t orcs, uint32_t day, uint16_t land_id, uint32_t partial_orcs);
    ACTION clearorcs();
    ACTION clearlands();

    ACTION addtowl(vector <name> accounts_to_add);
    ACTION clearwl();
    ACTION setnftsold(uint32_t n);

    [[eosio::on_notify("clashdometkn::transfer")]] void transfer(const name &from, const name &to, const asset &quantity, const string &memo);

private:

    TABLE landactivity_s {
        uint64_t timestamp;
        uint16_t land_id;
        uint64_t partial_orcs;
    
        uint64_t primary_key() const {return timestamp;}
    };

    typedef multi_index <name("landactivity"), landactivity_s> landactivity_t;
    landactivity_t landactivity = landactivity_t(get_self(), get_self().value); 

    TABLE killedorcs_s {
        uint32_t day;
        uint64_t kills;
        uint16_t orcs_ludio_ratio;

        uint64_t primary_key() const {return (uint64_t) day;}
    };

    typedef multi_index <name("killedorcs"), killedorcs_s> killedorcs_t;
    killedorcs_t killedorcs = killedorcs_t(get_self(), get_self().value); 

    const string GAME_NAMES[3] = {"Endless Siege", "Candy Fiesta", "Templok"};

    const string COLLECTION_NAME = "clashdomenft";
    const string SCHEMA_NAME = "lands";

    static constexpr symbol LUDIO_SYMBOL = symbol(symbol_code("LUDIO"), 4);

    // EARLY ACCESS NFT
    const uint32_t NFT_PRICE = 5; // PRICE IN LUDIO MULTIPLIED BY 1E4
    const uint32_t NFT_MAX_SUPPLY = 250;

    const string EARLY_ACCESS_SCHEMA_NAME = "gamedata";
    const uint32_t EARLY_ACCESS_TEMPLATE_ID = 82326;

    TABLE whitelists_s {
    
        uint64_t id;
        vector<name> whitelist;

        uint64_t primary_key() const {return  id;}
    };

    typedef multi_index <name("whitelists"), whitelists_s> whitelists_t;
    whitelists_t whitelists = whitelists_t(get_self(), get_self().value); 

    TABLE nftsold_s {
    
        uint64_t id;
        uint32_t n;

        uint64_t primary_key() const {return  id;}
    };

    typedef multi_index <name("nftsold"), nftsold_s> nftsold_t;
    nftsold_t nftsold = nftsold_t(get_self(), get_self().value); 
};