#include <clashdomedst.hpp>

void clashdomedst::claimludio(name account, uint64_t asset_id, uint16_t game_id) {
    
    require_auth(account);

    // CHECK IF game_id IS VALID
    check(game_id >= 0 && game_id < sizeof(GAME_NAMES)/sizeof(GAME_NAMES[0]), "wrong game ID:" + to_string(game_id));

    atomicassets::assets_t player_assets = atomicassets::get_assets(account);
    auto asset_itr = player_assets.require_find(asset_id, "No NFT with this ID exists");

    // CHECK THAT THE ASSET CORRESPONDS TO OUR COLLECTION
    check(asset_itr->collection_name == name(COLLECTION_NAME), "NFT doesn't correspond to " + COLLECTION_NAME);
    check(asset_itr->schema_name == name(SCHEMA_NAME), "NFT doesn't correspond to schema " + SCHEMA_NAME);

    // CHECK HOW MANY ORCS ARE IN THE PARTIAL COUNTER
    atomicassets::schemas_t collection_schemas = atomicassets::get_schemas(name(COLLECTION_NAME));
    auto schema_itr = collection_schemas.find(name(SCHEMA_NAME).value);

    atomicassets::templates_t collection_templates = atomicassets::get_templates(name(COLLECTION_NAME));
    auto template_itr = collection_templates.find(asset_itr->template_id);

    vector <uint8_t> immutable_serialized_data = template_itr->immutable_serialized_data;
    vector <uint8_t> mutable_serialized_data = asset_itr->mutable_serialized_data;

    atomicassets::ATTRIBUTE_MAP idata = atomicdata::deserialize(immutable_serialized_data, schema_itr->format);
    atomicassets::ATTRIBUTE_MAP mdata = atomicdata::deserialize(mutable_serialized_data, schema_itr->format);

    uint8_t co_owners_amount = get<uint8_t> (idata["co-owners_amount"]);
    uint64_t partial_dead_orcs_counter = get<uint64_t> (mdata["partial_dead_orcs_counter"]);

    check(partial_dead_orcs_counter > 0, "Nothing to claim");

    auto today_orcs_data_itr = killedorcs.crbegin();
    uint16_t orcs_ludio_ratio = today_orcs_data_itr->orcs_ludio_ratio;

    uint64_t killed_orcs_ludio_reward = (uint64_t) ((((float) partial_dead_orcs_counter / (float) co_owners_amount) / (float) orcs_ludio_ratio) * 10000.0); 

    // REWARD THE CORRESPONDING LUDIO
    asset ludio;
    ludio.symbol = LUDIO_SYMBOL;
    ludio.amount = killed_orcs_ludio_reward;

    string land_name = get<string> (idata["name"]);

    action(
        permission_level{get_self(), name("active")},
        name("clashdometkn"),
        name("transfer"),
        std::make_tuple (
            get_self(),
            account,
            ludio,
            GAME_NAMES[game_id] + " land " + land_name + " owner reward" 
        )
    ).send();

    // CHANGE THE MUTABLE DATA IN THE NFT
    mdata["partial_dead_orcs_counter"] = (uint64_t) 0;
    mdata["last_claim_timestamp"] = (uint64_t) eosio::current_time_point().sec_since_epoch();

    action(
        permission_level{get_self(), name("active")},
        name("atomicassets"),
        name("setassetdata"),
        std::make_tuple (
            get_self(),
            account,
            asset_id,
            mdata
        )
    ).send();
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

        uint16_t orcs_ludio_ratio = 25;

        float killed_orcs_average = total_killed_orcs / 5;

        if (killed_orcs_average > 1E8) {
            orcs_ludio_ratio = 150;
        } else if (killed_orcs_average > 1E7) {
            orcs_ludio_ratio = 50;
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

void clashdomedst::addtowl(vector <name> accounts_to_add) {

    require_auth(get_self());

    // TODO: CHECK IF ACCOUNTS ARE DUPLICATED AND VALID 
    
    auto wl_itr = whitelists.begin();

    if (wl_itr == whitelists.end()) {

        whitelists.emplace(get_self(), [&](auto &_wl) {
            _wl.id = 1;
            _wl.whitelist = accounts_to_add;
        });

    } else {

        vector<name> whitelist = wl_itr->whitelist;

        for (auto accounts_itr = accounts_to_add.begin(); accounts_itr < accounts_to_add.end(); accounts_itr ++) {
            whitelist.push_back(*accounts_itr);
        }

        whitelists.modify(wl_itr, get_self(), [&](auto &_wl) {

            _wl.whitelist = whitelist;
        });
    }   
}

void clashdomedst::clearwl() {
    
    require_auth(get_self());

    auto it = whitelists.begin();
    while (it != whitelists.end()) {
        it = whitelists.erase(it);
    }
}

void clashdomedst::transfer(const name &from, const name &to, const asset &quantity, const string &memo) {

    require_auth(from);

    if (from == _self || to != _self) {
        return;
    }

    // CHECK IF IS IT A VALID LUDIO PAYMENT
    check(quantity.symbol.is_valid(), "invalid quantity");
    check(quantity.amount > 0, "only positive quantity allowed");
    check(quantity.amount >= NFT_PRICE, "not enough LUDIO to complete the transaction");
    check(quantity.symbol == LUDIO_SYMBOL, "only LUDIO tokens allowed");

    // TODO: USAR EL MEMO POR QUE A CUALQUIERA Q MANDE ESA CANTIDAD DE LUDIO A 
    // clashdomedst SE LE MINTARA UN NFT

    // CHECK IF ACCOUNT IS WHITELISTED
    bool whitelisted = false;

    auto wl_itr = whitelists.begin();
    vector<name> whitelist = wl_itr->whitelist;

    for (auto it = whitelist.begin(); it != whitelist.end(); ++it) {

        if (*it == from) {

            whitelisted = true;

            // REMOVE IT FROM THE WHITELIST
            whitelist.erase(it);

            whitelists.modify(wl_itr, get_self(), [&](auto &_wl) {
                _wl.whitelist = whitelist;
            });

            break;
        }
    }

    check(whitelisted, "account is not whitelisted");

    // MINT THE NFT

    action (
        permission_level{get_self(), name("active")},
        name("atomicassets"),
        name("mintasset"),
        make_tuple(
            get_self(),
            "clashdomenft",
            "gamedata",
            82326,
            from,
            (atomicassets::ATTRIBUTE_MAP) {},
            (atomicassets::ATTRIBUTE_MAP) {},
            (vector <asset>) {}
        )
    ).send();
}

