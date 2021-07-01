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

    // VER CUANTOS ORCOS HAY EN EL CONTADOR PARCIAL
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

    // GIVE THE CORRESPONDING LUDIO
    asset ludio;
    ludio.symbol = LUDIO_SYMBOL;
    ludio.amount = killed_orcs_ludio_reward;

    action(
        permission_level{get_self(), name("active")},
        name("clashdometkn"),
        name("transfer"),
        std::make_tuple (
            get_self(),
            account,
            ludio,
            GAME_NAMES[game_id] + " land owner reward" 
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

void clashdomedst::updateorcs(uint32_t orcs, uint32_t day) {
    
    require_auth(get_self());

    // KILLED ORCS SECURITY TEST
    if (orcs > 1E5) {
        orcs = 1E5;
    }

    auto orcs_itr = killedorcs.find(day);

    if (orcs_itr == killedorcs.end()) {

        uint8_t size = 0;
        uint64_t total_orcs = 0;

        for (auto itr = killedorcs.begin(); itr != killedorcs.end(); ++itr) {
            size ++;
            total_orcs += itr->kills;
        }

        if (size > 29) { 
            killedorcs.erase(killedorcs.begin());
        }

        uint16_t orcs_ludio_ratio = 25;

        if (size > 0) {

            float killedorcs_average = total_orcs / size;

            if (killedorcs_average > 1E8) {
                orcs_ludio_ratio = 150;
            } else if (killedorcs_average > 1E7) {
                orcs_ludio_ratio = 50;
            }
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
}

void clashdomedst::clearorcs() {

    auto it = killedorcs.begin();
    while (it != killedorcs.end()) {
        it = killedorcs.erase(it);
    }
}
