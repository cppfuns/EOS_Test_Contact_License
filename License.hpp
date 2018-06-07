#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

class License : public eosio::contract {
    public:
        License( account_name self )
        :eosio::contract(self)
        ,projects(_self, _self)
        ,accounts(_self, _self){}

        void changeUserInfo(account_name owner, const std::string& company_name, const std::string& contact_info);
        void createProject(account_name owner, const std::string& project_name);
        void changeProject(account_name owner, const std::string& project_name, const std::string& company_name, const std::string& contact_info);
        void buyLicense(account_name owner, const std::string& project_name, uint8_t license_type);
        void getLicense(account_name owner, const std::string& project_name, uint8_t license_type);

    private:

        struct account{
            account_name name;
            std::string company_name;
            std::string contact_info;
            uint8_t level;
            uint64_t primary_key()const { return name; }
            EOSLIB_SERIALIZE(account, (name)(company_name)(contact_info)(level))
        };

        typedef eosio::multi_index<N(accounts),account> account_table;
        account_table accounts;

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
EOSIO_ABI(License, (changeUserInfo)(createProject)(changeProject)(buyLicense)(getLicense))