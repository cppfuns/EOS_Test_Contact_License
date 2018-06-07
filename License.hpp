#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

class License : public eosio::contract {
    public:
        License( account_name self )
        :eosio::contract(self)
        ,projects(_self, _self){}

    private:


        //@abi table projects i64
        struct project{
            account_name owner;
            std::string project_name;
            std::string company_name;
            std::string contact_info;
            uint8_t      status;
            std::string license_i;
            std::string license_u;

            uint64_t primary_key()const { return owner; }
            EOSLIB_SERIALIZE(project, (owner)(project_name)(company_name)(contact_info)(status)(license_i)(license_u))
        };

        typedef eosio::multi_index<N(projects),project> project_table;
        project_table projects;
};