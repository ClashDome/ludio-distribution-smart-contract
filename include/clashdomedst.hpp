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
    ACTION claim(name account);
    ACTION updateorcs(uint32_t orcs, uint32_t day, uint16_t land_id, uint32_t partial_orcs);
    ACTION updateballs(uint32_t balls, uint32_t day, uint16_t hall_id, uint32_t partial_balls);
    ACTION clearorcs();
    ACTION clearlands();
    ACTION clearballs();
    [[eosio::on_notify("clashdometkn::transfer")]] void transfer(const name &from, const name &to, const asset &quantity, const string &memo);

private:

    TABLE claimsts_s {
        name account;
        uint64_t timestamp;
    
        uint64_t primary_key() const {return account.value;}
    };

    typedef multi_index <name("claimsts"), claimsts_s> claimsts_t;
    claimsts_t claimsts = claimsts_t(get_self(), get_self().value); 

    TABLE landactivity_s {
        uint64_t timestamp;
        uint16_t land_id;
        uint64_t partial_orcs;
    
        uint64_t primary_key() const {return timestamp;}
    };

    typedef multi_index <name("landactivity"), landactivity_s> landactivity_t;
    landactivity_t landactivity = landactivity_t(get_self(), get_self().value); 

     TABLE hallactivity_s {
        uint64_t timestamp;
        uint16_t hall_id;
        uint64_t partial_balls;
    
        uint64_t primary_key() const {return timestamp;}
    };

    typedef multi_index <name("hallactivity"), hallactivity_s> hallactivity_t;
    hallactivity_t hallactivity = hallactivity_t(get_self(), get_self().value); 

    TABLE killedorcs_s {
        uint32_t day;
        uint64_t kills;
        uint16_t orcs_ludio_ratio;

        uint64_t primary_key() const {return (uint64_t) day;}
    };

    typedef multi_index <name("killedorcs"), killedorcs_s> killedorcs_t;
    killedorcs_t killedorcs = killedorcs_t(get_self(), get_self().value); 

    TABLE pballs_s {
        uint32_t day;
        uint64_t pocketed_balls;
        uint16_t balls_ludio_ratio;

        uint64_t primary_key() const {return (uint64_t) day;}
    };

    typedef multi_index <name("pballs"), pballs_s> pballs_t;
    pballs_t pballs = pballs_t(get_self(), get_self().value); 

     // TOKEN STATS
    TABLE tokenstats_s{

        uint32_t day;
        asset mined_carbz;
        asset consumed_carbz;
        asset burned_carbz;
        asset mined_credits;
        asset consumed_credits;
        asset burned_credits;
        asset mined_jigo;
        asset consumed_jigo;
        asset burned_jigo;

        uint64_t primary_key() const {return (uint64_t) day;}
    };

    typedef multi_index<name("tokenstats"), tokenstats_s> coindailystats_t;

    coindailystats_t tokenstats = coindailystats_t(get_self(), get_self().value); 

    const string GAME_NAMES[5] = {"Endless Siege", "Candy Fiesta", "Templok", "Ringy Dingy", "Rug Pool"};

    const string COLLECTION_NAME = "clashdomenft";
    const string SCHEMA_NAME_LANDS = "lands";
    const string SCHEMA_NAME_HALL = "poolhalls";

    static constexpr symbol LUDIO_SYMBOL = symbol(symbol_code("LUDIO"), 4);

    // EARLY ACCESS NFT
    const uint64_t SALE_TIME = 1626969600; // Thursday, 22. July 2021 16:00:00
    const uint32_t NFT_PRICE = 50000000; // CHANGE TO 50000000 -> 5K LUDIO
    const uint32_t NFT_MAX_SUPPLY = 250;

    const string EARLY_ACCESS_COLLECTION_NAME = "clashdomenft";
    const string EARLY_ACCESS_SCHEMA_NAME = "vip";
    const uint32_t EARLY_ACCESS_TEMPLATE_ID = 230544;
    const bool WHITELISTED_SALE = true;

    //CONSTANTS
    static constexpr symbol CREDITS_SYMBOL = symbol(symbol_code("CREDITS"), 4);
    static constexpr symbol CARBZ_SYMBOL = symbol(symbol_code("CARBZ"), 4);
    static constexpr symbol JIGOWATTS_SYMBOL = symbol(symbol_code("JIGO"), 4);

    //AUXILIAR FUNCTIONS
    void updateDailyStats(asset assetVal,int type);
    uint32_t epochToDay(time_t time);

};