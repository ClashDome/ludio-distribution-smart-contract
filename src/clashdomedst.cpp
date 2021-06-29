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

    uint8_t co_ownters_amount = get<uint8_t> (idata["co-owners_amount"]);
    uint64_t partial_dead_orcs_counter = get<uint64_t> (mdata["partial_dead_orcs_counter"]);

    // TODO: DETERMINAR LA CANTIDAD DE LUDIO QUE DA UN ORCO MUERTO
    float ludio_per_orc = 0.01f;

    uint32_t killed_orcs_ludio_reward = (uint32_t) (partial_dead_orcs_counter / co_ownters_amount * ludio_per_orc * 10000); 

    // DAR EL LUDIO CORRESPONDIENTE
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

    // CAMBIAR LOS PARAMETROS DEL NFT
    mdata["partial_dead_orcs_counter"] = 0;
    mdata["last_claim_timestamp"] = eosio::current_time_point().sec_since_epoch();

    // AND SAVE THE MUTABLE DATA IN THE NFT
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

void clashdomedst::updateorcs(uint32_t land_id, uint32_t dead_orcs) {
    
    require_auth(get_self());

    // TODO: ENCONTRAR TODOS LOS NFTS QUE CORRESPONDAN AL ID DEL TERRENO
    // TODO: INCREMENTAR A TODOS ESTOS CAMPOS "partial_dead_orcs_counter", "total_dead_orcs_counter" y "games_played"

    // TODO: HACER UNA TABLA QUE CONTENGA LA CANTIDAD DE ORCOS QUE MUEREN CADA DIA
    // TODO: INCREMENTAR LOS DE HOY Y HACER Q ESTA TABLA CONTENGA LOS ULTIMOS 30 DIAS BORRANDO UNA FILA SI ES NECESARIO
}
