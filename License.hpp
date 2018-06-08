#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

class License : public eosio::contract {
    public:
        License( account_name self )
        :eosio::contract(self)
        ,projects(_self, _self){}

        void setuserinfo(account_name owner, const std::string& company_name, const std::string& contact_info);
        void makeproject(account_name owner, const std::string& project_name);
        void setproject(account_name owner, const std::string& project_name, const std::string& company_name, const std::string& contact_info);
        void buylicense(account_name owner, const std::string& project_name, uint8_t license_type);
        void getlicense(account_name owner, const std::string& project_name, uint8_t license_type);

    private:
        //@abi table projects i64
        struct project{
            account_name owner;
            std::string company_name;
            std::string contact_info;
            uint8_t level;
            uint64_t primary_key()const { return owner; }
            EOSLIB_SERIALIZE(project, (owner)(company_name)(contact_info)(level))
        };

        typedef eosio::multi_index<N(projects),project> project_table;
        project_table projects;
};
EOSIO_ABI(License, (setuserinfo)(makeproject)(setproject)(buylicense)(getlicense))