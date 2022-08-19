#include <clashdomedst.hpp>

void clashdomedst::claimludio(name account, uint64_t asset_id, uint16_t game_id) {
    
    require_auth(account);

    atomicassets::assets_t player_assets = atomicassets::get_assets(account);
    auto asset_itr = player_assets.require_find(asset_id, "No NFT with this ID exists");

    check(asset_itr->collection_name == name(COLLECTION_NAME), "NFT doesn't correspond to " + COLLECTION_NAME);

    if (game_id == 0) {

        check(0 == 1, "Currently disabled, try again later.");
        // // CHECK THAT THE ASSET CORRESPONDS TO OUR COLLECTION
        // check(asset_itr->schema_name == name(SCHEMA_NAME_LANDS), "NFT doesn't correspond to schema " + SCHEMA_NAME_LANDS);

        // // CHECK HOW MANY ORCS ARE IN THE PARTIAL COUNTER
        // atomicassets::schemas_t collection_schemas = atomicassets::get_schemas(name(COLLECTION_NAME));
        // auto schema_itr = collection_schemas.find(name(SCHEMA_NAME_LANDS).value);

        // atomicassets::templates_t collection_templates = atomicassets::get_templates(name(COLLECTION_NAME));
        // auto template_itr = collection_templates.find(asset_itr->template_id);

        // vector <uint8_t> immutable_serialized_data = template_itr->immutable_serialized_data;
        // vector <uint8_t> mutable_serialized_data = asset_itr->mutable_serialized_data;

        // atomicassets::ATTRIBUTE_MAP idata = atomicdata::deserialize(immutable_serialized_data, schema_itr->format);
        // atomicassets::ATTRIBUTE_MAP mdata = atomicdata::deserialize(mutable_serialized_data, schema_itr->format);

        // uint8_t co_owners_amount = get<uint8_t> (idata["co-owners_amount"]);
        // uint64_t partial_dead_orcs_counter = get<uint64_t> (mdata["partial_dead_orcs_counter"]);

        // check(partial_dead_orcs_counter > 0, "Nothing to claim");

        // auto today_orcs_data_itr = killedorcs.crbegin();
        // uint16_t orcs_ludio_ratio = today_orcs_data_itr->orcs_ludio_ratio;

        // uint64_t killed_orcs_ludio_reward = (uint64_t) ((((float) partial_dead_orcs_counter / (float) co_owners_amount) / (float) orcs_ludio_ratio) * 10000.0); 

        // // REWARD THE CORRESPONDING LUDIO
        // asset ludio;
        // ludio.symbol = LUDIO_SYMBOL;
        // ludio.amount = killed_orcs_ludio_reward;

        // string land_name = get<string> (idata["name"]);

        // action(
        //     permission_level{get_self(), name("active")},
        //     name("clashdometkn"),
        //     name("transfer"),
        //     std::make_tuple (
        //         get_self(),
        //         account,
        //         ludio,
        //         GAME_NAMES[game_id] + " land " + land_name + " owner reward" 
        //     )
        // ).send();

        // // CHANGE THE MUTABLE DATA IN THE NFT
        // mdata["partial_dead_orcs_counter"] = (uint64_t) 0;
        // mdata["last_claim_timestamp"] = (uint64_t) eosio::current_time_point().sec_since_epoch();

        // action(
        //     permission_level{get_self(), name("active")},
        //     name("atomicassets"),
        //     name("setassetdata"),
        //     std::make_tuple (
        //         get_self(),
        //         account,
        //         asset_id,
        //         mdata
        //     )
        // ).send();

        // //update daily token stats
        // ludio.symbol=CREDITS_SYMBOL;
        // updateDailyStats(ludio,1);
    } else if (game_id == 4) {

        check(0 == 1, "Currently disabled, try again later.");
        // // CHECK THAT THE ASSET CORRESPONDS TO OUR COLLECTION
        // check(asset_itr->schema_name == name(SCHEMA_NAME_HALL), "NFT doesn't correspond to schema " + SCHEMA_NAME_HALL);

        // // CHECK HOW MANY ORCS ARE IN THE PARTIAL COUNTER
        // atomicassets::schemas_t collection_schemas = atomicassets::get_schemas(name(COLLECTION_NAME));
        // auto schema_itr = collection_schemas.find(name(SCHEMA_NAME_HALL).value);

        // atomicassets::templates_t collection_templates = atomicassets::get_templates(name(COLLECTION_NAME));
        // auto template_itr = collection_templates.find(asset_itr->template_id);

        // vector <uint8_t> immutable_serialized_data = template_itr->immutable_serialized_data;
        // vector <uint8_t> mutable_serialized_data = asset_itr->mutable_serialized_data;

        // atomicassets::ATTRIBUTE_MAP idata = atomicdata::deserialize(immutable_serialized_data, schema_itr->format);
        // atomicassets::ATTRIBUTE_MAP mdata = atomicdata::deserialize(mutable_serialized_data, schema_itr->format);

        // uint8_t co_owners_amount = get<uint8_t> (idata["co-owners_amount"]);
        // uint64_t partial_pocketed_balls = get<uint64_t> (mdata["partial_pocketed_balls"]);

        // check(partial_pocketed_balls > 0, "Nothing to claim");

        // auto today_balls_data_itr = pballs.crbegin();
        // uint16_t balls_ludio_ratio = today_balls_data_itr->balls_ludio_ratio;

        // uint64_t balls_pocketed_ludio_reward = (uint64_t) ((((float) partial_pocketed_balls / (float) co_owners_amount) / (float) balls_ludio_ratio) * 10000.0); 

        // // REWARD THE CORRESPONDING LUDIO
        // asset ludio;
        // ludio.symbol = LUDIO_SYMBOL;
        // ludio.amount = balls_pocketed_ludio_reward;

        // string hall_name = get<string> (idata["name"]);

        // action(
        //     permission_level{get_self(), name("active")},
        //     name("clashdometkn"),
        //     name("transfer"),
        //     std::make_tuple (
        //         get_self(),
        //         account,
        //         ludio,
        //         GAME_NAMES[game_id] + " hall " + hall_name + " owner reward" 
        //     )
        // ).send();

        // // CHANGE THE MUTABLE DATA IN THE NFT
        // mdata["partial_pocketed_balls"] = (uint64_t) 0;
        // mdata["last_claim_timestamp"] = (uint64_t) eosio::current_time_point().sec_since_epoch();

        // action(
        //     permission_level{get_self(), name("active")},
        //     name("atomicassets"),
        //     name("setassetdata"),
        //     std::make_tuple (
        //         get_self(),
        //         account,
        //         asset_id,
        //         mdata
        //     )
        // ).send();

        // //update daily token stats
        // ludio.symbol=CREDITS_SYMBOL;
        // updateDailyStats(ludio,1);
    } else {
        check(0 == 1, "wrong game ID:" + to_string(game_id));
    }

    
}

void clashdomedst::claim(name account) {
    
    require_auth(account);

    uint64_t timestamp = eosio::current_time_point().sec_since_epoch();

    auto claim_itr = claimsts.find(account.value);

    if (claim_itr == claimsts.end()) {
        claimsts.emplace(get_self(), [&](auto &_row) {
            _row.account = account;
            _row.timestamp = timestamp;
        });
    } else {
        claimsts.modify(claim_itr, get_self(), [&](auto &_row) {
            _row.timestamp = timestamp;
        });
    }
}

void clashdomedst::updateorcs(uint32_t orcs, uint32_t day, uint16_t land_id, uint32_t partial_orcs) {
    
    require_auth(get_self());

    auto orcs_itr = killedorcs.find(day);

    uint8_t size = 0;

    if (orcs_itr == killedorcs.end()) {

        uint64_t total_killed_orcs = 0;

        for (auto itr = killedorcs.begin(); itr != killedorcs.end(); ++itr) {

            size ++;

            if (size <= 5) {
                total_killed_orcs += itr->kills;
            }
        }

        if (size > 29) { 
            killedorcs.erase(killedorcs.begin());
        }

        uint16_t orcs_ludio_ratio;

        float killed_orcs_average = total_killed_orcs / 5;

        if (killed_orcs_average < 750000) {
            orcs_ludio_ratio = 25;
        } else {

            float f;

            if (killed_orcs_average < 5E6) {
                f = 0.85;
            } else if (killed_orcs_average < 1E7) {
                f = 0.75;
            } else if (killed_orcs_average < 1E8) {
                f = 0.65;
            } else {
                f = 0.5;
            }

            orcs_ludio_ratio = (uint16_t) (killed_orcs_average / 750000 * 25 * f);
        }
        
        killedorcs.emplace(get_self(), [&](auto &_orcs) {
            _orcs.day = day;
            _orcs.kills = orcs;
            _orcs.orcs_ludio_ratio = orcs_ludio_ratio;
        });

    } else {

        killedorcs.modify(orcs_itr, get_self(), [&](auto &_orcs) {
            _orcs.kills += orcs;
        });
    }

    landactivity.emplace(get_self(), [&](auto &_land_data) {
        _land_data.timestamp = (uint64_t) eosio::current_time_point().sec_since_epoch();
        _land_data.land_id = land_id;
        _land_data.partial_orcs = partial_orcs;
    });

    size = 0;

    for (auto itr = landactivity.begin(); itr != landactivity.end(); ++itr) {

        size ++;
    }

    if (size > 50) { 
        landactivity.erase(landactivity.begin());
    }
}

void clashdomedst::updateballs(uint32_t balls, uint32_t day, uint16_t hall_id, uint32_t partial_balls) {
    
    require_auth(get_self());

    auto balls_itr = pballs.find(day);

    uint8_t size = 0;

    if (balls_itr == pballs.end()) {

        uint64_t total_pocketed_balls = 0;

        for (auto itr = pballs.begin(); itr != pballs.end(); ++itr) {

            size ++;

            if (size <= 5) {
                total_pocketed_balls += itr->pocketed_balls;
            }
        }

        if (size > 29) { 
            pballs.erase(pballs.begin());
        }

        uint16_t balls_ludio_ratio = 1;

        // float pocketed_balls_average = total_pocketed_balls / 5;

        // if (pocketed_balls_average < 15000) {
        //     balls_ludio_ratio = 5;
        // } else {

        //     float f;

        //     if (pocketed_balls_average < 100000) {
        //         f = 0.85;
        //     } else if (pocketed_balls_average < 200000) {
        //         f = 0.75;
        //     } else if (pocketed_balls_average < 2000000) {
        //         f = 0.65;
        //     } else {
        //         f = 0.5;
        //     }

        //     balls_ludio_ratio = (uint16_t) (pocketed_balls_average / 15000 * 5 * f);
        // }
        
        pballs.emplace(get_self(), [&](auto &_balls) {
            _balls.day = day;
            _balls.pocketed_balls = balls;
            _balls.balls_ludio_ratio = balls_ludio_ratio;
        });

    } else {

        pballs.modify(balls_itr, get_self(), [&](auto &_balls) {
            _balls.pocketed_balls += balls;
        });
    }

    hallactivity.emplace(get_self(), [&](auto &_hall_data) {
        _hall_data.timestamp = (uint64_t) eosio::current_time_point().sec_since_epoch();
        _hall_data.hall_id = hall_id;
        _hall_data.partial_balls = partial_balls;
    });

    size = 0;

    for (auto itr = hallactivity.begin(); itr != hallactivity.end(); ++itr) {

        size ++;
    }

    if (size > 50) { 
        hallactivity.erase(hallactivity.begin());
    }
}

void clashdomedst::clearorcs() {

    require_auth(get_self());

    auto it = killedorcs.begin();
    while (it != killedorcs.end()) {
        it = killedorcs.erase(it);
    }
}

void clashdomedst::clearlands() {

    require_auth(get_self());

    auto it = landactivity.begin();
    while (it != landactivity.end()) {
        it = landactivity.erase(it);
    }
}

void clashdomedst::clearballs() {

    require_auth(get_self());

    auto it = pballs.begin();
    while (it != pballs.end()) {
        it = pballs.erase(it);
    }
}

void clashdomedst::transfer(const name &from, const name &to, const asset &quantity, const string &memo) {

    require_auth(from);

    if (to == _self || from != _self) {
        return;
    }

    // CHECK IF IT IS A VALID CLASHDOME TOKEN PAYMENT
    check(quantity.symbol.is_valid(), "ClashDome Error - invalid quantity");
    check(quantity.amount > 0, "ClashDome Error - only positive ClashDome token transfer allowed");

    if (memo.find("NFT claim") != string::npos) {

        asset ludio;
        ludio.symbol = CREDITS_SYMBOL;
        ludio.amount = quantity.amount;

        updateDailyStats(ludio,1);
    }
}

void clashdomedst::updateDailyStats(asset assetVal,int type){
    int64_t amount= assetVal.amount;
    symbol symbol= assetVal.symbol;

    asset nullasset;
    nullasset.amount=0.0000;
    nullasset.symbol=CARBZ_SYMBOL;
    uint64_t timestamp = eosio::current_time_point().sec_since_epoch();
    
    uint32_t day=epochToDay(timestamp);

    auto ptokenstatsitr = tokenstats.find(day);

    if (ptokenstatsitr == tokenstats.end()) {

        tokenstats.erase(tokenstats.begin());                 //We delete the oldest row in the table   

        ptokenstatsitr = tokenstats.emplace(CONTRACTN, [&](auto &new_d) {
            new_d.day = day;
            new_d.mined_carbz=nullasset;
            new_d.consumed_carbz=nullasset;
            new_d.burned_carbz=nullasset;
            nullasset.symbol=CREDITS_SYMBOL;
            new_d.mined_credits=nullasset;
            new_d.consumed_credits=nullasset;
            new_d.burned_credits=nullasset;
            nullasset.symbol=JIGOWATTS_SYMBOL;
            new_d.mined_jigo=nullasset;
            new_d.consumed_jigo=nullasset;
            new_d.burned_jigo=nullasset;
        });
    }
    if(symbol==CARBZ_SYMBOL){
        if (type==1){
        //mined carbz++
        int64_t currtoken=ptokenstatsitr->mined_carbz.amount;
        currtoken += amount;
        tokenstats.modify(ptokenstatsitr, get_self(), [&](auto &mod_day) {
                mod_day.mined_carbz.amount=currtoken;
            });
        
        }else if(type==0){
        //consumed carbz++
        int64_t currtoken=ptokenstatsitr->consumed_carbz.amount;
        currtoken += amount;
        tokenstats.modify(ptokenstatsitr, get_self(), [&](auto &mod_day) {
                mod_day.consumed_carbz.amount=currtoken;
            });
        }else if(type==2){
        //burned carbz++
        int64_t currtoken=ptokenstatsitr->burned_carbz.amount;
        currtoken += amount;
        tokenstats.modify(ptokenstatsitr, get_self(), [&](auto &mod_day) {
                mod_day.burned_carbz.amount=currtoken;
            });
        }
    }
    else if(symbol==CREDITS_SYMBOL){
        if (type==1){
        //mined credits++
        int64_t currtoken=ptokenstatsitr->mined_credits.amount;
        currtoken += amount;
        tokenstats.modify(ptokenstatsitr, get_self(), [&](auto &mod_day) {
                mod_day.mined_credits.amount=currtoken;
            });
        
        }else if(type==0){
        //consumed credits++
        int64_t currtoken=ptokenstatsitr->consumed_credits.amount;
        currtoken += amount;
        tokenstats.modify(ptokenstatsitr, get_self(), [&](auto &mod_day) {
                mod_day.consumed_credits.amount=currtoken;
            });
        }else if(type==2){
        //burned credits++
        int64_t currtoken=ptokenstatsitr->burned_credits.amount;
        currtoken += amount;
        tokenstats.modify(ptokenstatsitr, get_self(), [&](auto &mod_day) {
                mod_day.burned_credits.amount=currtoken;
            });
        }
    }
    else if(symbol==JIGOWATTS_SYMBOL){
        if (type==1){
        //minted jigo++
        int64_t currtoken=ptokenstatsitr->mined_jigo.amount;
        currtoken += amount;
        tokenstats.modify(ptokenstatsitr, get_self(), [&](auto &mod_day) {
                mod_day.mined_jigo.amount=currtoken;
            });
        
        }else if(type==0){
        //consumed jigo++
        int64_t currtoken=ptokenstatsitr->consumed_jigo.amount;
        currtoken += amount;
        tokenstats.modify(ptokenstatsitr, get_self(), [&](auto &mod_day) {
                mod_day.consumed_jigo.amount=currtoken;
            });
        }else if(type==2){
        //burned jigo++
        int64_t currtoken=ptokenstatsitr->burned_jigo.amount;
        currtoken += amount;
        tokenstats.modify(ptokenstatsitr, get_self(), [&](auto &mod_day) {
                mod_day.burned_jigo.amount=currtoken;
            });
        }
    }
} 
uint32_t clashdomedst::epochToDay(time_t time){
    tm *tm_gmt = gmtime(&time);
	uint32_t daytime=0;
	return daytime=(tm_gmt->tm_year+1900)*10000+(tm_gmt->tm_mon+1)*100+(tm_gmt->tm_mday);
}

